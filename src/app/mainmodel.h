#ifndef APP_MAINMODEL_H
#define APP_MAINMODEL_H

#include <QObject>
#include <QUrl>
#include <QImage>
#include <QtQml/qqmlregistration.h>

#include "imageitem.h"

class MainModel : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MainModel(QObject* parent = nullptr);

    QVector<ImageItem> items() const;

    bool setItemAt(int index, const ImageItem& item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void importImages(QList<QUrl> files);
    void exportImages(QUrl folder);
    void doBinning();
    void removeImages();

private:
    QVector<ImageItem> items_;
};

#endif // APP_MAINMODEL_H
