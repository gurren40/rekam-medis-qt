#include "rekammedislist.h"

RekamMedisList::RekamMedisList(QObject *parent) : QObject(parent)
{
    RekamMedisItem item;
    item.ID = 1;
    item.Nama = "Data1";
    item.NIK = "12345";
    item.Umur = 21;
    item.JK = true;
    item.Tegangan = 22;
    item.mAs = 23;
    item.mGy = 24;
    item.OutputRadiasi = 25;
    item.ESAK = 26;
    item.DAP = 27;
    item.imageFile = 28;
    mItems.append(item);
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
        item.NIK = jsonItem["NIK"].toString();
        item.Umur = jsonItem["Umur"].toInt();
        item.JK = jsonItem["JK"].toBool();
        item.Tegangan = jsonItem["Tegangan"].toDouble();
        item.mAs = jsonItem["mAs"].toDouble();
        item.mGy = jsonItem["mGy"].toDouble();
        item.OutputRadiasi = jsonItem["OutputRadiasi"].toDouble();
        item.ESAK = jsonItem["Esak"].toDouble();
        item.DAP = jsonItem["DAP"].toDouble();
        item.imageFile = jsonItem["imageName"].toString();
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
            item.NIK = jsonItem["NIK"].toString();
            item.Umur = jsonItem["Umur"].toInt();
            item.JK = jsonItem["JK"].toBool();
            item.Tegangan = jsonItem["Tegangan"].toDouble();
            item.mAs = jsonItem["mAs"].toDouble();
            item.mGy = jsonItem["mGy"].toDouble();
            item.OutputRadiasi = jsonItem["OutputRadiasi"].toDouble();
            item.ESAK = jsonItem["Esak"].toDouble();
            item.DAP = jsonItem["DAP"].toDouble();
            item.imageFile = jsonItem["imageName"].toString();
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
    mItem.NIK = jsonObj["NIK"].toString();
    mItem.Umur = jsonObj["Umur"].toInt();
    mItem.JK = jsonObj["JK"].toBool();
    mItem.Tegangan = jsonObj["Tegangan"].toDouble();
    mItem.mAs = jsonObj["mAs"].toDouble();
    mItem.mGy = jsonObj["mGy"].toDouble();
    mItem.OutputRadiasi = jsonObj["OutputRadiasi"].toDouble();
    mItem.ESAK = jsonObj["Esak"].toDouble();
    mItem.DAP = jsonObj["DAP"].toDouble();
    mItem.imageFile = jsonObj["imageName"].toString();
    emit itemChanged();
}

void RekamMedisList::getRekamMedisList()
{
    QNetworkReply *rekamMedisListReply;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QString urlString = user->getDomain()+"/RekamMedisAPI/getAll";
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("keys="+user->getKey().toUtf8());
    rekamMedisListReply = m_networkManager->post(request,data);
    connect(rekamMedisListReply,&QNetworkReply::finished,this,&RekamMedisList::gotRekamMedisList);
}

void RekamMedisList::gotRekamMedisList()
{
    QNetworkReply *rekamMedisListReply = qobject_cast<QNetworkReply *>(sender());
    QByteArray replyData = rekamMedisListReply->readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(replyData));
    if(jsonDoc.object().contains("status")){
        emit notify(jsonDoc.object()["status"].toString());
        if(jsonDoc.object()["status"].toString() == "expired"){
            user->delKey();
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
    QString urlString = user->getDomain()+"/RekamMedisAPI/get/"+QString::number(id.toInt()).toUtf8();
    QUrl url(urlString);
    request.setUrl(url);
    QByteArray data;
    data.append("keys="+user->getKey().toUtf8());
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

void RekamMedisList::createNewRekamMedis(QVariant Nama, QVariant NIK, QVariant Umur, QVariant JK, QVariant Alamat, QVariant Tegangan, QVariant mAs, QVariant mGy, QVariant OutputRadiasi, QVariant ESAK, QVariant DAP, QVariant ImageFile)
{
    QNetworkReply *createRekamMedisReply;
    QNetworkRequest request;
    QUrl fileurl(ImageFile.toString());
    QFile file(fileurl.toString(QUrl::RemoveScheme | QUrl::PreferLocalFile | QUrl::FullyEncoded));
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
        int jkvalue;
        if(JK.toBool()){
            jkvalue = 1;
        }
        else{
            jkvalue = 0;
        }
        data.append("keys="+user->getKey().toUtf8()+"&");
        data.append("Nama="+Nama.toString().toUtf8()+"&");
        data.append("NIK="+NIK.toString().toUtf8()+"&");
        data.append("Umur="+Umur.toString().toUtf8()+"&");
        data.append("JK="+QString::number(jkvalue).toUtf8()+"&");
        data.append("Alamat="+Alamat.toString().toUtf8()+"&");
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

void RekamMedisList::setUser(User *value)
{
    user = value;
}

int RekamMedisList::getID()
{
    return mItem.ID;
}

QString RekamMedisList::getNama()
{
    return mItem.Nama;
}

QString RekamMedisList::getNIK()
{
    return mItem.NIK;
}

int RekamMedisList::getUmur()
{
    return mItem.Umur;
}

bool RekamMedisList::getJK()
{
    return mItem.JK;
}

QString RekamMedisList::getAlamat()
{
    return mItem.Alamat;
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
