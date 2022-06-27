#include <QQmlExtensionPlugin>
#include "QQuickImageProvider"
#include "imageprovider.h"
#include "binning.h"
#include "xrayimage.h"
#include "imagereader.h"

ImageProvider::ImageProvider(const QVector<ImageItem>& items) :
    QQuickImageProvider(QQuickImageProvider::Pixmap), items_(items)
{
}

QPixmap ImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    int width = 100;
    int height = 50;

    if (items_.empty()) {
        return QPixmap();
    }

    if (size)
    {
        *size = QSize(width, height);
    }

    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    QUuid uuid(QByteArray::fromPercentEncoding(id.toLatin1()));

    auto imageItem = std::find_if(items_.begin(), items_.end(), [&](ImageItem item) {
        return item.id == uuid; }
    );

    // Load image from url
    if (imageItem != items_.end()) {
        auto image = getImage(*imageItem);
        QImage img = convertToQImage(*image);
        QPixmap modifiedImg = QPixmap::fromImage(img);
        //pixmap = QPixmap(modifiedImg.scaled(
        //    QSize(100, 50), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        pixmap = QPixmap(modifiedImg);
        return modifiedImg;
    }

    return pixmap;
}

std::unique_ptr<XrayImageAbstract> ImageProvider::getImage(const ImageItem& imageItem)
{
    ImageReader imageReader;

    // TODO: Cache images?

    auto image = imageReader.read(imageItem.url.toLocalFile().toStdString());

    for (auto& enhancement : imageItem.enhancements) {
        image = enhancement->execute(*image);
    }

    return image;
}

QImage ImageProvider::convertToQImage(XrayImageAbstract& image)
{
    auto format = image.getFormat() == XrayImageFormat::Gray8 ?
                QImage::Format::Format_Grayscale8 : QImage::Format::Format_Grayscale16;

    QImage qImage(image.width(), image.height(), format);

    const auto totalPixels = image.width() * image.height();

    // TODO: Use image->getPixelData() instead rather than casts

    if (image.getFormat() == XrayImageFormat::Gray8) {
        auto d = reinterpret_cast<uint8_t*> (qImage.bits());
        auto t = dynamic_cast<XrayImage<uint8_t>&>(image);
        auto pixels = t.pixels();
        for(int i = 0; i < totalPixels; i++) {
            d[i] = pixels[i];
        }

        return qImage;
    }

    if (image.getFormat() == XrayImageFormat::Gray16) {
        auto d = reinterpret_cast<quint16*>(qImage.bits());
        auto t = dynamic_cast<XrayImage<uint16_t>&>(image);
        auto pixels = t.pixels();
        for(int i = 0; i < totalPixels; i++) {
            d[i] = pixels[i];
        }

        return qImage;
    }

    return QImage();
}
