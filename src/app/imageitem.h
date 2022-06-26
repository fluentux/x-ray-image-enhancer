#ifndef APP_IMAGEITEM_H
#define APP_IMAGEITEM_H

#include <QUuid>
#include <QUrl>
#include <QSharedPointer>
#include "imageenhancement.h"

struct ImageItem {
    QUuid id;
    QUrl url;
    bool selected;
    QVector<QSharedPointer<ImageEnhancement>> enhancements;
};

#endif // APP_IMAGEITEM_H
