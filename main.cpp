#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QSignalMapper>
#include <QIcon>
#include <QMetaType>
#include <QObject>
#include <QtSvg>
#include <QFileDialog>

#include "user.h"
#include "rekammedislist.h"
#include "rekammedismodel.h"
#include "rekammedisfilter.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Rekam Medis");
    QGuiApplication::setOrganizationDomain("rekam-medis.web.id");
    QGuiApplication::setOrganizationName("Informatika Undip");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //init all object
    QNetworkAccessManager networkManager;
    User user;
    RekamMedisList rmlist;
    RekamMedisModel rmmodel;
    RekamMedisFilter rmfilter;
    user.setNetworkManager(&networkManager);
    rmlist.setNetworkManager(&networkManager);
    rmlist.setUser(&user);

    rmmodel.setList(&rmlist);
    rmfilter.setSourceModel(&rmmodel);
    rmfilter.setFilterRole(RekamMedisModel::NamaRole);
    rmfilter.setSortRole(RekamMedisModel::NamaRole);


    //misc
    QIcon::setThemeName("witchcraft");
    qRegisterMetaType<QJsonObject>();

    //qmlRegisterType<RekamMedisModel>("RekamMedis", 1, 0, "RekamMedisModel");
    //qmlRegisterType<RekamMedisFilter>("RekamMedis", 1, 0, "RekamMedisFilter");
    qmlRegisterUncreatableType<RekamMedisList>("RekamMedis", 1, 0, "RekamMedisList",
        QStringLiteral("RekamMedisList should not be created in QML"));

    engine.rootContext()->setContextProperty(QStringLiteral("user"), &user);
    engine.rootContext()->setContextProperty(QStringLiteral("rekamMedisLists"), &rmlist);
    engine.rootContext()->setContextProperty(QStringLiteral("rekamMedisFilter"), &rmfilter);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
