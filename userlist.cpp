#include "userlist.h"

UserList::UserList(QObject *parent) : QObject(parent)
{

}

QVector<UserItem> UserList::items() const
{
    return mItems;
}

bool UserList::setItemAt(int index, const UserItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void UserList::setNetworkManager(QNetworkAccessManager *netmgr)
{
    m_networkManager = netmgr;
}

void UserList::setUserList(QJsonArray jsonArr)
{
    for (int i=0;i<mItems.size();i++) {
        UserItem item = mItems.at(i);
        QJsonObject jsonItem = jsonArr.at(i).toObject();
        item.ID = jsonItem["ID"].toInt();
        item.NIK = jsonItem["NIK"].toString();
        item.Nama = jsonItem["Nama"].toString();
        item.Umur = jsonItem["Umur"].toInt();
        if(jsonItem["JK"].toInt() == 1){
            item.JK = true;
        }
        else {
            item.JK = false;
        }
        item.Alamat = jsonItem["Alamat"].toString();
        mItems[i] = item;
        emit itemDataChanged(i,i);
    }

    if(mItems.size() > jsonArr.size()){
        while (mItems.size() > jsonArr.size()) {
            emit preItemRemoved(mItems.size() - 1);
            mItems.remove(mItems.size() - 1);
            emit postItemRemoved();
        }
    }
    else if(mItems.size() < jsonArr.size()){
        while(mItems.size() < jsonArr.size()){
            UserItem item;
            QJsonObject jsonItem = jsonArr.at(mItems.size()).toObject();
            item.ID = jsonItem["ID"].toInt();
            item.NIK = jsonItem["NIK"].toString();
            item.Nama = jsonItem["Nama"].toString();
            item.Umur = jsonItem["Umur"].toInt();
            if(jsonItem["JK"].toInt() == 1){
                item.JK = true;
            }
            else {
                item.JK = false;
            }
            item.Alamat = jsonItem["Alamat"].toString();
            emit preItemAppended();
            mItems.append(item);
            emit postItemAppended();
        }
    }
}

void UserList::getUserList()
{
    QNetworkReply *UserListReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString urlString = user->getDomain()+"/UserAPI/getAll";
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("key="+user->getKey().toUtf8());
    UserListReply = m_networkManager->post(request,data);
    connect(UserListReply,&QNetworkReply::finished,this,&UserList::gotUserList);
}

void UserList::gotUserList()
{
    QNetworkReply *UserListReply = qobject_cast<QNetworkReply *>(sender());
    QByteArray replyData = UserListReply->readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData));
    if(jsonDoc.object().contains("status")){
        emit notify(jsonDoc.object()["status"].toString());
        if(jsonDoc.object()["status"].toString() == "expired"){
            user->delKey();
        }
    }
    else if(jsonDoc.array().size()>0){
        setUserList(jsonDoc.array());
    }
    UserListReply->disconnect();
    UserListReply->deleteLater();
}

void UserList::setUser(User *value)
{
    user = value;
    connect(this,&UserList::notify,user,&User::notify);
}
