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

    xmlAkisiYaz.writeTextElement("UzunluğunBirimi","cm");
    xmlAkisiYaz.writeTextElement("KuvvetinBirimi","kN");
    xmlAkisiYaz.writeTextElement("MomentinBirimi","kN.m");
    foreach (auto cisim, cisimModeliListesi) {
        auto tipIsmi = cisim->tipIsmiAl().replace(" ","");
        xmlAkisiYaz.writeStartElement(tipIsmi);
        xmlAkisiYaz.writeTextElement("NoktaKonumu",QString("%1").arg(cisim->noktaKonumuAl()));
        xmlAkisiYaz.writeTextElement("NoktaKuvveti",QString("%1").arg(cisim->noktaKuvvetiAl()));
        xmlAkisiYaz.writeTextElement("BaşlangıçKonumu",QString("%1").arg(cisim->baslangciKonumuAl()));
        xmlAkisiYaz.writeTextElement("BaşlangıçKuvveti",QString("%1").arg(cisim->baslangicKuvvetiAl()));
        xmlAkisiYaz.writeTextElement("BitişKonumu",QString("%1").arg(cisim->bitisKonumuAl()));
        xmlAkisiYaz.writeTextElement("BitişKuvveti",QString("%1").arg(cisim->bitisKuvvetiAl()));
        xmlAkisiYaz.writeTextElement("Moment",QString("%1").arg(cisim->momentAl()));
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
    ayarlariOku(kok);
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

void DosyaIslemleri::cisimleriOku(QDomElement &kok)
{
    CisimModeli cisim;

    foreach (auto tipIsmi, cisim.tipIsimleriAl().values()) {
        int tip = cisim.tipIsimleriAl().key(tipIsmi);
        tipIsmi = tipIsmi.replace(" ","");
        QDomElement eleman = kok.firstChildElement(tipIsmi);
        if (!eleman.isNull()) {
            CisimModeli *yeniEleman = new CisimModeli();
            foreach (auto deger, yeniEleman->degerlerinIsimleriniAl().keys()) {
                QString isim = yeniEleman->degerlerinIsimleriniAl().value(deger);
                isim = isim.replace(" ","");
                if (!isim.isEmpty()) {
                    switch (deger) {
                    case CisimModeli::Tip:
                        yeniEleman->tipAta(tip);
                        yeniEleman->tipIsmiAta(cisim.tipIsimleriAl().value(tip));
                        break;
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
    }


}

double DosyaIslemleri::elemaninDegerleriniOku(QDomElement &eleman,QString &ozellikIsmi)
{
    bool tamam;
    double deger = eleman.firstChildElement(ozellikIsmi).text().toDouble(&tamam);

    return deger;
}

void DosyaIslemleri::ayarlariOku(QDomElement &kok)
{
    Ayarlar ayarlarim;
    foreach (auto ayarIsmi, ayarlarim.ayarlarinIsimleriniAl().values()) {
        int ayar = ayarlarim.ayarlarinIsimleriniAl().key(ayarIsmi);
        ayarIsmi = ayarIsmi.replace(" ","");
        QString ayarinDegeri = kok.firstChildElement(ayarIsmi).text();
        switch (ayar) {
        case Ayarlar::UzunlugunBirimi:
            ayarlar.insert(Ayarlar::UzunlugunBirimi,ayarinDegeri);
            break;
        case Ayarlar::KuvvetinBirimi:
            ayarlar.insert(Ayarlar::KuvvetinBirimi,ayarinDegeri);
            break;
        case Ayarlar::MomentinBirimi:
            ayarlar.insert(Ayarlar::MomentinBirimi,ayarinDegeri);
            break;
        default:
            break;
        }
    }
}
