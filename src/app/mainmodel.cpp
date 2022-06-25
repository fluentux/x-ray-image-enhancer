#include <QUrl>
#include <QUuid>
#include "mainmodel.h"
#include "imageitem.h"
#include "imagewriter.h"

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    imageProvider_ = new ImageProvider(items_);
}

MainModel::~MainModel()
{
    delete imageProvider_;
}

ImageProvider* MainModel::getImageProvider()
{
    return imageProvider_;
}

void MainModel::importImages(QList<QUrl> urls)
{
    for (auto& url : urls) {
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
    for (auto& imageItem : items_) {
        auto image = imageProvider_->getImage(imageItem);

        std::string fullname = imageItem.url.fileName().toStdString();
        size_t lastindex = fullname.find_last_of(".");
        std::string rawname = fullname.substr(0, lastindex);

        std::string imageExtension = ".png";
        std::string imageUrl = url.toLocalFile().toStdString() +
                "/" + rawname + imageExtension;

        ImageWriter imageWriter;
        imageWriter.write(imageUrl, image);
    }
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
