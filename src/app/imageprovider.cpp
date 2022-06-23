
#include <QQmlExtensionPlugin>
#include "QQuickImageProvider"

#include "imageprovider.h"
#include "binning.h"
#include "xrayimage.h"
#include "imagereader.h"

static QImage read_image(QList<ImageItem>::Iterator imageItem)
{
    // TODO: Read image with ImageReader and do binning when needed

    QImage image(imageItem->url.toLocalFile());

    return image;
}

ImageProvider::ImageProvider(MainModel* mainModel) :
    QQuickImageProvider(QQuickImageProvider::Pixmap), mainModel_(mainModel)
{

}

QPixmap ImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    int width = 100;
    int height = 50;

    if (!mainModel_) {
        return QPixmap();
    }

    if (size)
    {
        *size = QSize(width, height);
    }

    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);

    QUuid uuid(QByteArray::fromPercentEncoding(id.toLatin1()));

    auto items = mainModel_->items();

    auto imageItem = std::find_if(items.begin(), items.end(), [&](ImageItem item) {
        return item.id == uuid; }
    );

    // Load image from url
    if (imageItem != items.end()) {
        QImage img = read_image(imageItem);
        QPixmap modifiedImg = QPixmap::fromImage(img);
        return modifiedImg;
    }

    return pixmap;
}
