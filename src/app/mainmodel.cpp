#include <QUrl>
#include <QUuid>

#include "mainmodel.h"
#include "imageitem.h"

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{

}

void MainModel::importImages(QList<QUrl> urls)
{
    for (auto url : urls) {
        ImageItem imageItem;
        imageItem.id = QUuid::createUuid();
        imageItem.url = url;
        imageItem.selected = true;

        emit preItemAppended();

        items_.append(imageItem);

        emit postItemAppended();
    }
}

void MainModel::exportImages(QUrl url)
{
    // TODO: Export images
}

void MainModel::doBinning()
{
    // TODO: Do binning
}

QVector<ImageItem> MainModel::items() const
{
    return items_;
}

bool MainModel::setItemAt(int index, const ImageItem& item)
{
    if (index < 0 || index >= items_.size())
        return false;

    const ImageItem& oldItem = items_.at(index);
    if (item.id == oldItem.id)
        return false;

    items_[index] = item;

    return true;
}

void MainModel::removeImages()
{
    for (int i = 0; i < items_.size(); ) {
        if (items_.at(i).selected) {
            emit preItemRemoved(i);
            items_.removeAt(i);
            emit postItemRemoved();
        } else {
            i++;
        }
    }
}
