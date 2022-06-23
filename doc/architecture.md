# Architecture

The architecture of the application is separated into layers:

- Domain - business objects and logic
- Service - application logic
- Infrastructure - persisting data
- Presentation - user interface

## Modules

### Imaging (imaging)

Imaging module contains domain objects related to imaging.

Layer: Domain

```mermaid
classDiagram
  class XrayImage {
    +vector<GrayPixel> pixels()
    +uint width()
    +uint height()
    -vector<GrayPixel> pixels
    -uint width uint
    -uint height
  }
```

### Image Processing (imageprocessing)

Image processing module contains algorithms for enhancing images.

Layer: Service

```mermaid
classDiagram
  class Binning {
    +Binning(uint blockWidth, uint blockHeight)
    +XrayImage calculate(XrayImage image)
    -uint blockWidth
    -uint blockHeight
  }
```

### Image Storing (imagestoring)

Image storing module is responsible in reading and writing images.

Layer: Infrastructure

```mermaid
classDiagram
  class ImageReader {
    +ImageReader()
    +XrayImage read(string url)
  }
```

```mermaid
classDiagram
  class ImageWriter {
    +ImageWriter()
    +bool write(string url, XRayImage image)
  }
```

### User interface (app)

User interface contains view for the application.

Layer: Presentation

```mermaid
classDiagram
  class ImageItem {
    +QUuid id
    +QUrl url
    +bool selected
  }
```

```mermaid
classDiagram
  class ImageListModel {
    +int rowCount(QModelIndex parent)
    +QVariant data(QModelIndex index, int role)
    +bool setData(QModelIndex index, QVariant value, int role)
    +ItemFlags flags(QModelIndex index)
    +QHash<int, QByteArray> rolenames()
    +MainModel mainModel()
    +setMainModel(MainModel mainModel)
    -MainModel mainModel
  }
```

```mermaid
classDiagram
  class ImageProvider {
    +ImageProvider(MainModel mainModel)
    +QPixmap requestPixmap(Qstring id, QSize size, QSize requestedSize)
    -MainModel mainModel
  }
```

```mermaid
classDiagram
  class MainModel {
    +MainModel(QObject parent)
    +QVector<ImageItem> items()
    +bool setItemAt(int index, ImageItem item)
    +preItemAppended()
    +postItemAppended()
    +preItemRemoved(int index)
    +postItemRemoved()
    +importImages(QList<QUrl> files)
    +exportImages(QUrl folder)
    +doBinning()
    +removeImages()
    -QVector<ImageItem> items
  }
```

### Unit tests (tests)

Unit tests are written for domain objects and services.

- BinningTests
- XrayImageTests