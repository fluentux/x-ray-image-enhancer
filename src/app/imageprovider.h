#ifndef APP_IMAGE_PROVIDER_H
#define APP_IMAGE_PROVIDER_H

#include "QQuickImageProvider"

#include "mainmodel.h"

class ImageProvider : public QQuickImageProvider {
public:
    ImageProvider(MainModel* mainModel);

    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override;

private:
    MainModel* mainModel_;
};

#endif // APP_IMAGE_PROVIDER_H
