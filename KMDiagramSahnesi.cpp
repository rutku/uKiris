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
    cisimleriSirala();
    mesnetleriHesapla();

    double h = 250;
    double x1 = 0;
    double x2 = 0;
    double y1 = h;
    double y2 = h;
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
    double dikdortgenKuvveti = 0.0;
    double dikdortgenKuvvetiKonumu = 0.0;
    double ucgenKuvveti = 0.0;
    double ucgenKuvvetiKonumu = 0.0;

    QPen kalem(Qt::black,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    for (int i = 0; i <= kirisUzunlugu; ++i) {
        QLine diagramCizgisi;

        bool sinirda = false;

        x2 = i;
        y2 = y2;
        addLine(x1,y1,x2,y2,kalem); // Kiriş Ve moment Diyagramının ilk burada çiziliyor.
        x1 = x2;// Ardından ikinci çizginin çizilmesi için aşağıda hesaplar yapılıyor.
        y1 = y2;


        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (cisim->tipAl() == DiagramItem::YayiliKuvvet) {
                if (i >= (int)cisim->baslangciKonumuAl() && i <= (int)cisim->bitisKonumuAl()) {

                    if (i == cisim->baslangciKonumuAl() || i == cisim->bitisKonumuAl()) {
                        sinirda = true;
                    }
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
                    sinirda = true;
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    tekilKuvvetMomenti = (tekilKuvvet * (i - cisim->noktaKonumuAl()));
                }

            }else if (cisim->tipAl() == DiagramItem::SabitMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    sabitMesnetKuvveti = cisim->noktaKuvvetiAl();
                    sinirda = true;
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    sabitMesnetMomenti = (sabitMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == DiagramItem::HareketliMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    hareketliMesnetKuvveti = cisim->noktaKuvvetiAl();
                    sinirda = true;
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    hareketliMesnetMomenti = (hareketliMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == DiagramItem::AnkastreMesnet) {
                if (i == (int)cisim->noktaKonumuAl()) {
                    ankastreMesnetKuvveti = cisim->noktaKuvvetiAl();
                    ankastreMesnetMomenti = cisim->momentAl() * 100;
                    sinirda = true;
                }else if (i > (int)cisim->noktaKonumuAl()) {
                    ankastreMomenti = (ankastreMesnetKuvveti * (i - cisim->noktaKonumuAl()));
                }
            }else if (cisim->tipAl() == DiagramItem::Moment && i == cisim->noktaKonumuAl()) {
                noktaMomenti = cisim->momentAl() * 100;
                sinirda = true;
            }
        }
        //TODO:moment değişkeni ve xNoktasindakiMoment değişkeni düzeltilmeli!
        kesmeKuvveti = (tekilKuvvet + yayiliKuvvet + sabitMesnetKuvveti + hareketliMesnetKuvveti +
                ankastreMesnetKuvveti) * 10;

        moment = (tekilKuvvetMomenti + yayiliMoment + sabitMesnetMomenti + hareketliMesnetMomenti +
                  ankastreMesnetMomenti + ankastreMomenti + noktaMomenti)/10;

        //Hesaplanan Yük(lerin)ün ve Mesnetlerin Kuvvet ve Moment Diyagramları Aşağıda çiziliyor.
        x2 = i;
        if (diagramim == KesmeDiagrami) {
            y2 = kesmeKuvveti + h;
            if (sinirda) {
                ucKuvvetler.append(QVector2D(i,kesmeKuvveti));
            }
        }else {
            y2 = moment + h;
            if (sinirda) {
                if (ankastreMesnetMomenti != 0
                        && moment == 0
                        && ankastreMomenti == 0) {
                    ucMomentler.append(QVector2D(i,(moment-(ankastreMesnetMomenti/10.0))));
                }else {
                    ucMomentler.append(QVector2D(i,moment));
                }
            }
        }

        diagramCizgisi.setLine(x1,y1,x2,y2);
        x1 = x2;
        y1 = y2;
        addLine(diagramCizgisi,kalem);


    }
    QPen kirisKalemi(Qt::red,2,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin);
    QGraphicsLineItem *kiris = addLine(0,h,kirisUzunlugu,h,kirisKalemi);
    kiris->setZValue(kiris->zValue() - 0.1);
    uclariCiz();

}

void KMDiagramSahnesi::uclariCiz()
{
    QPen kalem(Qt::blue,2,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin);

    QList<QVector2D> kuvvetler;
    QString kuvvetYazisi;
    int kuvvetXPozisyonu;

    if (diagramim == KesmeDiagrami) {
        kuvvetler = ucKuvvetler;
        kuvvetYazisi = tr("Kuvvet(kN)");
        kuvvetXPozisyonu = -100;
    }else {
        kuvvetler = ucMomentler;
        kuvvetYazisi = tr("Moment(kN.m)");
        kuvvetXPozisyonu = -130;
    }

    double enBuyukKuvvet = 0.0;
    double enKucukKuvvet = 0.0;
    foreach (QVector2D y, kuvvetler) {
        if (enBuyukKuvvet < y.y()) {
            enBuyukKuvvet = y.y();
        }
        if (y.y() < 0.0) {
            if (abs(enKucukKuvvet) < abs(y.y())) {
                enKucukKuvvet = y.y();
            }
        }
    }

    double h = 250.0;
    double xEksenininYsi = enBuyukKuvvet + h + 50;
    double yEksenininYsi = enKucukKuvvet + h - 50;
    double xEksenininXsi = kirisUzunlugu + 50;

    addLine(-20,xEksenininYsi,xEksenininXsi,xEksenininYsi,kalem);//->(x)
    QGraphicsTextItem *xMesafeYazisi = addText("x(cm)");
    xMesafeYazisi->setPos(xEksenininXsi,xEksenininYsi);

    addLine(-20,xEksenininYsi,-20,yEksenininYsi,kalem);//->(Kuvvet || Moment)
    QGraphicsTextItem *kuvvetYazisininPozisyonu = addText(kuvvetYazisi);
    kuvvetYazisininPozisyonu->setPos(kuvvetXPozisyonu,yEksenininYsi - 15);

    kalem.setStyle(Qt::SolidLine);
    QGraphicsPolygonItem *xOku = addPolygon(okCiz(-1),kalem);
    xOku->setPos(xEksenininXsi,xEksenininYsi);

    QGraphicsPolygonItem *kuvvetOku = addPolygon(okCiz(0),kalem);
    kuvvetOku->setPos(-20,yEksenininYsi);

    kalem.setStyle(Qt::DashDotDotLine);



    foreach (QVector2D x, kuvvetler) {
        kalem.setColor(Qt::green);
        QGraphicsLineItem *xEkseni = addLine(x.x(),x.y()+h,x.x(),xEksenininYsi,kalem);//->(x)
        xEkseni->setZValue(xEkseni->zValue()-0.1);
        QGraphicsTextItem *mesafe = addText(QString("%1").arg(x.x()));
        mesafe->setPos(x.x(),xEksenininYsi);
        if (x.y() != 0.0) {
            kalem.setColor(Qt::cyan);
            QGraphicsLineItem *yEkseni =  addLine(-20,x.y()+h,x.x(),x.y()+h,kalem);//->(Kuvvet || Moment)
            yEkseni->setZValue(xEkseni->zValue()-0.1);
            QString _kuvvet = QString("%1").arg(x.y()/10.0);
            QGraphicsTextItem *kuvvet = addText(_kuvvet);
            kuvvet->setPos(-1*(_kuvvet.size()*3+50),x.y()+h-15);
        }

    }

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
        if (_cisimModelListesi.at(i)->tipAl() == DiagramItem::Kiris) {
            kirisUzunlugu = _cisimModelListesi.at(i)->bitisKonumuAl() - _cisimModelListesi.at(i)->baslangciKonumuAl();
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
            cisim->noktaKuvvetiAta(ankastreMesnet);
            mesnetinKuvvetiniBul(DiagramItem::AnkastreMesnet);
        }else if (cisim->tipAl() == DiagramItem::SabitMesnet) {
            hareketliMesnet = -1 * mesnetinKuvvetiniBul(DiagramItem::SabitMesnet);
            sabitMesnet = -1 * (kuvvetleriTopla() + hareketliMesnet);
            cisim->noktaKuvvetiAta(sabitMesnet);
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
    double noktaKonumu = 0;
    foreach (CisimModeli *mesnet, enKucuktenCisimModelListesi) {
        if (tip == mesnet->tipAl()) {
            noktaKonumu = mesnet->noktaKonumuAl() * METRE;
        }
    }

    foreach (CisimModeli *mesnet, enKucuktenCisimModelListesi) {
        double moment = 0;

        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (DiagramItem::TekilKuvvet == cisim->tipAl()) {
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
        if (mesnet->tipAl() == DiagramItem::AnkastreMesnet) {
            mesnet->momentAta(moment);
        }
    }
    return kuvvet;

}
