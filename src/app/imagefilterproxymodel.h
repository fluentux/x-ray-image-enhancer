#ifndef APP_IMAGEFILTERPROXYMODEL_H
#define APP_IMAGEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class ImageFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    explicit ImageFilterProxyModel(QObject* parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const;
};

#endif // APP_IMAGEFILTERPROXYMODEL_H
