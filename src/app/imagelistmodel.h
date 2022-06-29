#ifndef APP_IMAGELISTMODEL_H
#define APP_IMAGELISTMODEL_H

#include <QAbstractListModel>

#include "mainmodel.h"

// Image list handler which allows showing and updating list of images
// in the view
class ImageListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(MainModel* mainModel READ mainModel WRITE setMainModel)

public:
    explicit ImageListModel(QObject* parent = nullptr);

    enum {
        IdRole = Qt::UserRole,
        UrlRole = Qt::UserRole + 1,
        SelectedRole = Qt::UserRole + 2
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    MainModel* mainModel() const;
    void setMainModel(MainModel* mainModel);

private:
    MainModel* mainModel_;
};

#endif // APP_IMAGELISTMODEL_H
