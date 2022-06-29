#include <QUrl>
#include <QUuid>
#include <memory>
#include "mainmodel.h"
#include "imageitem.h"
#include "imagewriter.h"
#include "imagewriterexception.h"
#include "imagereaderexception.h"
#include "binning.h"

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

QVector<ImageItem> MainModel::items() const
{
    return items_;
}

bool MainModel::setItemAt(int index, const ImageItem& item)
{
    if (index < 0 || index >= items_.size())
        return false;

    const ImageItem& oldItem = items_.at(index);

    items_[index] = item;

    return true;
}

void MainModel::importImages(QList<QUrl> urls)
{
    int importCount = 0;
    for (auto& url : urls) {
        ImageItem imageItem;
        imageItem.id = QUuid::createUuid();
        imageItem.url = url;
        imageItem.selected = false;

        emit preItemAppended();

        items_.append(imageItem);

        emit postItemAppended();

        importCount++;
    }
}

void MainModel::exportImages(QUrl url)
{
    ImageWriter imageWriter;

    int exportCount = 0;
    int failureCount = 0;
    for (auto& imageItem : items_) {
        if (!imageItem.selected)
            continue;

        try {
            auto image = imageProvider_->getImage(imageItem);

            auto writeUrl = url.toString() + "/" +
                imageItem.url.fileName().section(".", 0, 0) +
                ".png";

            imageWriter.write(image, writeUrl.toStdString());
            exportCount++;
        }
        catch (ImageReaderException) {
            failureCount++;
        }
        catch (ImageWriterException) {
            failureCount++;
        }
    }

    QString s = exportCount > 1 ? "s" : "";
    if (failureCount > 0) {
        emit showError(QString("Failed to export %1 image%2").arg(failureCount).arg(s));
    } else {
        emit showMessage(QString("Exported %1 image%2").arg(exportCount).arg(s));
    }
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

void MainModel::resetChanges()
{
    int index = 0;
    for (auto& imageItem : items_) {
        if (imageItem.selected) {
            imageItem.enhancements.clear();
            emit updateItem(index);
            emit updateImage(imageItem.id);
        }
        index++;
    }
}

void MainModel::doBinning()
{
    int index = 0;
    for (auto& imageItem : items_) {
        if (imageItem.selected) {
            auto binningPointer = QSharedPointer<Binning>(new Binning(2, 2));
            imageItem.enhancements.append(binningPointer);
            emit updateItem(index);
            emit updateImage(imageItem.id);
        }
        index++;
    }
}
