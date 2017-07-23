#include "KMDiagramSahnesi.h"
#include "diagramItem.h"

#include <QDebug>

KMDiagramSahnesi::KMDiagramSahnesi(QObject *parent)
    : QGraphicsScene(parent)
{

}

void KMDiagramSahnesi::kesmeDiagramiCiz(QList<CisimModeli*> _cisimModelListesi)
{
    cisimModelListesi = _cisimModelListesi;

    int h = 500;
    QPen kalem(Qt::red,1,Qt::DashDotDotLine,Qt::RoundCap,Qt::RoundJoin);

    foreach (CisimModeli *cisim, cisimModelListesi) {
        switch (cisim->tipAl()) {
        case DiagramItem::Kiris:
        {
            int baslangic = cisim->baslangciKonumuAl();
            int bitis = cisim->bitisKonumuAl();
            kirisUzunlugu = bitis - baslangic;
            QLine cizgi(baslangic,(h/2),bitis,(h/2));
            addLine(cizgi);
            QLine dikeyCizgi1(baslangic,200,baslangic,300);
            QLine dikeyCizgi2(bitis,200,bitis,300);
            addLine(dikeyCizgi1);
            addLine(dikeyCizgi2);
        }
            break;
        case DiagramItem::SabitMesnet:
        {
            int noktaKonumu = cisim->noktaKonumuAl();

            QLine dikeyCizgi(noktaKonumu,0,noktaKonumu,h);
            addLine(dikeyCizgi,kalem);
        }
            break;
        case DiagramItem::HareketliMesnet:
        {
            int noktaKonumu = cisim->noktaKonumuAl();

            QLine dikeyCizgi(noktaKonumu,0,noktaKonumu,h);
            addLine(dikeyCizgi,kalem);
        }
            break;
        case DiagramItem::AnkastreMesnet:
        {
            int noktaKonumu = cisim->noktaKonumuAl();

            QLine dikeyCizgi(noktaKonumu,0,noktaKonumu,h);
            addLine(dikeyCizgi,kalem);
        }
            break;
        case DiagramItem::TekilKuvvet:
        {
            int noktaKonumu = cisim->noktaKonumuAl();

            QLine dikeyCizgi(noktaKonumu,0,noktaKonumu,h);
            addLine(dikeyCizgi,kalem);

        }
            break;
        case DiagramItem::YayiliKuvvet:
        {
            int baslangic = cisim->baslangciKonumuAl();
            int bitis = cisim->bitisKonumuAl();
            QLine dikeyCizgi1(baslangic,0,baslangic,h);
            QLine dikeyCizgi2(bitis,0,bitis,h);
            addLine(dikeyCizgi1,kalem);
            addLine(dikeyCizgi2,kalem);
        }
            break;
        case DiagramItem::Moment:
        {
            int noktaKonumu = cisim->noktaKonumuAl();

            QLine dikeyCizgi(noktaKonumu,0,noktaKonumu,h);
            addLine(dikeyCizgi,kalem);
        }
            break;
        default:
            break;
        }
    }
    cisimleriSirala();
}

void KMDiagramSahnesi::cisimleriSirala()
{
    QList<CisimModeli*> _cisimModelListesi(cisimModelListesi);

    QList<CisimModeli*> enBuyuktenCisimModelListesi;

    for (int i = 0; i < _cisimModelListesi.size(); ++i) {
        if (_cisimModelListesi.at(i)->tipAl() == DiagramItem::Kiris) {
            _cisimModelListesi.removeAt(i);
        }
    }

    int enBuyukKonum = 0;

    for (int i = 0; i < cisimModelListesi.size() -1 ; ++i) {
        int indis;
        for (int j = 0; j < _cisimModelListesi.size(); ++j) {
            CisimModeli *cisim = _cisimModelListesi.at(j);
            int konum = 0;

            if (cisim->tipAl() == DiagramItem::YayiliKuvvet) {
                konum = cisim->baslangciKonumuAl();
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

    mesnetleriHesapla();
    kesmeDiagraminiOlustur();
}

double KMDiagramSahnesi::kuvvetleriTopla()
{

    double toplamKuvvet = 0;
    foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
        if (cisim->tipAl() == DiagramItem::TekilKuvvet) {
            toplamKuvvet += cisim->noktaKuvvetiAl();
        }else if (cisim->tipAl() == DiagramItem::YayiliKuvvet) {
            double tabanUzunlugu = (cisim->bitisKonumuAl() - cisim->baslangciKonumuAl()) * METRE;
            double dikDortgenKuvveti = 0;
            double ucgenKuvveti = 0;

            if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
                dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
            }else if (abs(cisim->baslangicKuvvetiAl()) < abs(cisim->bitisKuvvetiAl())) {
                dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                ucgenKuvveti = (((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl())
                        * tabanUzunlugu)/2.0);
            }else if (abs(cisim->baslangicKuvvetiAl()) > abs(cisim->bitisKuvvetiAl())) {
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
        if (cisim->tipAl() ==  DiagramItem::AnkastreMesnet) {
            ankastreMesnet = -1 * kuvvetleriTopla();
        }else if (cisim->tipAl() == DiagramItem::SabitMesnet) {
            hareketliMesnet = -1 * (mesnetinKuvvetiniBul(DiagramItem::SabitMesnet));
            sabitMesnet = -1 * (kuvvetleriTopla()) - hareketliMesnet;
            break;

        }else if (cisim->tipAl() == DiagramItem::HareketliMesnet) {
            sabitMesnet = -1 * (mesnetinKuvvetiniBul(DiagramItem::HareketliMesnet));
            hareketliMesnet = -1 * (kuvvetleriTopla()) - hareketliMesnet;
            break;
        }
    }

}

double KMDiagramSahnesi::mesnetinKuvvetiniBul(DiagramItem::CisimTipi tip)
{
    double kuvvet = 0;

    foreach (CisimModeli *mesnet, enKucuktenCisimModelListesi) {
        double moment = 0;
        double noktaKonumu = 0;

        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (tip == cisim->tipAl()) {
                noktaKonumu = cisim->noktaKonumuAl() * METRE;
            }else if (DiagramItem::TekilKuvvet == cisim->tipAl()) {
                moment += (cisim->noktaKonumuAl() * METRE - noktaKonumu) * cisim->noktaKuvvetiAl();
            }else if (DiagramItem::YayiliKuvvet == cisim->tipAl()) {
                double tabanUzunlugu = (cisim->bitisKonumuAl() - cisim->baslangciKonumuAl()) * METRE;
                double dikDortgenKuvveti = 0;
                double ucgenKuvveti = 0;
                double dikdortgenMesafe = (cisim->baslangciKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu/2);
                double ucgenMesafe = 0;

                if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
                    dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                }else if (abs(cisim->baslangicKuvvetiAl()) < abs(cisim->bitisKuvvetiAl())) {
                    dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                    ucgenKuvveti = (((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl())
                            * tabanUzunlugu)/2.0);
                    ucgenMesafe = (cisim->baslangciKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu*(2.0/3.0));
                }else if (abs(cisim->baslangicKuvvetiAl()) > abs(cisim->bitisKuvvetiAl())) {
                    dikDortgenKuvveti = cisim->bitisKuvvetiAl() * tabanUzunlugu;
                    ucgenKuvveti = (1/2)*((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl())
                            * tabanUzunlugu);
                    ucgenMesafe = (cisim->baslangciKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu*(1.0/3.0));
                }

                moment += dikDortgenKuvveti * dikdortgenMesafe + ucgenKuvveti * ucgenMesafe;
            }else if (DiagramItem::Moment == cisim->tipAl()) {
                moment += cisim->momentAl();
            }
        }

        if (tip != mesnet->tipAl()) {
            if (mesnet->tipAl() == DiagramItem::SabitMesnet ||
                    mesnet->tipAl() == DiagramItem::HareketliMesnet) {
                double mesafe = mesnet->noktaKonumuAl() * METRE - noktaKonumu;
                kuvvet = moment / mesafe;
                break;
            }
        }
    }
    return kuvvet;

}

void KMDiagramSahnesi::kesmeDiagraminiOlustur()
{

    double x1 = 0;
    double x2 = 0;
    double y1 = 250.0;
    double y2 = 250.0;

    QPen kalem;
    for (int i = 0; i < kirisUzunlugu; ++i) {
        x2 = i;
        y2 = y2;
        addLine(x1,y1,x2,y2,kalem);
        x1 = x2;
        y1 = y2;
        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (cisim->tipAl() == DiagramItem::YayiliKuvvet) {
                if (i >= (int)cisim->baslangciKonumuAl() && i <= (int)cisim->bitisKonumuAl()) {
                    double tabanUzunlugu = (i - cisim->baslangciKonumuAl())/10000;
                    double dikdortgenKuvveti = 0;
                    double ucgenKuvveti = 0;
                    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
                        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                    }
                    else if (abs(cisim->baslangicKuvvetiAl()) < abs(cisim->bitisKuvvetiAl())) {
                        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                        ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                                tabanUzunlugu)/2;
                    }else {
                        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                        ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                                tabanUzunlugu)/2;
                    }
                    x2 = i;
                    y2 += (dikdortgenKuvveti+ucgenKuvveti);
                    QLine cizgi(x1,y1,x2,y2);
                    addLine(cizgi,kalem);
                    x1 = x2;
                    y1 = y2;
                }
            }else if (cisim->tipAl() == DiagramItem::TekilKuvvet &&
                      i == (int)cisim->noktaKonumuAl()) {
                x2 = i;
                y2 += cisim->noktaKuvvetiAl();
                addLine(x1,y1,x2,y2,kalem);
                x1 = x2;
                y1 = y2;
            }else if (cisim->tipAl() == DiagramItem::SabitMesnet &&
                      i == (int)cisim->noktaKonumuAl()) {
                x2 = i;
                y2 += sabitMesnet;
                addLine(x1,y1,x2,y2,kalem);
                x1 = x2;
                y1 = y2;
            }else if (cisim->tipAl() == DiagramItem::HareketliMesnet &&
                      i == (int)cisim->noktaKonumuAl()) {
                x2 = i;
                y2 += hareketliMesnet;
                addLine(x1,y1,x2,y2,kalem);
                x1 = x2;
                y1 = y2;
            }else if (cisim->tipAl() == DiagramItem::AnkastreMesnet &&
                      i == (int)cisim->noktaKonumuAl()) {
                x2 = i;
                y2 += ankastreMesnet;
                addLine(x1,y1,x2,y2,kalem);
                x1 = x2;
                y1 = y2;
            }

        }
    }
}

void KMDiagramSahnesi::momentDiagraminiOlustur()
{
    double x1 = 0;
    double x2 = 0;
    double y1 = 250.0;
    double y2 = 250.0;

    QPen kalem;

    CisimModeli momentNoktasiAlinanCisim;
    int baslangicNoktasi;
    foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
        if (cisim->tipAl() == DiagramItem::AnkastreMesnet) {
            momentNoktasiAlinanCisim = cisim;
            baslangicNoktasi = cisim->noktaKonumuAl();
        }
    }

    for (int i = 0; i < kirisUzunlugu; ++i) {
        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (cisim->tipAl() == DiagramItem::YayiliKuvvet) {
                if (i >= (int)cisim->baslangciKonumuAl() && i <= (int)cisim->bitisKonumuAl()) {
                    double tabanUzunlugu = (i - cisim->baslangciKonumuAl())/10000;
                    double dikdortgenKuvveti = 0;
                    double ucgenKuvveti = 0;
                    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
                        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                    }
                    else if (abs(cisim->baslangicKuvvetiAl()) < abs(cisim->bitisKuvvetiAl())) {
                        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                        ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                                tabanUzunlugu)/2;
                    }else {
                        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                        ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                                tabanUzunlugu)/2;
                    }
                    x2 = i;
                    y2 += (dikdortgenKuvveti+ucgenKuvveti);
                    QLine cizgi(x1,y1,x2,y2);
                    addLine(cizgi,kalem);
                    x1 = x2;
                    y1 = y2;
                }
            }else if (cisim->tipAl() == DiagramItem::TekilKuvvet &&
                      i == (int)cisim->noktaKonumuAl()) {
                x2 = i;
                y2 += cisim->noktaKuvvetiAl();
                addLine(x1,y1,x2,y2,kalem);
                x1 = x2;
                y1 = y2;
            }else if (cisim->tipAl() == DiagramItem::SabitMesnet &&
                      i == (int)cisim->noktaKonumuAl()) {
                x2 = i;
                y2 += sabitMesnet;
                addLine(x1,y1,x2,y2,kalem);
                x1 = x2;
                y1 = y2;
            }else if (cisim->tipAl() == DiagramItem::HareketliMesnet &&
                      i == (int)cisim->noktaKonumuAl()) {
                x2 = i;
                y2 += hareketliMesnet;
                addLine(x1,y1,x2,y2,kalem);
                x1 = x2;
                y1 = y2;
            }else if (cisim->tipAl() == DiagramItem::AnkastreMesnet &&
                      i == (int)cisim->noktaKonumuAl()) {
                x2 = i;
                y2 += ankastreMesnet;
                addLine(x1,y1,x2,y2,kalem);
                x1 = x2;
                y1 = y2;
            }

        }
    }
}
