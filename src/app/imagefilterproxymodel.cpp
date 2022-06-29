#include "imagefilterproxymodel.h"
#include "imagelistmodel.h"

ImageFilterProxyModel::ImageFilterProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    connect(this, &QAbstractItemModel::rowsInserted, this, &ImageFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::rowsRemoved, this, &ImageFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::modelReset, this, &ImageFilterProxyModel::countChanged);
    connect(this, &QAbstractItemModel::layoutChanged, this, &ImageFilterProxyModel::countChanged);
    setDynamicSortFilter(true);
}

int ImageFilterProxyModel::count() const
{
    return rowCount();
}

bool ImageFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    const bool selected = index.data(ImageListModel::SelectedRole).toBool();
    
    return selected;
}
