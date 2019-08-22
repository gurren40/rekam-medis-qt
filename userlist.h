#ifndef USERLIST_H
#define USERLIST_H

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

struct UserItem{
    int ID;
    QString NIK;
    QString Nama;
    int Umur;
    bool JK;
    QString Alamat;
};

class UserList : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QVariant ID READ getID NOTIFY itemChanged)
//    Q_PROPERTY(QVariant NIK READ getNIK NOTIFY itemChanged)
//    Q_PROPERTY(QVariant Nama READ getNama NOTIFY itemChanged)
//    Q_PROPERTY(QVariant Umur READ getUmur NOTIFY itemChanged)
//    Q_PROPERTY(QVariant JK READ getJK NOTIFY itemChanged)
//    Q_PROPERTY(QVariant Alamat READ getAlamat NOTIFY itemChanged)

public:
    explicit UserList(QObject *parent = nullptr);

    QVector<UserItem> items() const;
    bool setItemAt(int index, const UserItem &item);

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
    //void itemChanged();

public slots:

    //items
//    int getID();
//    QString getNIK();
//    QString getNama();
//    int getUmur();
//    bool getJK();
//    QString getAlamat();

    //sets & gets
    void setNetworkManager(QNetworkAccessManager *netmgr);
    void setUserList(QJsonArray jsonArr);

    //ambil list rekam medis
    void getUserList();
    void gotUserList();

private:
    QVector<UserItem> mItems;
    QNetworkAccessManager *m_networkManager;
    User *user;
};

#endif // USERLIST_H
