#include "tablowidget.h"
#include "cisimmodeli.h"

TabloWidget::TabloWidget(QWidget *parent)
    : QTableWidget(parent)
{

}

void TabloWidget::cisimEkle(CisimModeli *cisimModeli)
{
    insertRow(rowCount());
    setItem(rowCount() - 1,0,new QTableWidgetItem(tr("%1").arg(cisimModeli->tipAl())));
    setItem(rowCount() - 1,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
    setItem(rowCount() - 1,2,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaYukuAl())));
    setItem(rowCount() - 1,3,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangciKonumuAl())));
    setItem(rowCount() - 1,4,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisKonumuAl())));
    setItem(rowCount() - 1,5,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangicYukuAl())));
    setItem(rowCount() - 1,6,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisYukuAl())));

}
