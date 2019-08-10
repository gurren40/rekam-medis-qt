#ifndef REKAMMEDISFILTER_H
#define REKAMMEDISFILTER_H

#include <QSortFilterProxyModel>

class RekamMedisFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(bool isDescending READ getDescending WRITE setDescendingOrder NOTIFY descendingSig)

signals:
    void descendingSig();

public:
    RekamMedisFilter(QObject* parent = nullptr);

    Q_INVOKABLE void setFilterString(QString string);

    bool getDescending();

    Q_INVOKABLE void setDescendingOrder(bool checked);

private:
    bool isDescending;
};

#endif // REKAMMEDISFILTER_H
