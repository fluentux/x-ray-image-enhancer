#ifndef APP_IMAGEFILTERPROXYMODEL_H
#define APP_IMAGEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class ImageFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    explicit ImageFilterProxyModel(QObject* parent = nullptr);

    int count() const;

signals:
    void countChanged();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const;
};

#endif // APP_IMAGEFILTERPROXYMODEL_H
