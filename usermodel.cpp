#include "usermodel.h"
#include "userlist.h"

UserModel::UserModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int UserModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant UserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const UserItem item = mList->items().at(index.row());
    switch (role) {
    case IDRole:
        return QVariant(item.ID);
    case NIKRole:
        return QVariant(item.NIK);
    case NamaRole:
        return QVariant(item.Nama);
    case UmurRole:
        return QVariant(item.Umur);
    case JKRole:
        return QVariant(item.JK);
    case AlamatRole:
        return QVariant(item.Alamat);
    }

    return QVariant();
}

bool UserModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    UserItem item = mList->items().at(index.row());
    switch (role) {
    case IDRole:
        item.ID = value.toInt();
        break;
    case NIKRole:
        item.NIK = value.toString();
        break;
    case NamaRole:
        item.Nama = value.toString();
        break;
    case UmurRole:
        item.Umur = value.toInt();
        break;
    case JKRole:
        item.JK = value.toBool();
        break;
    case AlamatRole:
        item.Alamat = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags UserModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> UserModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IDRole] = "ID";
    names[NIKRole] = "NIK";
    names[NamaRole] = "Nama";
    names[UmurRole] = "Umur";
    names[JKRole] = "JK";
    names[AlamatRole] = "Alamat";
    return names;
}

UserList *UserModel::list() const
{
    return mList;
}

void UserModel::setList(UserList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //append item
        connect(mList, &UserList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &UserList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        //remove item
        connect(mList, &UserList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &UserList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &UserList::itemDataChanged, this, [=](int first, int last) {
            emit dataChanged(index(first),index(last),QVector<int>());
        });

        //setted pin value
        connect(mList, &UserList::preItemDataChanged, this, [=](){
            beginResetModel();
        });
        connect(mList, &UserList::postItemDataChanged, this, [=](){
            endResetModel();
        });
    }

    endResetModel();
}
