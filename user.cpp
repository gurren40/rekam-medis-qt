#include "user.h"

User::User(QObject *parent) : QObject(parent)
{
    notifyMessage = "";
    Nama = "";
    Umur = 0;
    JK = false;
    Alamat = "";
}

void User::setNetworkManager(QNetworkAccessManager *netmgr)
{
    m_networkManager = netmgr;
}

void User::setKey(QString key)
{
    QSettings setting;
    setting.setValue("key",key);
    emit keySig();
    emit isLoggedInSig();
}

void User::delKey()
{
    QSettings setting;
    setting.remove("key");
    emit keySig();
    emit isLoggedInSig();
}

QString User::getKey()
{
    QSettings setting;
    if(setting.contains("key")){
        return setting.value("key").toString();
    }
    else{
        return "none";
    }
}

void User::setNIK(QString NIK)
{
    QSettings setting;
    setting.setValue("NIK",NIK);
    emit userDataSig();
}

QString User::getNIK()
{
    QSettings setting;
    if(setting.contains("NIK")){
        return setting.value("NIK").toString();
    }
    else{
        return "none";
    }
}

QString User::getNama()
{
    return Nama;
}

int User::getUmur()
{
    return Umur;
}

bool User::getJK()
{
    return JK;
}

QString User::getAlamat()
{
    return Alamat;
}

bool User::getIsLoggedIn()
{
    QSettings setting;
    if(setting.contains("key")){
        return true;
    }
    else{
        return false;
    }
}

void User::setDomain(QString domain)
{
    QSettings setting;
    setting.setValue("domain",domain);
    emit domainSig();
}

QString User::getDomain()
{
    QSettings setting;
    if(setting.contains("domain")){
        return setting.value("domain").toString();
    }
    else{
        return "http://rekam-medis.southeastasia.cloudapp.azure.com";
    }
}


void User::createKey(QVariant NIK, QVariant password)
{
    QNetworkReply *m_networkAuthKeyReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString urlString = getDomain()+"/UserAPI/authkey";
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("NIK="+NIK.toString().toUtf8()+"&");
    data.append("password="+password.toString().toUtf8());
    m_networkAuthKeyReply = m_networkManager->post(request,data);
    connect(m_networkAuthKeyReply,&QNetworkReply::finished,this,&User::keyCreated);
}

void User::keyCreated()
{
    QNetworkReply *m_networkAuthKeyReply = qobject_cast<QNetworkReply *>(sender());
    QByteArray replyData = m_networkAuthKeyReply->readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData));
    if(jsonDoc.object().contains("status")){
        emit notify(jsonDoc.object()["status"].toString());
        if(jsonDoc.object()["status"].toString() == "expired"){
            delKey();
        }
    }
    else if(jsonDoc.object().contains("key")){
        setKey(jsonDoc.object()["key"].toString());
    }
    m_networkAuthKeyReply->disconnect();
    m_networkAuthKeyReply->deleteLater();
}

void User::createUser(QVariant NIK, QVariant password, QVariant Nama, QVariant Umur, QVariant JK, QVariant Alamat)
{
    QNetworkReply *m_networkCreateUserReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString urlString = getDomain()+"/UserAPI/create";
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("NIK="+NIK.toString().toUtf8()+"&");
    data.append("password="+password.toString().toUtf8()+"&");
    data.append("Nama="+Nama.toString().toUtf8()+"&");
    data.append("Umur="+Umur.toString().toUtf8()+"&");
    data.append("JK="+JK.toString().toUtf8()+"&");
    data.append("Alamat="+Alamat.toString().toUtf8());
    m_networkCreateUserReply = m_networkManager->post(request,data);
    connect(m_networkCreateUserReply,&QNetworkReply::finished,this,&User::userCreated);
}

void User::userCreated()
{
    QNetworkReply *m_networkCreateUserReply = qobject_cast<QNetworkReply *>(sender());
    QByteArray replyData = m_networkCreateUserReply->readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData));
    emit notify(jsonDoc.object()["status"].toString());
    m_networkCreateUserReply->disconnect();
    m_networkCreateUserReply->deleteLater();
}

void User::getUserInfo()
{
    QNetworkReply *userInfoReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString urlString = getDomain()+"/UserAPI/get/";
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("key="+getKey().toUtf8());
    userInfoReply = m_networkManager->post(request,data);
    connect(userInfoReply,&QNetworkReply::finished,this,&User::gotUserInfo);
}

void User::gotUserInfo()
{
    QNetworkReply *userInfoReply = qobject_cast<QNetworkReply *>(sender());
    QByteArray replyData = userInfoReply->readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData));
    if(jsonDoc.object().contains("status")){
        emit notify(jsonDoc.object()["status"].toString());
        if(jsonDoc.object()["status"].toString() == "expired"){
            delKey();
        }
    }
    else{
        Nama = jsonDoc.object()["Nama"].toString();
        Umur = jsonDoc.object()["Umur"].toInt();
        if(jsonDoc.object()["JK"].toInt() == 1){
            JK = true;
        }
        else {
            JK = false;
        }
        Alamat = jsonDoc.object()["Alamat"].toString();
        emit userDataSig();
    }
    userInfoReply->disconnect();
    userInfoReply->deleteLater();
}

void User::notify(QString status)
{
    notifyMessage = status;
    emit notifySig();
}

QString User::getNotify()
{
    return notifyMessage;
}

bool User::enableNotify()
{
    QSettings setting;
    if(!setting.contains("enableInternalNotification")){
        return true;
    }
    else{
        return setting.value("enableInternalNotification").toBool();
    }
}

void User::setEnableNotify(QVariant notify)
{
    QSettings setting;
    setting.setValue("enableInternalNotification",notify.toBool());
    emit enableNotifySig();
}

void User::logOut(){
    delKey();
}

void User::setAO(QVariant value)
{
    QSettings setting;
    setting.setValue("advancedOption",value.toBool());
    emit sigAO();
}

bool User::getAO()
{
    QSettings setting;
    if(!setting.contains("advancedOption")){
        return false;
    }
    else{
        return setting.value("advancedOption").toBool();
    }
}
