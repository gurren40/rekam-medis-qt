#ifndef USERMODEL_H
#define USERMODEL_H

#include <QAbstractListModel>

class UserList;

class UserModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(UserList *list READ list WRITE setList)

public:
    explicit UserModel(QObject *parent = nullptr);

    enum {
        IDRole = Qt::UserRole,
        NIKRole,
        NamaRole,
        UmurRole,
        JKRole,
        AlamatRole,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    UserList *list() const;
    void setList(UserList *list);

private:
    UserList *mList;
};

#endif // USERMODEL_H
