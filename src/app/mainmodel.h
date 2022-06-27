#ifndef APP_MAINMODEL_H
#define APP_MAINMODEL_H

#include <QObject>
#include <QUrl>
#include <QImage>
#include <QtQml/qqmlregistration.h>
#include "imageprovider.h"
#include "imageitem.h"

class MainModel : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MainModel(QObject* parent = nullptr);

    ~MainModel();

    QVector<ImageItem> items() const;

    bool setItemAt(int index, const ImageItem& item);

    ImageProvider* getImageProvider();

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void updateItem(int index);
    void updateImage(QUuid id);

public slots:
    void importImages(QList<QUrl> files);
    void exportImages(QUrl folder);
    void doBinning();
    void removeImages();

private:
    QVector<ImageItem> items_;
    ImageProvider* imageProvider_;

    // Prevent copy construction and assignment
    MainModel(const MainModel&);
    MainModel& operator=(const MainModel &);
};

#endif // APP_MAINMODEL_H
