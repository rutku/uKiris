#include "tablowidget.h"
#include "cisimmodeli.h"
#include "diagramItem.h"

#include <QDebug>
#include <QMouseEvent>

TabloWidget::TabloWidget(QWidget *parent)
    : QTableWidget(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

void TabloWidget::tabloyaCisimEkle(CisimModeli *cisimModeli)
{

    cisimModelListesi.append(cisimModeli);

    insertRow(rowCount());

    setItem(rowCount() - 1,0,new QTableWidgetItem(cisimModeli->tipIsmiAl()));
    switch (cisimModeli->tipAl()) {
    case DiagramItem::Kiris:
        setItem(rowCount() - 1,3,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangciKonumuAl())));
        setItem(rowCount() - 1,4,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisKonumuAl())));
        break;
    case DiagramItem::SabitMesnet:
        setItem(rowCount() - 1,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    case DiagramItem::HareketliMesnet:
        setItem(rowCount() - 1,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    case DiagramItem::AnkastreMesnet:
        setItem(rowCount() - 1,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    default:
        break;
    }

//    setItem(rowCount() - 1,2,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaYukuAl())));
//    setItem(rowCount() - 1,5,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangicYukuAl())));
//    setItem(rowCount() - 1,6,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisYukuAl())));

}

void TabloWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (selectedItems().isEmpty()) {
        return;
    }

    qDebug() << cisimModelListesi.at(selectedItems().first()->row())->tipAl();

    QTableWidget::mouseDoubleClickEvent(event);
}

