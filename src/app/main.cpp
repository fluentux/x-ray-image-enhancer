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

    engine.addImageProvider(QLatin1String("colors"), new ImageProvider(&mainModel));
    engine.rootContext()->setContextProperty(QStringLiteral("mainModelTest"), &mainModel);

    engine.load(QUrl(QStringLiteral("qrc:/XRayImageEnhancer/main.qml")));

    return app.exec();
}
