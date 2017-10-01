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


#ifndef KESMEDIAGRAMSAHNESI_H
#define KESMEDIAGRAMSAHNESI_H

#include "diagramItem.h"
#include "cisimmodeli.h"

#include <QGraphicsScene>
#include <QList>
#include <QtMath>
#include <QVector2D>

QT_BEGIN_NAMESPACE
class QPen;
class DiagramItem;
class QLine;
QT_END_NAMESPACE


class KMDiagramSahnesi : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Diagram { KesmeDiagrami, MomentDiagrami };
    KMDiagramSahnesi(QObject *parent = 0);
    void sonuclariSil();

public slots:
    void kesmeDiagramiCiz(QList<CisimModeli *> _cisimModelListesi);
    void momentDiagramiCiz(QList<CisimModeli *> _cisimModelListesi);

private:
    QList<CisimModeli*> cisimModelListesi;
    QList<CisimModeli*> enKucuktenCisimModelListesi;    

    QList<QVector2D> kesmeKuvvetleri;
    QList<QVector2D> momentler;
    QList<QVector2D> ucKuvvetler;
    QList<QVector2D> ucMomentler;

    CisimModeli *_cisimModeli;
    Diagram diagramim;
    void cisimleriSirala();
    double kuvvetleriTopla();
    void mesnetleriHesapla();
    double mesnetinKuvvetiniBul(CisimModeli::CisimTipi tip);
    void diagramlariCiz();
    void kesmeDiagraminiOlustur();
    void momentDiagraminiOlustur();
    void eksenleriCiz();
    void sinirlardakiKuvvetleriCiz();
    double enBuyukKuvvetiAl(QList<QVector2D> kuvvetListesi);
    double enKucukKuvvetiAl(QList<QVector2D> kuvvetListesi);
    double yayiliIcKuvvet(CisimModeli *cisim, double x);
    double yayiliIcMoment(CisimModeli *cisim, double x);
    double yayiliDisMoment(CisimModeli *cisim, int i);
    double ucgeninIcKuvveti(CisimModeli *cisim, double x);
    double ucgeninKonumu(CisimModeli *cisim, double x);
    double dikdortgeninIcKuvveti(CisimModeli *cisim, double x);
    double dikdortgeninKonumu(CisimModeli *cisim, double x);
    QVector2D enBuyukMomentiAl();
    double METRE = 0.01;
    double SANTIMETRE = 100;
    double kirisUzunlugu;
    double sabitMesnet;
    double hareketliMesnet;
    double ankastreMesnet;
    QList<double> kesmeKuvvetlerininListesi;
    void hesapla();
    QPolygonF okCiz(int yon/*-1 = Kuvvet || Moment ; 0 = x*/);

};

#endif // KESMEDIAGRAMSAHNESI_H
