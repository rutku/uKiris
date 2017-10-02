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

#include "dosyaislemleri.h"

DosyaIslemleri::DosyaIslemleri(QObject *parent)
    : QObject(parent)
{
    xmlAkisiYaz.setAutoFormatting(true);

}

void DosyaIslemleri::xmlOlarakKaydet(QIODevice *dosya, QList<CisimModeli *> cisimModeliListesi)
{
    xmlAkisiYaz.setDevice(dosya);
    xmlAkisiYaz.writeStartDocument();
    xmlAkisiYaz.writeDTD("<!DOCTYPE xbel>");
    xmlAkisiYaz.writeStartElement("xbel");
    xmlAkisiYaz.writeAttribute("version", "1.0");

    Ayarlar _ayarlar;
    QString uzunlugunBirimi = _ayarlar.ayarIsmiAl(Ayarlar::UzunlugunBirimi).replace(" ","_");
    QString kuvvetinBirimi = _ayarlar.ayarIsmiAl(Ayarlar::KuvvetinBirimi).replace(" ","_");
    QString momentinBirimi = _ayarlar.ayarIsmiAl(Ayarlar::MomentinBirimi).replace(" ","_");

    xmlAkisiYaz.writeTextElement(uzunlugunBirimi,"cm");
    xmlAkisiYaz.writeTextElement(kuvvetinBirimi,"kN");
    xmlAkisiYaz.writeTextElement(momentinBirimi,"kN.m");
    foreach (auto cisim, cisimModeliListesi) {
        QString tipIsmi = cisim->tipIsmiAl().replace(" ","_");
        QString sira = cisim->degerIsmiAl(CisimModeli::Sira).replace(" ","_");
        QString noktaKonumu = cisim->degerIsmiAl(CisimModeli::NoktaKonumu).replace(" ","_");
        QString noktaKuvveti = cisim->degerIsmiAl(CisimModeli::NoktaKuvveti).replace(" ","_");
        QString baslangicKonumu = cisim->degerIsmiAl(CisimModeli::BaslangicKonumu).replace(" ","_");
        QString baslangicKuvveti = cisim->degerIsmiAl(CisimModeli::BaslangicKuvveti).replace(" ","_");
        QString bitisKonumu = cisim->degerIsmiAl(CisimModeli::BitisKonumu).replace(" ","_");
        QString bitisKuvveti = cisim->degerIsmiAl(CisimModeli::BitisKuvveti).replace(" ","_");
        QString moment = cisim->degerIsmiAl(CisimModeli::Moment).replace(" ","_");

        xmlAkisiYaz.writeStartElement(tipIsmi);        
        xmlAkisiYaz.writeTextElement(sira,QString("%1").arg(cisim->siraAl()));
        xmlAkisiYaz.writeTextElement(noktaKonumu,QString("%1").arg(cisim->noktaKonumuAl()));
        xmlAkisiYaz.writeTextElement(noktaKuvveti,QString("%1").arg(cisim->noktaKuvvetiAl()));
        xmlAkisiYaz.writeTextElement(baslangicKonumu,QString("%1").arg(cisim->baslangicKonumuAl()));
        xmlAkisiYaz.writeTextElement(baslangicKuvveti,QString("%1").arg(cisim->baslangicKuvvetiAl()));
        xmlAkisiYaz.writeTextElement(bitisKonumu,QString("%1").arg(cisim->bitisKonumuAl()));
        xmlAkisiYaz.writeTextElement(bitisKuvveti,QString("%1").arg(cisim->bitisKuvvetiAl()));
        xmlAkisiYaz.writeTextElement(moment,QString("%1").arg(cisim->momentAl()));
        xmlAkisiYaz.writeEndElement();
    }
    xmlAkisiYaz.writeEndDocument();
}

int DosyaIslemleri::xmlAc(QIODevice *dosya)
{
    QString hataMesaji;
    int hataDizesi;
    int hataKolonu;

    if (!domBelgesi.setContent(dosya,true,&hataMesaji,&hataDizesi,&hataKolonu)) {
        return -1;
    }

    QDomElement kok = domBelgesi.documentElement();

    if (kok.tagName() != "xbel") {
        return -2;
    } else if (kok.hasAttribute("version")
               && kok.attribute("version") != "1.0") {
        return -3;
    }

    cisimleriOku(kok);
    return 0;
}

void DosyaIslemleri::goruntuOlarakKaydet(QString &dosyaYolu, QGraphicsScene *sahne)
{
    sahne->clearSelection();
    sahne->setSceneRect(sahne->itemsBoundingRect());
    QImage goruntu(sahne->sceneRect().size().toSize(),QImage::Format_ARGB32);
    goruntu.fill(Qt::white);

    QPainter boyaci(&goruntu);
    sahne->render(&boyaci);
    goruntu.save(dosyaYolu);

}

void DosyaIslemleri::verileriTemizle()
{
//    qDeleteAll(cisimModelListesi.begin(),cisimModelListesi.end());
    cisimModelListesi.clear();
}

void DosyaIslemleri::cisimleriOku(QDomElement &kok)
{
    CisimModeli cisim;

    QDomNode n = ayarlariOku(kok);

    while(!n.isNull()){
        QDomElement eleman = n.toElement();
        QString tipIsmi = eleman.tagName();

        int tip = cisim.tipIsimleriAl().key(tipIsmi.replace("_"," "));
        if (!eleman.isNull()) {
            CisimModeli *yeniEleman = new CisimModeli();
            foreach (auto deger, yeniEleman->degerlerinIsimleriniAl().keys()) {
                QString isim = yeniEleman->degerlerinIsimleriniAl().value(deger);
                isim = isim.replace(" ","_");
                if (!isim.isEmpty()) {
                    switch (deger) {
                    case CisimModeli::Tip:
                        yeniEleman->tipAta(tip);
                        yeniEleman->tipIsmiAta(cisim.tipIsimleriAl().value(tip));
                        break;
                    case CisimModeli::Sira:
                        yeniEleman->siraAta(elemaninDegerleriniOku(eleman,isim));
                    case CisimModeli::NoktaKonumu:
                        yeniEleman->noktaKonumuAta(elemaninDegerleriniOku(eleman,isim));
                        break;
                    case CisimModeli::NoktaKuvveti:
                        yeniEleman->noktaKuvvetiAta(elemaninDegerleriniOku(eleman,isim));
                        break;
                    case CisimModeli::BaslangicKonumu:
                        yeniEleman->baslangciKonumuAta(elemaninDegerleriniOku(eleman,isim));
                        break;
                    case CisimModeli::BaslangicKuvveti:
                        yeniEleman->baslangicKuvvetiAta(elemaninDegerleriniOku(eleman,isim));
                        break;
                    case CisimModeli::BitisKonumu:
                        yeniEleman->bitisKonumuAta(elemaninDegerleriniOku(eleman,isim));
                        break;
                    case CisimModeli::BitisKuvveti:
                        yeniEleman->bitisKuvvetiAta(elemaninDegerleriniOku(eleman,isim));
                        break;
                    case CisimModeli::MomentDegeri:
                        yeniEleman->momentAta(elemaninDegerleriniOku(eleman,isim));
                        break;
                    default:
                        break;
                    }
                }
            }

            cisimModelListesi.append(yeniEleman);
        }
        n = n.nextSibling();
    }


}

double DosyaIslemleri::elemaninDegerleriniOku(QDomElement &eleman,QString &ozellikIsmi)
{
    bool tamam;
    double deger = eleman.firstChildElement(ozellikIsmi).text().toDouble(&tamam);

    return deger;
}

QDomNode DosyaIslemleri::ayarlariOku(QDomElement &kok)
{
    QDomNode n = kok.firstChild();

    int ayarSayisi = 0;
    Ayarlar ayarlarim;
    while (ayarSayisi < ayarlarim.ayarlarinIsimleriniAl().size()) {
        QDomElement ayar = n.toElement();
        int sira = ayarlarim.ayarlarinIsimleriniAl().key(ayar.tagName().replace("_"," "));
        QString ayarinDegeri = ayar.text();
        switch (sira) {
        case Ayarlar::UzunlugunBirimi:
        case Ayarlar::KuvvetinBirimi:
        case Ayarlar::MomentinBirimi:
            ayarlar.insert(sira,ayarinDegeri);
            break;
        default:
            break;
        }
        n = n.nextSibling();
        ayarSayisi++;
    }

    return n;
}
