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

#include "KMDiagramSahnesi.h"
#include "diagramItem.h"

#include <QDebug>

KMDiagramSahnesi::KMDiagramSahnesi(QObject *parent)
    : QGraphicsScene(parent)
{
}

void KMDiagramSahnesi::sonuclariSil()
{
    foreach (auto cisim, items(Qt::AscendingOrder)) {
        removeItem(cisim);
    }
    cisimModelListesi.clear();
}

void KMDiagramSahnesi::kesmeDiagramiCiz(QList<CisimModeli *> _cisimModelListesi)
{
    diagramim = KesmeDiagrami;
    cisimModelListesi = _cisimModelListesi;
    hesapla();
}

void KMDiagramSahnesi::momentDiagramiCiz(QList<CisimModeli *> _cisimModelListesi)
{
    diagramim = MomentDiagrami;
    cisimModelListesi = _cisimModelListesi;
    hesapla();
}

void KMDiagramSahnesi::hesapla()
{
    cisimleriSirala();
    mesnetleriHesapla();

    double moment = 0.0;
    double kesmeKuvveti = 0.0;
    double tekilKuvvet = 0.0;
    double yayiliKuvvet = 0.0;
    double hareketliMesnetKuvveti = 0.0;
    double sabitMesnetKuvveti = 0.0;
    double ankastreMesnetKuvveti = 0.0;
    double tekilKuvvetMomenti = 0.0;
    double sabitMesnetMomenti = 0.0;
    double hareketliMesnetMomenti = 0.0;
    double ankastreMesnetMomenti = 0.0;
    double ankastreMomenti = 0.0;
    double yayiliMoment = 0.0;
    double noktaMomenti = 0.0;

    QPen kalem(Qt::black,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    for (int i = 0; i <= kirisUzunlugu; ++i) {
        QLine diagramCizgisi;
        tekilKuvvetMomenti = 0.0;
        yayiliMoment =0.0;

        bool sinirda = false;

        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (cisim->tipAl() == CisimModeli::YayiliKuvvet) {
                if (i >= (int)cisim->baslangicKonumuAl() && i <= (int)cisim->bitisKonumuAl()) {

                    if (i == (int)cisim->baslangicKonumuAl() || i == (int)cisim->bitisKonumuAl()) {
                        sinirda = true;
                    }

                    yayiliKuvvet = yayiliIcKuvvet(cisim,(double)i);
                    yayiliMoment = yayiliIcMoment(cisim,(double)i);

                }else if (i > (int)cisim->bitisKonumuAl()) {
                    yayiliMoment = yayiliDisMoment(cisim,i);
                }
            }else if (cisim->tipAl() == CisimModeli::TekilKuvvet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    tekilKuvvet += cisim->noktaKuvvetiAl();
                    sinirda = true;
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    tekilKuvvetMomenti += (cisim->noktaKuvvetiAl() * (i - cisim->noktaKonumuAl()));
                }

            }else if (cisim->tipAl() == CisimModeli::SabitMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    sabitMesnetKuvveti = cisim->noktaKuvvetiAl();
                    sinirda = true;
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    sabitMesnetMomenti = (sabitMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == CisimModeli::HareketliMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    hareketliMesnetKuvveti = cisim->noktaKuvvetiAl();
                     sinirda = true;
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    hareketliMesnetMomenti = (hareketliMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == CisimModeli::AnkastreMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    ankastreMesnetKuvveti = cisim->noktaKuvvetiAl();
                    ankastreMesnetMomenti = cisim->momentAl() * 100;
                    sinirda = true;
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    ankastreMomenti = (ankastreMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == CisimModeli::Moment && i == cisim->noktaKonumuAl()) {
                noktaMomenti = cisim->momentAl() * 100;
                sinirda = true;
            }
        }
        //TODO:moment değişkeni ve xNoktasindakiMoment değişkeni düzeltilmeli!

        double tmpKesmeKuvveti = kesmeKuvveti;
        kesmeKuvveti = (tekilKuvvet + yayiliKuvvet + sabitMesnetKuvveti + hareketliMesnetKuvveti +
                ankastreMesnetKuvveti) * 10.0;
//        qDebug()<<"i["<<i<<"]TK:"<<tekilKuvvet<<"YK:"<<yayiliKuvvet<<"SMK:"<<sabitMesnetKuvveti<<"HMK:"<<hareketliMesnetKuvveti
//               << "AMK:"<<ankastreMesnetKuvveti<<" K:"<<kesmeKuvveti * 10.0;

        moment = (tekilKuvvetMomenti + yayiliMoment + sabitMesnetMomenti + hareketliMesnetMomenti +
                  ankastreMesnetMomenti + ankastreMomenti + noktaMomenti)/10.0;
        if (qFabs(moment) < 0.0001 ) { //Hata Payı
            moment = 0.0;
        }
//        qDebug()<<"i["<<i<<"]TKM:"<<tekilKuvvetMomenti<<"YKM:"<<yayiliMoment<<"SMKM:"<<sabitMesnetMomenti<<"HMKM:"<<hareketliMesnetMomenti
//               << "AMKM:"<<ankastreMesnetMomenti<<" M:"<<moment/10;


        //Hesaplanan Yük(lerin)ün ve Mesnetlerin Kuvvet ve Moment Diyagramları Aşağıda çiziliyor.
        if (diagramim == KesmeDiagrami) {
            kesmeKuvvetleri.append(QVector2D(i,kesmeKuvveti));
            if (sinirda) {
                if (kesmeKuvveti != tmpKesmeKuvveti) {
                    kesmeKuvvetleri.insert((kesmeKuvvetleri.size()-1),QVector2D(i,kesmeKuvveti));
                }
            }
        }else {
            momentler.append(QVector2D(i,moment));
            if (CisimModeli::AnkastreMesnet || CisimModeli::TekilKuvvet) { // Kesmenin Sıfır olduğu kısımdaki Momenti buluyoruz.
                if (qFabs(tmpKesmeKuvveti) > 1 && qFabs(kesmeKuvveti) <= 1) {
                    sinirda = true;
                }
            }
            if (sinirda) {
                if (ankastreMesnetMomenti != 0
                        && moment == 0
                        && ankastreMomenti == 0) {
                    momentler.insert(momentler.size()-1,QVector2D(i,((moment-(ankastreMesnetMomenti/10.0)))));
                }else {
                    momentler.insert(momentler.size()-1,QVector2D(i,(moment)));
                }
            }
        }
    }

    diagramlariCiz();
}

void KMDiagramSahnesi::diagramlariCiz()
{
    double h = 250;
    double x1 = 0;
    double x2 = 0;
    double y1 = h;
    double y2 = h;

    QPen kirisKalemi(Qt::red,2,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin);
    auto kiris = addLine(0,h,kirisUzunlugu,h,kirisKalemi);
    kiris->setZValue(kiris->zValue() - 0.1);


    auto kuvvetler = diagramim == KesmeDiagrami ? kesmeKuvvetleri : momentler;
    QPen kalem(Qt::black,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

    foreach (auto k, kuvvetler) {
        x2 = k.x();
        y2 = k.y() + h;
        addLine(x1,y1,x2,y2,kalem);
        x1 = x2;
        y1 = y2;
    }

    eksenleriCiz();
}

void KMDiagramSahnesi::eksenleriCiz()
{
    QPen kalem(Qt::blue,2,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin);

    QList<QVector2D> kuvvetListesi;
    QString mesafeYazisi = "x(cm)";
    QString kuvvetYazisi;
    int kuvvetXPozisyonu;
    double h = 250.0;
    double xEksenininXi = kirisUzunlugu + 50;
    double xEksenininYsi = h + 50;
    double yEksenininYsi = h - 50;

    if (diagramim == KesmeDiagrami) {
        kuvvetListesi = kesmeKuvvetleri;
        kuvvetYazisi = "Kuvvet(kN)";
        kuvvetXPozisyonu = -100;
    }else {
        kuvvetListesi = momentler;
        kuvvetYazisi = "Moment(kN.m)";
        kuvvetXPozisyonu = -130;
    }

    xEksenininYsi += enBuyukKuvvetiAl(kuvvetListesi);
    yEksenininYsi += enKucukKuvvetiAl(kuvvetListesi);

    addLine(-20,xEksenininYsi,xEksenininXi,xEksenininYsi,kalem);//->(x)
    auto *xMesafesiYazisi = addText("x(cm)");
    xMesafesiYazisi->setPos(xEksenininXi,xEksenininYsi);

    addLine(-20,xEksenininYsi,-20,yEksenininYsi,kalem);//->(Kuvvet || Moment)
    auto *kuvvetYazisininPozisyonu = addText(kuvvetYazisi);
    kuvvetYazisininPozisyonu->setPos(kuvvetXPozisyonu,yEksenininYsi - 15);

    kalem.setStyle(Qt::SolidLine);
    auto *xOku = addPolygon(okCiz(-1),kalem);
    xOku->setPos(xEksenininXi,xEksenininYsi);

    auto *kuvvetOku = addPolygon(okCiz(0),kalem);
    kuvvetOku->setPos(-20,yEksenininYsi);
    sinirlardakiKuvvetleriCiz();

}

void KMDiagramSahnesi::sinirlardakiKuvvetleriCiz()
{

    double h = 250.0;
    auto kuvvetler = diagramim == KesmeDiagrami ? kesmeKuvvetleri : momentler;
    double xEksenininYsi = enBuyukKuvvetiAl(kuvvetler) + h + 55;
    QPen kalem(Qt::blue,2,Qt::DashDotLine,Qt::RoundCap,Qt::RoundJoin);

    foreach (auto k, kuvvetler) {
        bool sinirda = false;
        foreach (auto cisim, enKucuktenCisimModelListesi) {
            switch (cisim->tipAl()) {
            case CisimModeli::HareketliMesnet:
            case CisimModeli::SabitMesnet:
            case CisimModeli::AnkastreMesnet:
            case CisimModeli::TekilKuvvet:
            case CisimModeli::Moment:
                sinirda = cisim->noktaKonumuAl() == k.x() ? true : false;
                break;
            case CisimModeli::YayiliKuvvet:
                if (cisim->baslangicKonumuAl() == k.x() || cisim->bitisKonumuAl() == k.x())
                    sinirda = true;
                break;
            default:
                break;

            }

            if (sinirda || (enBuyukMomentiAl().x() == k.x() && enBuyukMomentiAl().y() == k.y())) {
                if (k.y() != 0.0) {//Y Eksenindeki Kesme Kuvveti ve Momentin kuvvet bilgileri
                    kalem.setColor(Qt::cyan);
                    QGraphicsLineItem *yEkseni =  addLine(-20,k.y()+h,k.x(),k.y()+h,kalem);//->(Kuvvet || Moment)
                    yEkseni->setZValue(yEkseni->zValue()-0.1);
                    QString _kuvvet = QString("%1").arg(k.y()/10.0);
                    QGraphicsTextItem *kuvvet = addText(_kuvvet);
                    kuvvet->setPos(-1*(_kuvvet.size()*3+50),k.y()+h-15);
                }
                kalem.setColor(Qt::green);
                QGraphicsLineItem *xEkseni = addLine(k.x(),k.y()+h,k.x(),xEksenininYsi,kalem);//->(x)
                xEkseni->setZValue(xEkseni->zValue()-0.1);
                QGraphicsTextItem *mesafe = addText(QString("%1").arg(k.x()));
                mesafe->setPos(k.x(),xEksenininYsi);
            }
        }
    }

}

double KMDiagramSahnesi::enBuyukKuvvetiAl(QList<QVector2D> kuvvetListesi)
{
    double enBuyukKuvvet = 0.0;
    foreach (auto k, kuvvetListesi) {
        if ( k.y() > enBuyukKuvvet ) {
            enBuyukKuvvet = k.y();
        }
    }

    return enBuyukKuvvet;
}

double KMDiagramSahnesi::enKucukKuvvetiAl(QList<QVector2D> kuvvetListesi)
{
    auto enBuyukKuvvet = enBuyukKuvvetiAl(kuvvetListesi);
    double enKucukKuvvet = enBuyukKuvvet;//Listedeki En büyük kuvveti eleye eleye en küçüğe iniyoruz.
    foreach (auto k, kuvvetListesi) {
        if (k.y() < enKucukKuvvet) {
            enKucukKuvvet = k.y();
        }
    }
    return enKucukKuvvet;
}

QPolygonF KMDiagramSahnesi::okCiz(int yon/*-1 = Kuvvet || Moment ; 0 = x*/)
{
    QPolygonF okBasi;
    if (yon == 0) {
        okBasi << QPointF(-5,0) << QPointF(0,-15)
               << QPointF(5,0);
    }else {
        okBasi << QPointF(0,-5) << QPointF(15,0)
               << QPointF(0,5);
    }

    return okBasi;
}

void KMDiagramSahnesi::cisimleriSirala()
{
    QList<CisimModeli*> _cisimModelListesi(cisimModelListesi);

    QList<CisimModeli*> enBuyuktenCisimModelListesi;

    for (int i = 0; i < _cisimModelListesi.size(); ++i) {
        if (_cisimModelListesi.at(i)->tipAl() == CisimModeli::Kiris) {
            kirisUzunlugu = _cisimModelListesi.at(i)->bitisKonumuAl() - _cisimModelListesi.at(i)->baslangicKonumuAl();
            _cisimModelListesi.removeAt(i);
        }
    }

    int enBuyukKonum = 0;

    for (int i = 0; i < cisimModelListesi.size() -1 ; ++i) {
        int indis;
        for (int j = 0; j < _cisimModelListesi.size(); ++j) {
            CisimModeli *cisim = _cisimModelListesi.at(j);
            int konum = 0;

            if (cisim->tipAl() == CisimModeli::YayiliKuvvet) {
                konum = cisim->baslangicKonumuAl();
            }else
            {
                konum = cisim->noktaKonumuAl();
            }

            if (enBuyukKonum <= konum) {
                enBuyukKonum = konum;
                _cisimModeli = cisim;
                indis = j;
            }
        }

        enBuyuktenCisimModelListesi.append(_cisimModelListesi.at(indis));
        _cisimModelListesi.removeAt(indis);
        enBuyukKonum = 0;
    }


    for (int i = enBuyuktenCisimModelListesi.size() - 1; i >= 0; --i) {
        enKucuktenCisimModelListesi.append(enBuyuktenCisimModelListesi.at(i));
    }

}

double KMDiagramSahnesi::kuvvetleriTopla()
{
    double toplamKuvvet = 0;
    foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
        if (cisim->tipAl() == CisimModeli::TekilKuvvet) {
            toplamKuvvet += cisim->noktaKuvvetiAl();
        }else if (cisim->tipAl() == CisimModeli::YayiliKuvvet) {
            double tabanUzunlugu = (cisim->bitisKonumuAl() - cisim->baslangicKonumuAl()) * METRE;
            double dikDortgenKuvveti = 0;
            double ucgenKuvveti = 0;

            if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
                dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
            }else if (qFabs(cisim->baslangicKuvvetiAl()) < qFabs(cisim->bitisKuvvetiAl())) {
                dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                ucgenKuvveti = (((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl())
                        * tabanUzunlugu)/2.0);
            }else if (qFabs(cisim->baslangicKuvvetiAl()) > qFabs(cisim->bitisKuvvetiAl())) {
                dikDortgenKuvveti = cisim->bitisKuvvetiAl() * tabanUzunlugu;
                ucgenKuvveti = (1.0/2.0)*((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl())
                        * tabanUzunlugu);
            }

            toplamKuvvet += dikDortgenKuvveti + ucgenKuvveti;
        }
    }

    return toplamKuvvet;

}

void KMDiagramSahnesi::mesnetleriHesapla()
{
    ankastreMesnet = 0;
    sabitMesnet = 0;
    hareketliMesnet = 0;

    foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
        if (cisim->tipAl() ==  CisimModeli::AnkastreMesnet) {
            ankastreMesnet = -1 * kuvvetleriTopla();
            cisim->noktaKuvvetiAta(ankastreMesnet);
            mesnetinKuvvetiniBul(CisimModeli::AnkastreMesnet);
        }else if (cisim->tipAl() == CisimModeli::SabitMesnet) {
            hareketliMesnet = -1 * mesnetinKuvvetiniBul(CisimModeli::SabitMesnet);
            sabitMesnet = -1 * (kuvvetleriTopla() + hareketliMesnet);
            cisim->noktaKuvvetiAta(sabitMesnet);
        }else if (cisim->tipAl() == CisimModeli::HareketliMesnet) {
            cisim->noktaKuvvetiAta(hareketliMesnet);
            break;
        }
        /*TODO:Sabit Mesnet -> Sabit Mesnet veya Hareketli Mesnet -> Hareketli Mesnet durumları
         incelenecek ! */
    }
}

double KMDiagramSahnesi::mesnetinKuvvetiniBul(CisimModeli::CisimTipi tip)
{
    double kuvvet = 0;
    double noktaKonumu = 0;
    foreach (CisimModeli *mesnet, enKucuktenCisimModelListesi) {
        if (tip == mesnet->tipAl()) {
            noktaKonumu = mesnet->noktaKonumuAl() * METRE;
        }
    }

    foreach (CisimModeli *mesnet, enKucuktenCisimModelListesi) {
        double moment = 0;

        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (CisimModeli::TekilKuvvet == cisim->tipAl()) {
                moment += (cisim->noktaKonumuAl() * METRE - noktaKonumu) * cisim->noktaKuvvetiAl();
            }else if (CisimModeli::YayiliKuvvet == cisim->tipAl()) {
                double tabanUzunlugu = (cisim->bitisKonumuAl() - cisim->baslangicKonumuAl()) * METRE;
                double dikDortgenKuvveti = 0;
                double ucgenKuvveti = 0;
                double dikdortgenMesafe = (cisim->baslangicKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu/2);
                double ucgenMesafe = 0;

                if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
                    dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                }else if (qFabs(cisim->baslangicKuvvetiAl()) < qFabs(cisim->bitisKuvvetiAl())) {
                    dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                    ucgenKuvveti = (((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl())
                            * tabanUzunlugu)/2.0);
                    ucgenMesafe = (cisim->baslangicKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu*(2.0/3.0));
                }else if (qFabs(cisim->baslangicKuvvetiAl()) > qFabs(cisim->bitisKuvvetiAl())) {
                    dikDortgenKuvveti = cisim->bitisKuvvetiAl() * tabanUzunlugu;
                    ucgenKuvveti = (1/2)*((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl())
                            * tabanUzunlugu);
                    ucgenMesafe = (cisim->baslangicKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu*(1.0/3.0));
                }

                moment += dikDortgenKuvveti * dikdortgenMesafe + ucgenKuvveti * ucgenMesafe;
            }else if (CisimModeli::Moment == cisim->tipAl()) {
                moment -= cisim->momentAl();
            }
        }

        if (tip != mesnet->tipAl()) {
            if (mesnet->tipAl() == CisimModeli::SabitMesnet ||
                    mesnet->tipAl() == CisimModeli::HareketliMesnet) {
                double mesafe = mesnet->noktaKonumuAl() * METRE - noktaKonumu;
                kuvvet = moment / mesafe;
                break;
            }
        }
        if (mesnet->tipAl() == CisimModeli::AnkastreMesnet) {
            mesnet->momentAta(moment);
        }
    }
    return kuvvet;

}


double KMDiagramSahnesi::yayiliIcKuvvet(CisimModeli *cisim, double x)
{
    double dikdortgenKuvveti = 0.0;
    double ucgeninKuvveti = 0.0;

    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
        ucgeninKuvveti = ucgeninIcKuvveti(cisim,x);
    }else if (cisim->baslangicKuvvetiAl() == 0.0) {
        ucgeninKuvveti = ucgeninIcKuvveti(cisim,x);
    }else if (cisim->bitisKuvvetiAl() == 0.0) {
        ucgeninKuvveti = ucgeninIcKuvveti(cisim,x);
    }else if (qFabs(cisim->baslangicKuvvetiAl()) < qFabs(cisim->bitisKuvvetiAl())) {
        dikdortgenKuvveti = dikdortgeninIcKuvveti(cisim,x);
        ucgeninKuvveti = ucgeninIcKuvveti(cisim,x);
    }else {
        dikdortgenKuvveti = dikdortgeninIcKuvveti(cisim,x);
        ucgeninKuvveti = ucgeninIcKuvveti(cisim,x);
    }
    return ((dikdortgenKuvveti+ucgeninKuvveti) / 100.0);
}

double KMDiagramSahnesi::yayiliIcMoment(CisimModeli *cisim, double x)
{
    double dikdortgenKuvveti = 0.0;
    double dikdortgenKuvvetiKonumu = 0.0;
    double ucgenKuvveti = 0.0;
    double ucgenKuvvetiKonumu = 0.0;

    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
        dikdortgenKuvveti = dikdortgeninIcKuvveti(cisim,x);
    }else if ( cisim->baslangicKuvvetiAl() == 0.0){
        ucgenKuvveti = ucgeninIcKuvveti(cisim,x);
        ucgenKuvvetiKonumu = ucgeninKonumu(cisim,x);
    }else if (cisim->bitisKuvvetiAl() == 0.0) {
        ucgenKuvveti = ucgeninIcKuvveti(cisim,x);
        ucgenKuvvetiKonumu = ucgeninKonumu(cisim,x);
    }else if ( qFabs(cisim->baslangicKuvvetiAl()) < qFabs(cisim->bitisKuvvetiAl())){
        dikdortgenKuvveti = dikdortgeninIcKuvveti(cisim,x);
        dikdortgenKuvvetiKonumu = dikdortgeninKonumu(cisim, x);
        ucgenKuvveti = ucgeninIcKuvveti(cisim,x);
        ucgenKuvvetiKonumu = ucgeninKonumu(cisim,x);
    }else {
        dikdortgenKuvveti = dikdortgeninIcKuvveti(cisim,x);
        dikdortgenKuvvetiKonumu = dikdortgeninKonumu(cisim,x);
        ucgenKuvveti = ucgeninIcKuvveti(cisim,x);
        ucgenKuvvetiKonumu = ucgeninKonumu(cisim,x);
    }
    return (((dikdortgenKuvveti * dikdortgenKuvvetiKonumu) +
             (ucgenKuvveti * ucgenKuvvetiKonumu)) / 100.0);
}

double KMDiagramSahnesi::yayiliDisMoment(CisimModeli *cisim, int i)
{
    double dikdortgenKuvvetiKonumu = i -(cisim->baslangicKonumuAl()+(cisim->bitisKonumuAl()-cisim->baslangicKonumuAl())/2.0);
    double dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * (cisim->bitisKonumuAl() - cisim->baslangicKonumuAl());
    double ucgenKuvvetiKonumu = i - (cisim->baslangicKonumuAl()+((cisim->bitisKonumuAl()-cisim->baslangicKonumuAl())*2.0)/3.0);
    double ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                           (cisim->bitisKonumuAl()-cisim->baslangicKonumuAl()))/2.0;

    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * (cisim->bitisKonumuAl()-cisim->baslangicKonumuAl());

    }else if (qFabs(cisim->baslangicKuvvetiAl()) > qFabs(cisim->bitisKuvvetiAl())) {
        dikdortgenKuvveti = cisim->bitisKuvvetiAl() * (cisim->bitisKonumuAl() - cisim->baslangicKonumuAl());
        ucgenKuvvetiKonumu = i - (cisim->baslangicKonumuAl()+(cisim->bitisKonumuAl()-cisim->baslangicKonumuAl())/3.0);
        ucgenKuvveti = ((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl()) *
                                    (cisim->bitisKonumuAl()-cisim->baslangicKonumuAl()))/2.0;
    }
    return ((((dikdortgenKuvveti * dikdortgenKuvvetiKonumu)) +
            (ucgenKuvveti * ucgenKuvvetiKonumu)) / 100.0);

}

double KMDiagramSahnesi::ucgeninIcKuvveti(CisimModeli *cisim, double x)
{
    double ucgeninXDekiBileskeKuvveti = 0.0;
    double ucgeninXdekiKuvveti = 0.0;

    if (cisim->baslangicKuvvetiAl() == 0.0) {
        ucgeninXdekiKuvveti = (cisim->bitisKuvvetiAl()/(cisim->bitisKonumuAl() - cisim->baslangicKonumuAl())) * ( x - cisim->baslangicKonumuAl());
        ucgeninXDekiBileskeKuvveti = (ucgeninXdekiKuvveti * (x - cisim->baslangicKonumuAl())) / 2.0;
    }else if( cisim->bitisKuvvetiAl() == 0.0){
        ucgeninXdekiKuvveti = (cisim->baslangicKuvvetiAl()/(cisim->bitisKonumuAl() - cisim->baslangicKonumuAl())) * ( x - cisim->baslangicKonumuAl());
        ucgeninXDekiBileskeKuvveti = (ucgeninXdekiKuvveti * (x - cisim->baslangicKonumuAl())) / 2.0;
    }else if (qFabs(cisim->baslangicKuvvetiAl()) < qFabs(cisim->bitisKuvvetiAl())) {
        ucgeninXdekiKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl())/(cisim->bitisKonumuAl() - cisim->baslangicKonumuAl())) * ( x - cisim->baslangicKonumuAl());
        ucgeninXDekiBileskeKuvveti = (ucgeninXdekiKuvveti * (x - cisim->baslangicKonumuAl())) / 2.0;
    }else if (qFabs(cisim->bitisKuvvetiAl()) < qFabs(cisim->baslangicKuvvetiAl())) {
        ucgeninXdekiKuvveti = ((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl())/(cisim->bitisKonumuAl() - cisim->baslangicKonumuAl())) * ( x - cisim->baslangicKonumuAl());
        ucgeninXDekiBileskeKuvveti = (ucgeninXdekiKuvveti * (x - cisim->baslangicKonumuAl())) / 2.0;
    }else {
        ucgeninXDekiBileskeKuvveti = -1;
    }

    return ucgeninXDekiBileskeKuvveti;
}

double KMDiagramSahnesi::ucgeninKonumu(CisimModeli *cisim, double x)
{
    double konum = 0.0;
    if (cisim->baslangicKuvvetiAl() == 0.0 ||
            qFabs(cisim->baslangicKuvvetiAl()) < qFabs(cisim->bitisKuvvetiAl())) {
        konum = (x - cisim->baslangicKonumuAl()) / 3.0;
    }else if( cisim->bitisKuvvetiAl() == 0.0 ||
              qFabs(cisim->bitisKuvvetiAl()) < qFabs(cisim->baslangicKuvvetiAl())){
        konum = ((x - cisim->baslangicKonumuAl()) * 2.0) / 3.0;
    }else{
        konum = -1;
    }

    return konum;
}

double KMDiagramSahnesi::dikdortgeninIcKuvveti(CisimModeli *cisim, double x)
{
    double dikdortgeninXdekiBileskeKuvveti = 0.0;

    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
        dikdortgeninXdekiBileskeKuvveti = cisim->baslangicKuvvetiAl() * (x - cisim->baslangicKonumuAl());
    }else if (qFabs(cisim->baslangicKuvvetiAl()) < qFabs(cisim->bitisKuvvetiAl())) {
        dikdortgeninXdekiBileskeKuvveti = cisim->baslangicKuvvetiAl() * (x - cisim->baslangicKonumuAl());
    }else if (qFabs(cisim->bitisKuvvetiAl()) < qFabs(cisim->baslangicKuvvetiAl())) {
        dikdortgeninXdekiBileskeKuvveti = cisim->bitisKuvvetiAl() * (x - cisim->baslangicKonumuAl());
    }else{
        dikdortgeninXdekiBileskeKuvveti = -1;
    }

    return dikdortgeninXdekiBileskeKuvveti;
}

double KMDiagramSahnesi::dikdortgeninKonumu(CisimModeli *cisim, double x)
{
    double konum = 0.0;
    if (cisim->baslangicKuvvetiAl() != 0.0 && cisim->bitisKuvvetiAl() != 0.0) {
        konum = (x - cisim->baslangicKonumuAl()) / 2.0;
    }else{
        konum = -1;
    }

    return konum;
}

QVector2D KMDiagramSahnesi::enBuyukMomentiAl()
{
    double enBuyukMoment = 0.0;
    QVector2D enBuyukMomentinBilgisi;
    foreach (auto m, momentler) {
        if (qFabs(m.y()) > qFabs(enBuyukMoment)) {
            enBuyukMoment = m.y();
            enBuyukMomentinBilgisi = m;
        }
    }

    return enBuyukMomentinBilgisi;
}
