#ifndef REKAMMEDISMODEL_H
#define REKAMMEDISMODEL_H

#include <QAbstractListModel>

class RekamMedisList;

class RekamMedisModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(RekamMedisList *list READ list WRITE setList)

public:
    explicit RekamMedisModel(QObject *parent = nullptr);

    enum {
        IDRole = Qt::UserRole,
        NamaRole,
        TeganganRole,
        mAsRole,
        mGyRole,
        OutputRadiasiRole,
        EsakRole,
        DAPRole,
        imageFileRole,
        datecreatedRole,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    RekamMedisList *list() const;
    void setList(RekamMedisList *list);

private:
    RekamMedisList *mList;
};

#endif // REKAMMEDISMODEL_H
