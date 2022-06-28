#include "imagefilterproxymodel.h"
#include "imagelistmodel.h"

ImageFilterProxyModel::ImageFilterProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    // Is this needed?
    setDynamicSortFilter(true);
}

bool ImageFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    const bool selected = index.data(ImageListModel::SelectedRole).toBool();
    
    return selected;
}
