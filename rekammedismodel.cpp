#include "rekammedismodel.h"
#include "rekammedislist.h"

RekamMedisModel::RekamMedisModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int RekamMedisModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant RekamMedisModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const RekamMedisItem item = mList->items().at(index.row());
    switch (role) {
    case IDRole:
        return QVariant(item.ID);
    case NamaRole:
        return QVariant(item.Nama);
    case TeganganRole:
        return QVariant(item.Tegangan);
    case mAsRole:
        return QVariant(item.mAs);
    case mGyRole:
        return QVariant(item.mGy);
    case OutputRadiasiRole:
        return QVariant(item.OutputRadiasi);
    case EsakRole:
        return QVariant(item.ESAK);
    case DAPRole:
        return QVariant(item.DAP);
    case imageFileRole:
        return QVariant(item.imageFile);
    case datecreatedRole:
        return QVariant(item.datecreated);
    }

    return QVariant();
}

bool RekamMedisModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    RekamMedisItem item = mList->items().at(index.row());
    switch (role) {
    case IDRole:
        item.ID = value.toInt();
        break;
    case NamaRole:
        item.Nama = value.toString();
        break;
    case TeganganRole:
        item.Tegangan = value.toDouble();
        break;
    case mAsRole:
        item.mAs = value.toDouble();
        break;
    case mGyRole:
        item.mGy = value.toDouble();
        break;
    case OutputRadiasiRole:
        item.OutputRadiasi = value.toDouble();
        break;
    case EsakRole:
        item.ESAK = value.toDouble();
        break;
    case DAPRole:
        item.DAP = value.toDouble();
        break;
    case imageFileRole:
        item.imageFile = value.toString();
        break;
    case datecreatedRole:
        item.datecreated = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags RekamMedisModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> RekamMedisModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IDRole] = "ID";
    names[NamaRole] = "Nama";
    names[mAsRole] = "mAs";
    names[mGyRole] = "mGy";
    names[OutputRadiasiRole] = "OutputRadiasi";
    names[EsakRole] = "Esak";
    names[DAPRole] = "DAP";
    names[imageFileRole] = "imageFile";
    names[datecreatedRole] = "datecreated";
    return names;
}

RekamMedisList *RekamMedisModel::list() const
{
    return mList;
}

void RekamMedisModel::setList(RekamMedisList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //append item
        connect(mList, &RekamMedisList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &RekamMedisList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        //remove item
        connect(mList, &RekamMedisList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &RekamMedisList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &RekamMedisList::itemDataChanged, this, [=](int first, int last) {
            emit dataChanged(index(first),index(last),QVector<int>());
        });

        //setted pin value
        connect(mList, &RekamMedisList::preItemDataChanged, this, [=](){
            beginResetModel();
        });
        connect(mList, &RekamMedisList::postItemDataChanged, this, [=](){
            endResetModel();
        });
    }

    endResetModel();
}
