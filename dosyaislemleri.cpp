#include "dosyaislemleri.h"

#include <QDebug>

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
