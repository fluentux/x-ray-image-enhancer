#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "imagelistmodel.h"
#include "imageprovider.h"
#include "mainmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<ImageListModel>("ImageList", 1, 0, "ImageListModel");
    qmlRegisterUncreatableType<MainModel>("Main", 1, 0, "MainModel",
        QStringLiteral("MainModel should not be created in QML"));

    MainModel mainModel;

    engine.addImageProvider(QLatin1String("images"), mainModel.getImageProvider());
    engine.rootContext()->setContextProperty(QStringLiteral("mainModelContext"), &mainModel);

    engine.load(QUrl(QStringLiteral("qrc:/XrayImageEnhancer/main.qml")));

    return app.exec();
}
