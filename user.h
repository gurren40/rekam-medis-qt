#ifndef USER_H
#define USER_H

#include <QObject>
#include <QSettings>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString key READ getKey WRITE setKey RESET delKey NOTIFY keySig)
    Q_PROPERTY(bool isLoggedIn READ getIsLoggedIn NOTIFY isLoggedInSig)
    Q_PROPERTY(QString domain READ getDomain WRITE setDomain NOTIFY domainSig)
    Q_PROPERTY(QString notify READ getNotify NOTIFY notifySig)
    Q_PROPERTY(bool enableNotify READ enableNotify WRITE setEnableNotify NOTIFY enableNotifySig)
    Q_PROPERTY(bool advancedOption READ getAO WRITE setAO NOTIFY sigAO)
    Q_PROPERTY(bool amIAdmin READ getAmIAdmin WRITE setIAmAdmin NOTIFY amIAdminSig)

    //the data
    Q_PROPERTY(QString NIK READ getNIK WRITE setNIK NOTIFY userDataSig)
    Q_PROPERTY(QString Nama READ getNama NOTIFY userDataSig)
    Q_PROPERTY(int Umur READ getUmur NOTIFY userDataSig)
    Q_PROPERTY(bool JK READ getJK NOTIFY userDataSig)
    Q_PROPERTY(QString Alamat READ getAlamat NOTIFY userDataSig)

public:
    explicit User(QObject *parent = nullptr);

signals:
    //key
    void keySig();

    //username
    void userDataSig();

    //isLoggedIn
    void isLoggedInSig();

    //domain
    void domainSig();

    void notifySig();

    void enableNotifySig();

    //if admin sig
    void amIAdminSig();

    //advanced option
    void sigAO();

public slots:
    //bind network manager
    void setNetworkManager(QNetworkAccessManager *netmgr);

    //key
    void setKey(QString key);
    void delKey();
    QString getKey();

    //username
    void setNIK(QString NIK);
    QString getNIK();
    QString getNama();
    int getUmur();
    bool getJK();
    QString getAlamat();

    //isLoggedIn
    bool getIsLoggedIn();

    //url
    void setDomain(QString domain);
    QString getDomain();

    //requestkey
    void createKey(QVariant NIK, QVariant password);
    void keyCreated();

    //createuser
    void createUser(QVariant NIK, QVariant password, QVariant Nama, QVariant Umur, QVariant JK, QVariant Alamat);
    void userCreated();

    //getUserInfo
    void getUserInfo();
    void gotUserInfo();

    void notify(QString status);
    QString getNotify();
    bool enableNotify();
    void setEnableNotify(QVariant notify);

    //logout
    void logOut();

    //advancedOption
    void setAO(QVariant value);
    bool getAO();

    //amIadmin
    bool getAmIAdmin();
    void setIAmAdmin(bool value);

private:
    QNetworkAccessManager *m_networkManager;
    QString notifyMessage;
    QString Nama;
    int Umur;
    bool JK;
    QString Alamat;
};

#endif // USER_H
