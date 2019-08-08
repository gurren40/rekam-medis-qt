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
    Q_PROPERTY(QString keys READ getKey WRITE setKey RESET delKey NOTIFY keySig)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY setUsernameSig)
    Q_PROPERTY(bool isLoggedIn READ getIsLoggedIn NOTIFY isLoggedInSig)
    Q_PROPERTY(QString domain READ getDomain WRITE setDomain NOTIFY domainSig)

public:
    explicit User(QObject *parent = nullptr);

signals:
    //keys
    void keySig();

    //username
    void setUsernameSig();

    //isLoggedIn
    void isLoggedInSig();

    //domain
    void domainSig();

    //notifysignal
    void notify(QString status);

public slots:
    //bind network manager
    void setNetworkManager(QNetworkAccessManager *netmgr);

    //keys
    void setKey(QString key);
    void delKey();
    QString getKey();

    //username
    void setUsername(QString username);
    QString getUsername();

    //isLoggedIn
    bool getIsLoggedIn();

    //url
    void setDomain(QString domain);
    QString getDomain();

    //requestkey
    void createKey(QVariant username, QVariant password);
    void keyCreated();

    //createuser
    void createUser(QVariant username, QVariant password);
    void userCreated();

    //logout
    void logOut();

private:
    QNetworkAccessManager *m_networkManager;
};

#endif // USER_H
