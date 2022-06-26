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
        QImage img = readImage(*imageItem);
        QPixmap modifiedImg = QPixmap::fromImage(img);
        pixmap = QPixmap(modifiedImg.scaled(
            QSize(100, 50), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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

QImage ImageProvider::readImage(const ImageItem imageItem)
{
    QImage image(imageItem.url.toLocalFile());

    return image;
}
