#ifndef APP_IMAGEITEM_H
#define APP_IMAGEITEM_H

#include <QUuid>
#include <QUrl>

struct ImageItem {
    QUuid id;
    QUrl url;
    bool selected;
};

#endif // APP_IMAGEITEM_H
