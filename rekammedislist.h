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
    QString NIK;
    int Umur;
    bool JK;
    QString Alamat;
    double Tegangan;
    double mAs;
    double mGy;
    double OutputRadiasi;
    double ESAK;
    double DAP;
    QString imageFile;
};

class RekamMedisList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant ID READ getID NOTIFY itemChanged)
    Q_PROPERTY(QVariant Nama READ getNama NOTIFY itemChanged)
    Q_PROPERTY(QVariant NIK READ getNIK NOTIFY itemChanged)
    Q_PROPERTY(QVariant Umur READ getUmur NOTIFY itemChanged)
    Q_PROPERTY(QVariant JK READ getJK NOTIFY itemChanged)
    Q_PROPERTY(QVariant Alamat READ getAlamat NOTIFY itemChanged)
    Q_PROPERTY(QVariant Tegangan READ getTegangan NOTIFY itemChanged)
    Q_PROPERTY(QVariant mAs READ getmAs NOTIFY itemChanged)
    Q_PROPERTY(QVariant mGy READ getmGy NOTIFY itemChanged)
    Q_PROPERTY(QVariant OutputRadiasi READ getOutputRadiasi NOTIFY itemChanged)
    Q_PROPERTY(QVariant ESAK READ getESAK NOTIFY itemChanged)
    Q_PROPERTY(QVariant DAP READ getDAP NOTIFY itemChanged)
    Q_PROPERTY(QVariant imageFile READ getimageFile NOTIFY itemChanged)

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
    QString getNIK();
    int getUmur();
    bool getJK();
    QString getAlamat();
    double getTegangan();
    double getmAs();
    double getmGy();
    double getOutputRadiasi();
    double getESAK();
    double getDAP();
    QString getimageFile();

    //sets & gets
    void setNetworkManager(QNetworkAccessManager *netmgr);
    void setRekamMedisList(QJsonArray jsonArr);
    void setRekamMedis(QJsonObject jsonObj);

    //ambil list rekam medis
    void getRekamMedisList();
    void gotRekamMedisList();

    //ambil rekam medis
    void getRekamMedis(QVariant id);
    void gotRekamMedis();

    //buat rekam medis
    void createNewRekamMedis(QVariant Nama, QVariant NIK, QVariant Umur, QVariant JK, QVariant Alamat, QVariant Tegangan, QVariant mAs, QVariant mGy, QVariant OutputRadiasi, QVariant ESAK, QVariant DAP, QVariant ImageFile);
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
