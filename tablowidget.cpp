#include "tablowidget.h"
#include "cisimmodeli.h"
#include "diagramItem.h"
#include "KMDiagramSahnesi.h"

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
    tabloyaEkle(rowCount()-1,cisimModeli);
}

void TabloWidget::tabloyuGuncelle(CisimModeli *cisimModeli)
{   
    tabloyaEkle(selectedItems().first()->row(),cisimModeli);
}

void TabloWidget::diagramCiz()
{
    emit kesmeDiagramiCiz(cisimModelListesi);
    emit momentDiagramiCiz(cisimModelListesi);
}

void TabloWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (selectedItems().isEmpty()) {
        return;
    }
    emit cisimDuzenle(cisimModelListesi.at(selectedItems().first()->row()));

    QTableWidget::mouseDoubleClickEvent(event);
}

void TabloWidget::tabloyaEkle(int satir, CisimModeli *cisimModeli)
{
    setItem(satir,0,new QTableWidgetItem(cisimModeli->tipIsmiAl()));
    switch (cisimModeli->tipAl()) {
    case DiagramItem::Kiris:
        setItem(satir,3,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangciKonumuAl())));
        setItem(satir,4,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisKonumuAl())));
        break;
    case DiagramItem::SabitMesnet:
        setItem(satir,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    case DiagramItem::HareketliMesnet:
        setItem(satir,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    case DiagramItem::AnkastreMesnet:
        setItem(satir,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    case DiagramItem::TekilKuvvet:
        setItem(satir,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        setItem(satir,2,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKuvvetiAl())));
        break;
    case DiagramItem::YayiliKuvvet:
        setItem(satir,3,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangciKonumuAl())));
        setItem(satir,4,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisKonumuAl())));
        setItem(satir,5,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangicKuvvetiAl())));
        setItem(satir,6,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisKuvvetiAl())));
        break;
    case DiagramItem::Moment:
        setItem(satir,1,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        setItem(satir,7,new QTableWidgetItem(tr("%1").arg(cisimModeli->momentAl())));
        break;
    default:
        break;
    }
}

