#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "imagefilterproxymodel.h"
#include "imagelistmodel.h"
#include "imageprovider.h"
#include "mainmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainModel mainModel;
    ImageListModel imageListModel;
    ImageFilterProxyModel imageFilterProxyModel;

    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<MainModel>("Main", 1, 0, "MainModel",
        QStringLiteral("MainModel should not be created in QML"));

    imageListModel.setMainModel(&mainModel);
    imageFilterProxyModel.setSourceModel(&imageListModel);

    engine.addImageProvider(QLatin1String("images"), mainModel.getImageProvider());
    engine.rootContext()->setContextProperty(QStringLiteral("mainModelContext"), &mainModel);
    engine.rootContext()->setContextProperty(QStringLiteral("imageListModelContext"), &imageListModel);
    engine.rootContext()->setContextProperty(QStringLiteral("imageFilterProxyModelContext"), &imageFilterProxyModel);

    engine.load(QUrl(QStringLiteral("qrc:/XrayImageEnhancer/main.qml")));

    return app.exec();
}
