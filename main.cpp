#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QSignalMapper>
#include <QIcon>
#include <QMetaType>
#include <QObject>

#include "user.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("Rekam Medis");
    QApplication::setOrganizationDomain("rekam-medis.web.id");
    QApplication::setOrganizationName("Informatika Undip");
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //init all object
    QNetworkAccessManager networkManager;
    User user;
    user.setNetworkManager(&networkManager);

    engine.rootContext()->setContextProperty(QStringLiteral("user"), &user);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
