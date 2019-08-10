#include "rekammedisfilter.h"

RekamMedisFilter::RekamMedisFilter(QObject *parent) : QSortFilterProxyModel (parent)
{
    setDescendingOrder(false);
}

void RekamMedisFilter::setFilterString(QString string)
{
    this->setFilterCaseSensitivity(Qt::CaseInsensitive);
    this->setFilterFixedString(string);
}

bool RekamMedisFilter::getDescending()
{
    return isDescending;
}

void RekamMedisFilter::setDescendingOrder(bool checked)
{
    if(checked){
        this->sort(0,Qt::DescendingOrder);
        isDescending = true;
    }
    else {
        this->sort(0,Qt::AscendingOrder);
        isDescending = false;
    }
    emit descendingSig();
}
