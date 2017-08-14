#include "KMDiagramSahnesi.h"
#include "diagramItem.h"

#include <QDebug>

KMDiagramSahnesi::KMDiagramSahnesi(QObject *parent)
    : QGraphicsScene(parent)
{

}

void KMDiagramSahnesi::kesmeDiagramiCiz(QList<CisimModeli *> _cisimModelListesi)
{
    diagramim = KesmeDiagrami;
    cisimModelListesi = _cisimModelListesi;
    diagramCiz();
}

void KMDiagramSahnesi::momentDiagramiCiz(QList<CisimModeli *> _cisimModelListesi)
{
    diagramim = MomentDiagrami;
    cisimModelListesi = _cisimModelListesi;
    diagramCiz();
}

void KMDiagramSahnesi::diagramCiz()
{
    diagramlariCiz();
    cisimleriSirala();
    mesnetleriHesapla();

    double h = 250;
    double x1 = 0;
    double x2 = 0;
    double y1 = h;
    double y2 = h;
    double moment = 0.0;
    double enBuyukMoment = 0.0;
    double kesmeKuvveti = 0.0;
    double tekilKuvvet = 0.0;
    double yayiliKuvvet = 0.0;
    double hareketliMesnetKuvveti = 0.0;
    double sabitMesnetKuvveti = 0.0;
    double ankastreMesnetKuvveti = 0.0;
    double tekilKuvvetMomenti = 0.0;
    double sabitMesnetMomenti = 0.0;
    double yayiliMoment = 0.0;
    double noktaMomenti = 0.0;
    double dikdortgenKuvveti = 0.0;
    double dikdortgenKuvvetiKonumu = 0.0;
    double ucgenKuvveti = 0.0;
    double ucgenKuvvetiKonumu = 0.0;
    double hareketliMesnetMomenti = 0.0;
    double ankastreMesnetMomenti = 0.0;

    QPen kalem;
    for (int i = 0; i < kirisUzunlugu; ++i) {
        QLine diagramCizgisi;
        x2 = i;
        y2 = y2;
        addLine(x1,y1,x2,y2,kalem);
        x1 = x2;
        y1 = y2;

        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (cisim->tipAl() == DiagramItem::YayiliKuvvet) {
                if (i >= (int)cisim->baslangciKonumuAl() && i <= (int)cisim->bitisKonumuAl()) {

                    double tabanUzunlugu = (i - cisim->baslangciKonumuAl());
                    dikdortgenKuvveti = 0;
                    dikdortgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+(tabanUzunlugu/2));
                    ucgenKuvveti = 0;
                    ucgenKuvvetiKonumu = 0.0;

                    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
                        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                    }

                    else if (abs(cisim->baslangicKuvvetiAl()) < abs(cisim->bitisKuvvetiAl())) {
                        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                        ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                                tabanUzunlugu)/2;
                        ucgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+(tabanUzunlugu*2.0)/3.0);
                    }else {
                        dikdortgenKuvveti = cisim->bitisKuvvetiAl() * tabanUzunlugu;
                        ucgenKuvveti = ((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl()) *
                                tabanUzunlugu)/2;
                        ucgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+(tabanUzunlugu/3.0));
                    }
                    yayiliKuvvet = (dikdortgenKuvveti+ucgenKuvveti) / 100;
                    yayiliMoment = ((dikdortgenKuvveti * dikdortgenKuvvetiKonumu) +
                            (ucgenKuvveti * ucgenKuvvetiKonumu)) / 100;
                }else if (i > (int)cisim->bitisKonumuAl()) {
                    dikdortgenKuvvetiKonumu = i -(cisim->baslangciKonumuAl()+(cisim->bitisKonumuAl()-cisim->baslangciKonumuAl())/2);
                    ucgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+((cisim->bitisKonumuAl()-cisim->baslangciKonumuAl())*2)/3);
                    if (abs(cisim->baslangicKuvvetiAl()) > abs(cisim->bitisKuvvetiAl())) {
                         ucgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+(cisim->bitisKonumuAl()-cisim->baslangciKonumuAl())/3);
                    }
                    yayiliMoment = (((dikdortgenKuvveti * dikdortgenKuvvetiKonumu)) +
                            (ucgenKuvveti * ucgenKuvvetiKonumu)) / 100;
                }
            }else if (cisim->tipAl() == DiagramItem::TekilKuvvet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    tekilKuvvet = cisim->noktaKuvvetiAl();
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    tekilKuvvetMomenti = (tekilKuvvet * (i - cisim->noktaKonumuAl()));
                }

            }else if (cisim->tipAl() == DiagramItem::SabitMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    sabitMesnetKuvveti = cisim->noktaKuvvetiAl();
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    sabitMesnetMomenti = (sabitMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == DiagramItem::HareketliMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    hareketliMesnetKuvveti = cisim->noktaKuvvetiAl();
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    hareketliMesnetMomenti = (hareketliMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == DiagramItem::AnkastreMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    ankastreMesnetKuvveti = cisim->noktaKuvvetiAl();
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    ankastreMesnetMomenti = (ankastreMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == DiagramItem::Moment && i == cisim->noktaKonumuAl()) {
                noktaMomenti = cisim->momentAl() * 100;
            }
        }
        kesmeKuvveti = (tekilKuvvet + yayiliKuvvet + sabitMesnetKuvveti + hareketliMesnetKuvveti +
                ankastreMesnetKuvveti) * 10;
        moment = (tekilKuvvetMomenti + yayiliMoment + sabitMesnetMomenti + hareketliMesnetMomenti +
                  ankastreMesnetMomenti+noktaMomenti)/10;
        if (enBuyukMoment<abs(moment)) {
            enBuyukMoment = moment;
        }

        x2 = i;
        if (diagramim == KesmeDiagrami) {
            y2 = kesmeKuvveti + h;
        }else {
            y2 = moment + h;
        }
        diagramCizgisi.setLine(x1,y1,x2,y2);
        x1 = x2;
        y1 = y2;
        addLine(diagramCizgisi,kalem);
    }

    qDebug() << "En Büyük Moment = " << enBuyukMoment;

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
            qDebug() << "Ankastre Mesnet " << ankastreMesnet;
        }else if (cisim->tipAl() == DiagramItem::SabitMesnet) {
            hareketliMesnet = -1 * mesnetinKuvvetiniBul(DiagramItem::SabitMesnet);
            sabitMesnet = -1 * (kuvvetleriTopla() + hareketliMesnet);
            cisim->noktaKuvvetiAta(sabitMesnet);
            qDebug() << "Sabit Mesnet" << sabitMesnet;
            qDebug() << "Hareketli Mesnet" << hareketliMesnet;
        }else if (cisim->tipAl() == DiagramItem::HareketliMesnet) {
            cisim->noktaKuvvetiAta(hareketliMesnet);
            break;
        }
        /*TODO:Sabit Mesnet -> Sabit Mesnet veya Hareketli Mesnet -> Hareketli Mesnet durumları
         incelenecek ! */
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
                moment -= cisim->momentAl();
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

void KMDiagramSahnesi::diagramlariCiz()
{
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

}
