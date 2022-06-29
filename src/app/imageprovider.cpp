#include <QQmlExtensionPlugin>
#include "QQuickImageProvider"
#include "imageprovider.h"
#include "binning.h"
#include "imagereader.h"
#include "imagereaderexception.h"
#include "xrayimage.h"

ImageProvider::ImageProvider(const QVector<ImageItem>& items) :
    QQuickImageProvider(QQuickImageProvider::Image), items_(items)
{
}

QImage ImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    if (items_.empty()) {
        return QImage();
    }

    int defaultWidth = 100;
    int defaultHeight = 100;
    if (size)
    {
        *size = QSize(defaultWidth, defaultHeight);
    }

    QUuid uuid(QByteArray::fromPercentEncoding(id.toLatin1()));

    auto imageItem = std::find_if(items_.begin(), items_.end(), [&](ImageItem item) {
        return item.id == uuid; }
    );

    if (imageItem != items_.end()) {
        try {
            auto image = getImage(*imageItem);
            if (image->getType() == XrayImageType::Gray8) {
                return convertToQImage<quint8>(*image);
            }
            if (image->getType() == XrayImageType::Gray16) {
                return convertToQImage<quint16>(*image);
            }
        } catch (ImageReaderException) {
            QImage errorImage(1, 1, QImage::Format_RGB16);
            errorImage.fill(Qt::red);
            return errorImage;
        }
    }

    return QImage();
}

std::unique_ptr<XrayImageAbstract> ImageProvider::getImage(const ImageItem& imageItem)
{
    ImageReader imageReader;

    auto image = imageReader.read(imageItem.url.toLocalFile().toStdString());

    for (auto& enhancement : imageItem.enhancements) {
        image = enhancement->execute(*image);
    }

    return image;
}

template <typename QPixelType>
QImage ImageProvider::convertToQImage(XrayImageAbstract& image)
{
    auto format = image.getType() == XrayImageType::Gray8 ?
                QImage::Format::Format_Grayscale8 : QImage::Format::Format_Grayscale16;

    QImage qImage(image.width(), image.height(), format);

    auto pixelData = reinterpret_cast<QPixelType*>(image.getPixelData());
    auto pixelIndex = 0;
    for (int row = 0; row < image.height(); row++) {
        auto pixelRow = reinterpret_cast<QPixelType*>(
                    qImage.bits() + row * qImage.bytesPerLine());
        for (int col = 0; col < image.width(); col++) {
            pixelRow[col] = static_cast<QPixelType>(pixelData[pixelIndex++]);
        }
    }

    return qImage;
}

