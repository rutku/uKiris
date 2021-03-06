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

#include "yayilikuvvetcismi.h"

YayiliKuvvetCismi::YayiliKuvvetCismi(CisimModeli *parent)
    : cisimModelim(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    tipim = cisimModelim->tipAl();
    siram = cisimModelim->siraAl();
}

QPainterPath YayiliKuvvetCismi::shape() const
{
    QPainterPath yol;
    yol.addRect(boundingRect());
    return yol;
}

void YayiliKuvvetCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    painter->setRenderHint(QPainter::Antialiasing);
    int x1 = cisimModelim->baslangicKonumuAl();
    int x2 = cisimModelim->bitisKonumuAl();
    x = x1;
    y = 0;
    cisimModelim->tipAta(CisimModeli::YayiliKuvvet);

    int y1 = -80;
    int y2 = -80;
    int yaziAcisi = 0;
    if (cisimModelim->baslangicKuvvetiAl() > 0) {
        painter->rotate(180);
        yaziAcisi = -180;
        x = x2;
    }

    if (qFabs(cisimModelim->baslangicKuvvetiAl()) < qFabs(cisimModelim->bitisKuvvetiAl())) {
        y1 = -40;
        y2 = -80;
    }else if (qFabs(cisimModelim->baslangicKuvvetiAl()) > qFabs(cisimModelim->bitisKuvvetiAl())){
        y1 = -80;
        y2 = -40;
    }

    if (yaziAcisi != 0) {
        int tmpY1 = y1;
        y1 = y2;
        y2 = tmpY1;
    }
    painter->drawPolygon(okBasiCiz(0,0));
    painter->drawPolygon(okGovdesiCiz(0,y1));

    painter->drawPolygon(okBasiCiz(x2-x1,0));
    painter->drawPolygon(okGovdesiCiz(x2-x1,y2));

    painter->drawLine(0,y1,x2-x1,y2);

    int yaziY1 = y1-10;
    int yaziY2 = y2-10;
    int yaziX1 = 0;
    int yaziX2 = x2-x1;
    if (yaziAcisi != 0) {
        yaziY1 = y2 * -1 + 15;
        yaziY2 = y1 * -1 + 15;
        yaziX1 = x1-x2;
        yaziX2 = 0;
    }

    painter->rotate(yaziAcisi);
    QString kuvvet1 = QString::number(cisimModelim->baslangicKuvvetiAl());
    painter->drawText(QPointF(yaziX1,yaziY1),kuvvet1);

    QString kuvvet2 = QString::number(cisimModelim->bitisKuvvetiAl());
    painter->drawText(QPointF(yaziX2,yaziY2),kuvvet2);
    cisimAlani.setRect(x,y,(x2-x1),yaziY2);
}

QPolygonF YayiliKuvvetCismi::okBasiCiz(int x, int y)
{
    QPolygonF okBasi;
    okBasi << QPointF(x-10,y-30) << QPointF(x,y-10)
           << QPointF(x+10,y-30);

    return okBasi;
}

QPolygonF YayiliKuvvetCismi::okGovdesiCiz(int x, int h)
{
    QPolygonF okGovdesi;
    okGovdesi << QPointF(x,-30) << QPointF(x,h);
    return okGovdesi;
}
