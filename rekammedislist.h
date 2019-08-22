#ifndef REKAMMEDISLIST_H
#define REKAMMEDISLIST_H

#include <QObject>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>
#include <QIODevice>
#include <QFile>

#include "user.h"

struct RekamMedisItem{
    int ID;
    QString Nama;
    double Tegangan;
    double mAs;
    double mGy;
    double OutputRadiasi;
    double ESAK;
    double DAP;
    QString imageFile;
    QString datecreated;
};

class RekamMedisList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant ID READ getID NOTIFY itemChanged)
    Q_PROPERTY(QVariant Nama READ getNama NOTIFY itemChanged)
    Q_PROPERTY(QVariant Tegangan READ getTegangan NOTIFY itemChanged)
    Q_PROPERTY(QVariant mAs READ getmAs NOTIFY itemChanged)
    Q_PROPERTY(QVariant mGy READ getmGy NOTIFY itemChanged)
    Q_PROPERTY(QVariant OutputRadiasi READ getOutputRadiasi NOTIFY itemChanged)
    Q_PROPERTY(QVariant ESAK READ getESAK NOTIFY itemChanged)
    Q_PROPERTY(QVariant DAP READ getDAP NOTIFY itemChanged)
    Q_PROPERTY(QVariant imageFile READ getimageFile NOTIFY itemChanged)
    Q_PROPERTY(QVariant datecreated READ getDateCreated NOTIFY itemChanged)

public:
    explicit RekamMedisList(QObject *parent = nullptr);

    QVector<RekamMedisItem> items() const;
    bool setItemAt(int index, const RekamMedisItem &item);

    void setUser(User *value);

signals:

    //list signal
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemDataChanged();
    void postItemDataChanged();

    void itemDataChanged(int first, int last);

    //misc signal
    void notify(QString status);

    //items
    void itemChanged();

public slots:

    //items
    int getID();
    QString getNama();
    double getTegangan();
    double getmAs();
    double getmGy();
    double getOutputRadiasi();
    double getESAK();
    double getDAP();
    QString getimageFile();
    QString getDateCreated();

    //sets & gets
    void setNetworkManager(QNetworkAccessManager *netmgr);
    void setRekamMedisList(QJsonArray jsonArr);
    void setRekamMedis(QJsonObject jsonObj);

    //ambil list rekam medis
    void getRekamMedisList(QVariant userID);
    void gotRekamMedisList();

    //ambil rekam medis
    void getRekamMedis(QVariant id);
    void gotRekamMedis();

    //buat rekam medis
    void createNewRekamMedis(QVariant Nama, QVariant Tegangan, QVariant mAs, QVariant mGy, QVariant OutputRadiasi, QVariant ESAK, QVariant DAP, QVariant ImageFile);
    void rekamMedisCreated();

    //hapus data
    void clearItemsData();

private:
    QVector<RekamMedisItem> mItems;
    RekamMedisItem mItem;
    QNetworkAccessManager *m_networkManager;
    User *user;
};

#endif // REKAMMEDISLIST_H
