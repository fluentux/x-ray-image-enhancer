#ifndef APP_IMAGE_PROVIDER_H
#define APP_IMAGE_PROVIDER_H

#include "QQuickImageProvider"
#include "imageitem.h"
#include "xrayimage.h"

#include "imagereader.h"

class ImageProvider : public QQuickImageProvider {
public:
    ImageProvider(const QVector<ImageItem>& items);

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

    std::unique_ptr<XrayImageAbstract> getImage(const ImageItem& imageItem);

private:
    QImage convertToQImage(XrayImageAbstract& image);

    const QVector<ImageItem>& items_;
};

#endif // APP_IMAGE_PROVIDER_H
