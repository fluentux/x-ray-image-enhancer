#ifndef APP_IMAGEFILTERPROXYMODEL_H
#define APP_IMAGEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

// Filter proxy model which can be used for showing only selected
// images in the view
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
