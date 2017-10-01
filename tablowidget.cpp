/****************************************************************************
**
** Copyright (C) 2017 Ramazan Utku
** Contact: ramazanutku@gmail.com
**
** This file is part of the examples of the Qt Toolkit.
**
** $UKIRIS_BEGIN_LICENSE:BSD$
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** TURKISH
** Her hakkı saklıdır.
** Değişiklik yapılarak veya yapılmaksızın, yeniden dağıtmak veya kaynak ve ikili biçimlerde
** kullanmak, aşağıdaki koşullar yerine getirildiği takdirde serbesttir:
**
**  * Kaynak kodun yeniden dağıtımı; yukarıdaki telif hakkı uyarısını, şartlar listesini ve
**    aşağıdaki ret yazısını muhafaza etmelidir.
**  * İkili biçimde yeniden dağıtımında; yukarıdaki telif hakkı uyarısı, şartlar listesi ve
**    aşağıdaki ret yazısı dağıtımla birlikte gelen belgelendirmede ve/veya diğer materyallerde
**    tekrarlanmalıdır.
**
** İŞBU YAZILIM TELİF HAKKI SAHİPLERİ VE KATKIDA BULUNANLAR TARAFINDAN OLDUĞU GİBİ” SAĞLANMIŞTIR
** VE TİCARETE ELVERİŞLİLİK VE ÖZEL BİR AMACA UYGUNLUK İÇİN KAPALI BİR TAAHHÜT DE DAHİL OLMAK ÜZERE
** VE BUNUNLA KISITLI OLMAKSIZIN HER TÜRLÜ AÇIK YA DA KAPALI TAAHHÜT REDDEDİLMİŞTİR.
** HİÇBİR KOŞULDA TELİF HAKKI SAHİPLERİ VE KATKIDA BULUNANLAR; HER NE SEBEPLE OLUŞMUŞSA VE SÖZLEŞMEDE,
** KUSURSUZ SORUMLULUKTA, VEYA TAZMİNAT YÜKÜMLÜLÜĞÜNDE OLMAK ÜZERE HANGİ YÜKÜMLÜLÜK KURAMINDA
** YER ALIRSA ALSIN,İŞBU YAZILIMIN KULLANIMIYLA ORTAYA ÇIKAN DOĞRUDAN, DOLAYLI, TESADÜFİ, ÖZEL,
** CEZAİ VEYA BİR SEBEP SONUCUNDA OLUŞAN (YEDEK PARÇA VEYA HİZMETLERİN TEMİNİ; KULLANIM,
** VERİ VEYA RANDIMAN KAYBI; YA DA İŞ KESİNTİSİ DE DAHİL OLMAK ÜZERE VE BUNUNLA KISITLI KALMAKSIZIN)
** HERHANGİ BİR ZARAR İÇİN, BU GİBİ HASARLARIN OLASILIĞI HAKKINDA UYARILMIŞ OLSALAR BİLE, SİZE KARŞI
** SORUMLU DEĞİLLERDİR.
**
** $UKIRIS_END_LICENSE$
**
****************************************************************************/

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

void TabloWidget::tumCisimleriSil()
{
    for (int i = 0; i < cisimModelListesi.size(); ++i) {
        emit Sil(cisimModelListesi.at(i));
    }
    setRowCount(0);
    qDeleteAll(cisimModelListesi.begin(),cisimModelListesi.end());
    cisimModelListesi.clear();
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
        setItem(satir,CisimModeli::BaslangicKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangicKonumuAl())));
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
        setItem(satir,CisimModeli::BaslangicKonumu,new QTableWidgetItem(tr("%1").arg(cisimModeli->baslangicKonumuAl())));
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

