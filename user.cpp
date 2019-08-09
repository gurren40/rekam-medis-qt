#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

void User::setNetworkManager(QNetworkAccessManager *netmgr)
{
    m_networkManager = netmgr;
}

void User::setKey(QString key)
{
    QSettings setting;
    setting.setValue("keys",key);
    emit keySig();
    emit isLoggedInSig();
}

void User::delKey()
{
    QSettings setting;
    setting.remove("keys");
    emit keySig();
    emit isLoggedInSig();
}

QString User::getKey()
{
    QSettings setting;
    if(setting.contains("keys")){
        return setting.value("keys").toString();
    }
    else{
        return "none";
    }
}

void User::setUsername(QString username)
{
    QSettings setting;
    setting.setValue("username",username);
    emit setUsernameSig();
}

QString User::getUsername()
{
    QSettings setting;
    if(setting.contains("username")){
        return setting.value("username").toString();
    }
    else{
        return "none";
    }
}

bool User::getIsLoggedIn()
{
    QSettings setting;
    if(setting.contains("keys")){
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
        return "http://localhost:8000";
    }
}


void User::createKey(QVariant username, QVariant password)
{
    QNetworkReply *m_networkAuthKeyReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString urlString = getDomain()+"/UserAPI/authkey";
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("username="+username.toString().toUtf8()+"&");
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

void User::createUser(QVariant username, QVariant password)
{
    QNetworkReply *m_networkCreateUserReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString urlString = getDomain()+"/UserAPI/create";
    QUrl url(urlString);
    request.setUrl(url);
    m_networkCreateUserReply = m_networkManager->post(request,"username=\""+username.toString().toUtf8()+"\"&password=\""+password.toString().toUtf8()+"\"");
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

void User::logOut(){
    delKey();
}
