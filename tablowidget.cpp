#include "tablowidget.h"

TabloWidget::TabloWidget(QWidget *parent)
    : QTableWidget(parent)
{

}

void TabloWidget::cisimEkle(int tip, int noktaKonumu, int noktaYuku,
                             int baslangicKonumu, int bitisKonumu,
                             int baslangicYuku, int bitisYuku)
{
    insertRow(rowCount());
    setItem(rowCount() - 1,0,new QTableWidgetItem(tr("%1").arg(tip)));
    setItem(rowCount() - 1,1,new QTableWidgetItem(tr("%1").arg(noktaKonumu)));
    setItem(rowCount() - 1,2,new QTableWidgetItem(tr("%1").arg(noktaYuku)));
    setItem(rowCount() - 1,3,new QTableWidgetItem(tr("%1").arg(baslangicKonumu)));
    setItem(rowCount() - 1,4,new QTableWidgetItem(tr("%1").arg(bitisKonumu)));
    setItem(rowCount() - 1,5,new QTableWidgetItem(tr("%1").arg(baslangicYuku)));
    setItem(rowCount() - 1,6,new QTableWidgetItem(tr("%1").arg(bitisYuku)));

}
