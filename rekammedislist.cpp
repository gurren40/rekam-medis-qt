#include "rekammedislist.h"

RekamMedisList::RekamMedisList(QObject *parent) : QObject(parent)
{
    RekamMedisItem item;
    item.ID = 0;
    item.Nama = "";
    item.Tegangan = 0;
    item.mAs = 0;
    item.mGy = 0;
    item.OutputRadiasi = 0;
    item.ESAK = 0;
    item.DAP = 0;
    item.imageFile = "none.jpg";
    item.datecreated = "";
    mItem = item;
}

QVector<RekamMedisItem> RekamMedisList::items() const
{
    return mItems;
}

bool RekamMedisList::setItemAt(int index, const RekamMedisItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void RekamMedisList::setNetworkManager(QNetworkAccessManager *netmgr)
{
    m_networkManager = netmgr;
}

void RekamMedisList::setRekamMedisList(QJsonArray jsonArr)
{
    for (int i=0;i<mItems.size();i++) {
        RekamMedisItem item = mItems.at(i);
        QJsonObject jsonItem = jsonArr.at(i).toObject();
        item.ID = jsonItem["ID"].toInt();
        item.Nama = jsonItem["Nama"].toString();
        item.Tegangan = jsonItem["Tegangan"].toDouble();
        item.mAs = jsonItem["mAs"].toDouble();
        item.mGy = jsonItem["mGy"].toDouble();
        item.OutputRadiasi = jsonItem["OutputRadiasi"].toDouble();
        item.ESAK = jsonItem["Esak"].toDouble();
        item.DAP = jsonItem["DAP"].toDouble();
        item.imageFile = jsonItem["imageName"].toString();
        item.datecreated = jsonItem["datecreated"].toString();
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
            RekamMedisItem item;
            QJsonObject jsonItem = jsonArr.at(mItems.size()).toObject();
            item.ID = jsonItem["ID"].toInt();
            item.Nama = jsonItem["Nama"].toString();
            item.Tegangan = jsonItem["Tegangan"].toDouble();
            item.mAs = jsonItem["mAs"].toDouble();
            item.mGy = jsonItem["mGy"].toDouble();
            item.OutputRadiasi = jsonItem["OutputRadiasi"].toDouble();
            item.ESAK = jsonItem["Esak"].toDouble();
            item.DAP = jsonItem["DAP"].toDouble();
            item.imageFile = jsonItem["imageName"].toString();
            item.datecreated = jsonItem["datecreated"].toString();
            emit preItemAppended();
            mItems.append(item);
            emit postItemAppended();
        }
    }
}

void RekamMedisList::setRekamMedis(QJsonObject jsonObj)
{
    mItem.ID = jsonObj["ID"].toInt();
    mItem.Nama = jsonObj["Nama"].toString();
    mItem.Tegangan = jsonObj["Tegangan"].toDouble();
    mItem.mAs = jsonObj["mAs"].toDouble();
    mItem.mGy = jsonObj["mGy"].toDouble();
    mItem.OutputRadiasi = jsonObj["OutputRadiasi"].toDouble();
    mItem.ESAK = jsonObj["Esak"].toDouble();
    mItem.DAP = jsonObj["DAP"].toDouble();
    mItem.imageFile = jsonObj["imageName"].toString();
    mItem.datecreated = jsonObj["datecreated"].toString();
    emit itemChanged();
}

void RekamMedisList::getRekamMedisList(QVariant userID)
{
    QNetworkReply *rekamMedisListReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString locationString;
    if(userID == 0){
        if(!user->getAmIAdmin()){
            locationString = "/RekamMedisAPI/getAll";
        }
        else {
            locationString = "/RekamMedisAPI";
        }
    }
    else {
        locationString = "/RekamMedisAPI/getByUser/"+userID.toString();
    }
    QString urlString = user->getDomain()+locationString;
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("key="+user->getKey().toUtf8());
    rekamMedisListReply = m_networkManager->post(request,data);
    connect(rekamMedisListReply,&QNetworkReply::finished,this,&RekamMedisList::gotRekamMedisList);
}

void RekamMedisList::gotRekamMedisList()
{
    QNetworkReply *rekamMedisListReply = qobject_cast<QNetworkReply *>(sender());
    QByteArray replyData = rekamMedisListReply->readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData));
    if(jsonDoc.object().contains("status")){
        if(jsonDoc.object()["status"].toString() != "nothing"){
            emit notify(jsonDoc.object()["status"].toString());
            if(jsonDoc.object()["status"].toString() == "expired"){
                user->delKey();
            }
        }
    }
    else if(jsonDoc.array().size()>0){
        setRekamMedisList(jsonDoc.array());
    }
    rekamMedisListReply->disconnect();
    rekamMedisListReply->deleteLater();
}

void RekamMedisList::getRekamMedis(QVariant id)
{
    QNetworkReply *rekamMedisReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString urlString = user->getDomain()+"/RekamMedisAPI/get/"+id.toString();
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("key="+user->getKey().toUtf8());
    rekamMedisReply = m_networkManager->post(request,data);
    connect(rekamMedisReply,&QNetworkReply::finished,this,&RekamMedisList::gotRekamMedis);
}

void RekamMedisList::gotRekamMedis()
{
    QNetworkReply *rekamMedisReply = qobject_cast<QNetworkReply *>(sender());
    QByteArray replyData = rekamMedisReply->readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData));
    if(jsonDoc.object().contains("status")){
        emit notify(jsonDoc.object()["status"].toString());
        if(jsonDoc.object()["status"].toString() == "expired"){
            user->delKey();
        }
    }
    else if(jsonDoc.object().contains("ID")){
        setRekamMedis(jsonDoc.object());
    }
    rekamMedisReply->disconnect();
    rekamMedisReply->deleteLater();
}

void RekamMedisList::createNewRekamMedis(QVariant userID, QVariant Nama, QVariant Tegangan, QVariant mAs, QVariant mGy, QVariant OutputRadiasi, QVariant ESAK, QVariant DAP, QVariant ImageFile)
{
    QNetworkReply *createRekamMedisReply;
    QNetworkRequest request;
    QUrl fileurl(ImageFile.toString());
    QFile file(fileurl.toString(QUrl::RemoveScheme | QUrl::PreferLocalFile | QUrl::PrettyDecoded));
    if(!file.open(QIODevice::ReadOnly)){
        emit notify("cannot open image file");
    }
    else {
        //QByteArray imageData = file.readAll();
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        QString urlString = user->getDomain()+"/RekamMedisAPI/create";
        QUrl url(urlString);
        request.setUrl(url);
        QByteArray data;
        data.append("key="+user->getKey().toUtf8()+"&");
        data.append("userID="+userID.toString().toUtf8()+"&");
        data.append("Nama="+Nama.toString().toUtf8()+"&");
        data.append("Tegangan="+Tegangan.toString().toUtf8()+"&");
        data.append("mAs="+mAs.toString().toUtf8()+"&");
        data.append("mGy="+mGy.toString().toUtf8()+"&");
        data.append("OutputRadiasi="+OutputRadiasi.toString().toUtf8()+"&");
        data.append("Esak="+ESAK.toString().toUtf8()+"&");
        data.append("DAP="+DAP.toString().toUtf8()+"&");
        //data.append("imageFile="+imageData.toBase64(QByteArray::Base64Encoding));
        data.append("imageFile="+file.readAll().toHex());
        createRekamMedisReply = m_networkManager->post(request,data);
        connect(createRekamMedisReply,&QNetworkReply::finished,this,&RekamMedisList::rekamMedisCreated);

//        QFile file2("/home/aditiya/yes.jpg");
//        file2.open(QIODevice::WriteOnly);
//        file2.write(QByteArray::fromBase64(file.readAll().toBase64()));
    }
}

void RekamMedisList::rekamMedisCreated()
{
    QNetworkReply *createRekamMedisReply = qobject_cast<QNetworkReply *>(sender());
    QByteArray replyData = createRekamMedisReply->readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData));
    if(jsonDoc.object().contains("status")){
        emit notify(jsonDoc.object()["status"].toString());
        if(jsonDoc.object()["status"].toString() == "expired"){
            user->delKey();
        }
    }
    createRekamMedisReply->disconnect();
    createRekamMedisReply->deleteLater();
}

void RekamMedisList::clearItemsData()
{
    while (mItems.size()>0) {
        emit preItemRemoved(mItems.size()-1);
        mItems.remove(mItems.size()-1);
        emit postItemRemoved();
    }
    RekamMedisItem item;
    item.ID = 0;
    item.Nama = "";
    item.Tegangan = 0;
    item.mAs = 0;
    item.mGy = 0;
    item.OutputRadiasi = 0;
    item.ESAK = 0;
    item.DAP = 0;
    item.imageFile = "none.jpg";
    item.datecreated = "";
    mItem = item;
    emit itemChanged();
}

void RekamMedisList::setUser(User *value)
{
    user = value;
    connect(this,&RekamMedisList::notify,user,&User::notify);
}

int RekamMedisList::getID()
{
    return mItem.ID;
}

QString RekamMedisList::getNama()
{
    return mItem.Nama;
}

double RekamMedisList::getTegangan()
{
    return mItem.Tegangan;
}

double RekamMedisList::getmAs()
{
    return mItem.mAs;
}

double RekamMedisList::getmGy()
{
    return mItem.mGy;
}

double RekamMedisList::getOutputRadiasi()
{
    return mItem.OutputRadiasi;
}

double RekamMedisList::getESAK()
{
    return mItem.ESAK;
}

double RekamMedisList::getDAP()
{
    return mItem.DAP;
}

QString RekamMedisList::getimageFile()
{
    return mItem.imageFile;
}

QString RekamMedisList::getDateCreated()
{
    return mItem.datecreated;
}
