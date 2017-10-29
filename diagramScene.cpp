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

#include "diagramScene.h"

#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QDebug>

DiagramScene::DiagramScene(QObject *parent)
    : QGraphicsScene(parent)
{
    kipim = CisimTasi;
    cisimRengim  = Qt::white;

}

DiagramScene::~DiagramScene()
{

}

void DiagramScene::kipAta(DiagramScene::Mode kip)
{
    kipim = kip;
}

void DiagramScene::cisimIslemleri(CisimModeli *_cisimModeli)
{
    if (_cisimModeli == nullptr) {
        return;
    }
    switch (kipim) {
    case CisimGir:
    {
        {
            switch (_cisimModeli->tipAl()) {
            case CisimModeli::Kiris:
                kirisCismi = new KirisCismi(_cisimModeli);
                addItem(kirisCismi);
                kirisCismi->setPos(_cisimModeli->baslangicKonumuAl(),0);
                break;
            case CisimModeli::SabitMesnet:
                sabitMesnetCismi = new SabitMesnetCismi(_cisimModeli);
                addItem(sabitMesnetCismi);
                sabitMesnetCismi->setPos(_cisimModeli->noktaKonumuAl(),35);
                break;
            case CisimModeli::HareketliMesnet:
                hareketliMesnet = new HareketliMesnetCismi(_cisimModeli);
                addItem(hareketliMesnet);
                hareketliMesnet->setPos(_cisimModeli->noktaKonumuAl(),60);
                break;
            case CisimModeli::AnkastreMesnet:
                ankastreMesnetCismi = new AnkastreMesnetCismi(_cisimModeli);
                addItem(ankastreMesnetCismi);
                ankastreMesnetCismi->setPos(_cisimModeli->noktaKonumuAl(),0);
                break;
            case CisimModeli::TekilKuvvet:
                tekilKuvvetCismi = new TekilKuvvetCismi(_cisimModeli);
                addItem(tekilKuvvetCismi);
                tekilKuvvetCismi->setPos(_cisimModeli->noktaKonumuAl(),0);
                break;
            case CisimModeli::YayiliKuvvet:
                yayiliKuvvetCismi = new YayiliKuvvetCismi(_cisimModeli);
                addItem(yayiliKuvvetCismi);
                yayiliKuvvetCismi->setPos(_cisimModeli->baslangicKonumuAl(),0);
                break;
            case CisimModeli::Moment:
                momentCismi = new MomentCismi(_cisimModeli);
                addItem(momentCismi);
                momentCismi->setPos(_cisimModeli->noktaKonumuAl()+22,0);
                break;
            default:
                break;
            }
        }
        emit tabloyaCisimEkle(_cisimModeli);
    }
        break;
    case CisimDuzenle:
    {
        {
            switch (_cisimModeli->tipAl()) {
            case CisimModeli::Kiris:
                kirisCismi->setPos(_cisimModeli->baslangicKonumuAl(),0);
                break;
            case CisimModeli::SabitMesnet:
                sabitMesnetCismi->setPos(_cisimModeli->noktaKonumuAl(),35);
                break;
            case CisimModeli::HareketliMesnet:
                hareketliMesnet->setPos(_cisimModeli->noktaKonumuAl(),60);
                break;
            case CisimModeli::AnkastreMesnet:
                ankastreMesnetCismi->setPos(_cisimModeli->noktaKonumuAl(),0);
                break;
            case CisimModeli::TekilKuvvet:
                tekilKuvvetCismi->setPos(_cisimModeli->noktaKonumuAl(),0);
                break;
            case CisimModeli::YayiliKuvvet:
                yayiliKuvvetCismi->setPos(_cisimModeli->baslangicKonumuAl(),0);
                break;
            case CisimModeli::Moment:
                momentCismi->setPos(_cisimModeli->noktaKonumuAl()+22,0);
                break;
            default:
                break;
            }
        }
        emit tabloyuGuncelle(_cisimModeli);
        break;
    }
    case CisimSil:
    {
        {
            foreach (QGraphicsItem *cisim, items(Qt::AscendingOrder)) {
                switch (cisim->type()) {
                case CisimModeli::Kiris:
                {
                    kirisCismi = qgraphicsitem_cast<KirisCismi *>(cisim);
                    if (kirisCismi->tipAl() == _cisimModeli->tipAl() &&
                            kirisCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::SabitMesnet:
                {
                    sabitMesnetCismi = qgraphicsitem_cast<SabitMesnetCismi *>(cisim);
                      if (sabitMesnetCismi->tipAl() == _cisimModeli->tipAl() &&
                            sabitMesnetCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::HareketliMesnet:
                {
                    hareketliMesnet = qgraphicsitem_cast<HareketliMesnetCismi *>(cisim);
                    if (hareketliMesnet->tipAl() == _cisimModeli->tipAl() &&
                            hareketliMesnet->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::AnkastreMesnet:
                {
                    ankastreMesnetCismi = qgraphicsitem_cast<AnkastreMesnetCismi *>(cisim);
                    if (ankastreMesnetCismi->tipAl() == _cisimModeli->tipAl() &&
                            ankastreMesnetCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::TekilKuvvet:
                {
                    tekilKuvvetCismi = qgraphicsitem_cast<TekilKuvvetCismi *>(cisim);
                    if (tekilKuvvetCismi->tipAl() == _cisimModeli->tipAl() &&
                            tekilKuvvetCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::YayiliKuvvet:
                {
                    yayiliKuvvetCismi = qgraphicsitem_cast<YayiliKuvvetCismi *>(cisim);
                    if (yayiliKuvvetCismi->tipAl() == _cisimModeli->tipAl() &&
                            yayiliKuvvetCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::Moment:
                {
                    momentCismi = qgraphicsitem_cast<MomentCismi *>(cisim);
                    if (momentCismi->tipAl() == _cisimModeli->tipAl() &&
                            momentCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                default:
                    break;
                }
            }
        }
        break;
    }
    default:
        break;
    }
}
