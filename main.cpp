#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QSignalMapper>
#include <QIcon>
#include <QMetaType>
#include <QObject>
#include <QtSvg>

#include "user.h"
#include "rekammedislist.h"
#include "rekammedismodel.h"

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
    RekamMedisList rmlist;
    user.setNetworkManager(&networkManager);
    rmlist.setNetworkManager(&networkManager);
    rmlist.setUser(&user);

    //misc
    QIcon::setThemeName("witchcraft");
    qRegisterMetaType<QJsonObject>();

    qmlRegisterType<RekamMedisModel>("RekamMedis", 1, 0, "RekamMedisModel");
    qmlRegisterUncreatableType<RekamMedisList>("RekamMedis", 1, 0, "RekamMedisList",
        QStringLiteral("RekamMedisList should not be created in QML"));

    engine.rootContext()->setContextProperty(QStringLiteral("user"), &user);
    engine.rootContext()->setContextProperty(QStringLiteral("rekamMedisLists"), &rmlist);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
