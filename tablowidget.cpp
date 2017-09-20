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

void TabloWidget::cisimSil()
{
    if (selectedItems().isEmpty()) {
        return;
    }
    bool tamam;
    QString tipIsmi = selectedItems().first()->text();
    int sira = selectedItems().at(1)->text().toInt(&tamam);

    for (int i = 0; i < cisimModelListesi.size(); i++) {
        if (cisimModelListesi.at(i)->tipIsmiAl() == tipIsmi &&
                cisimModelListesi.at(i)->siraAl() == sira) {
            emit Sil(cisimModelListesi.at(i));
            removeRow(selectedItems().first()->row());
            cisimModelListesi.removeAt(i);
        }
    }
}

void TabloWidget::tabloyaCisimEkle(CisimModeli *cisimModeli)
{

    siraAl(cisimModeli);
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
    setItem(satir,CisimModeli::Tip,new QTableWidgetItem(cisimModeli->tipIsmiAl()));
    setItem(satir,CisimModeli::Sira,new QTableWidgetItem(tr("%1").arg(cisimModeli->siraAl())));
    switch (cisimModeli->tipAl()) {
    case CisimModeli::Kiris:
        setItem(satir,CisimModeli::BaslangicKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangciKonumuAl())));
        setItem(satir,CisimModeli::BitisKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisKonumuAl())));
        break;
    case CisimModeli::SabitMesnet:
        setItem(satir,CisimModeli::NoktaKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    case CisimModeli::HareketliMesnet:
        setItem(satir,CisimModeli::HareketliMesnet,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    case CisimModeli::AnkastreMesnet:
        setItem(satir,CisimModeli::NoktaKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        break;
    case CisimModeli::TekilKuvvet:
        setItem(satir,CisimModeli::NoktaKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        setItem(satir,CisimModeli::NoktaKuvveti,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKuvvetiAl())));
        break;
    case CisimModeli::YayiliKuvvet:
        setItem(satir,CisimModeli::BaslangicKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangciKonumuAl())));
        setItem(satir,CisimModeli::BitisKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisKonumuAl())));
        setItem(satir,CisimModeli::BaslangicKuvveti,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangicKuvvetiAl())));
        setItem(satir,CisimModeli::BitisKuvveti,new QTableWidgetItem(tr("%1").arg(cisimModeli->bitisKuvvetiAl())));
        break;
    case CisimModeli::Moment:
        setItem(satir,CisimModeli::NoktaKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->noktaKonumuAl())));
        setItem(satir,CisimModeli::Moment,new QTableWidgetItem(tr("%1").arg(cisimModeli->momentAl())));
        break;
    default:
        break;
    }
}

void TabloWidget::siraAl(CisimModeli *cisim)
{
    int sira = 0;
    foreach (auto c, cisimModelListesiAl()) {
        if (cisim->tipAl() == c->tipAl()) {
            if (sira == c->siraAl()) {
                sira++;
            }
        }
    }
    cisim->siraAta(sira);
}

