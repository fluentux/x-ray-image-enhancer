#include "imagelistmodel.h"
#include "imageitem.h"
#include "mainmodel.h"

ImageListModel::ImageListModel(QObject* parent)
    : QAbstractListModel(parent), mainModel_(nullptr)
{
}

int ImageListModel::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mainModel_)
        return 0;

    return mainModel_->items().size();
}

QVariant ImageListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !mainModel_)
        return QVariant();

    const ImageItem item = mainModel_->items().at(index.row());

    switch (role) {
    case IdRole:
        return QVariant(item.id);
    case UrlRole:
        return QVariant(item.url);
    case SelectedRole:
        return QVariant(item.selected);
    }

    return QVariant();
}

bool ImageListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!mainModel_)
        return false;

    ImageItem item = mainModel_->items().at(index.row());
    switch (role) {
    case IdRole:
        item.id = value.toUuid();
        break;
    case UrlRole:
        item.url = value.toUrl();
        break;
    case SelectedRole:
        item.selected = value.toBool();
        break;
    }

    if (mainModel_->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

Qt::ItemFlags ImageListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ImageListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IdRole] = "id";
    names[UrlRole] = "url";
    names[SelectedRole] = "selected";
    return names;
}

MainModel* ImageListModel::mainModel() const
{
    return mainModel_;
}

void ImageListModel::setMainModel(MainModel* mainModel)
{
    beginResetModel();

    if (mainModel_)
        mainModel_->disconnect(this);

    mainModel_ = mainModel;

    if (mainModel_) {
        connect(mainModel_, &MainModel::preItemAppended, this, [=]() {
            const int index = mainModel_->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mainModel_, &MainModel::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mainModel_, &MainModel::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mainModel_, &MainModel::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
