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

    double h = 250;
    double x2 = 0;
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

    QPen kalem(Qt::black,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    for (int i = 0; i <= kirisUzunlugu; ++i) {
        QLine diagramCizgisi;
        tekilKuvvetMomenti = 0.0;
        yayiliMoment =0.0;

        bool sinirda = false;

        x2 = i;
        y2 = y2;


        foreach (CisimModeli *cisim, enKucuktenCisimModelListesi) {
            if (cisim->tipAl() == CisimModeli::YayiliKuvvet) {
                if (i >= (int)cisim->baslangciKonumuAl() && i <= (int)cisim->bitisKonumuAl()) {

                    if (i == cisim->baslangciKonumuAl() || i == cisim->bitisKonumuAl()) {
                        sinirda = true;
                    }

                    yayiliKuvvet = yayiliIcKuvvet(cisim,i);
                    yayiliMoment = yayiliIcMoment(cisim,i);

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
                ankastreMesnetKuvveti) * 10;

        moment = (tekilKuvvetMomenti + yayiliMoment + sabitMesnetMomenti + hareketliMesnetMomenti +
                  ankastreMesnetMomenti + ankastreMomenti + noktaMomenti)/10;
//        qDebug()<<"i["<<i<<"]TKM:"<<tekilKuvvetMomenti<<"YKM:"<<yayiliMoment<<"SMKM:"<<sabitMesnetMomenti<<"HMKM:"<<hareketliMesnetMomenti
//               << "AMKM:"<<ankastreMesnetMomenti<<" M:"<<moment/10;


        //Hesaplanan Yük(lerin)ün ve Mesnetlerin Kuvvet ve Moment Diyagramları Aşağıda çiziliyor.
        x2 = i;
        if (diagramim == KesmeDiagrami) {
            kesmeKuvvetleri.append(QVector2D(i,kesmeKuvveti));
            y2 = kesmeKuvveti + h;
            if (sinirda) {
                if (kesmeKuvveti != tmpKesmeKuvveti) {
                    kesmeKuvvetleri.insert((kesmeKuvvetleri.size()-1),QVector2D(i,tmpKesmeKuvveti));
                }
            }
        }else {
            momentler.append(QVector2D(i,moment));
            if (CisimModeli::AnkastreMesnet || CisimModeli::TekilKuvvet) { // Kesmenin Sıfır olduğu kısımdaki Momenti buluyoruz.
                if (qFabs(tmpKesmeKuvveti) > 1 && qFabs(kesmeKuvveti) <= 1) {
                    sinirda = true;
                }
            }
            y2 = moment + h;
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
                if (cisim->noktaKonumuAl() == k.x() && cisim->bitisKonumuAl() == k.x())
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

            if (cisim->tipAl() == CisimModeli::YayiliKuvvet) {
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
        if (cisim->tipAl() == CisimModeli::TekilKuvvet) {
            toplamKuvvet += cisim->noktaKuvvetiAl();
        }else if (cisim->tipAl() == CisimModeli::YayiliKuvvet) {
            double tabanUzunlugu = (cisim->bitisKonumuAl() - cisim->baslangciKonumuAl()) * METRE;
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
                double tabanUzunlugu = (cisim->bitisKonumuAl() - cisim->baslangciKonumuAl()) * METRE;
                double dikDortgenKuvveti = 0;
                double ucgenKuvveti = 0;
                double dikdortgenMesafe = (cisim->baslangciKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu/2);
                double ucgenMesafe = 0;

                if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
                    dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                }else if (qFabs(cisim->baslangicKuvvetiAl()) < qFabs(cisim->bitisKuvvetiAl())) {
                    dikDortgenKuvveti = cisim->baslangicKuvvetiAl() * tabanUzunlugu;
                    ucgenKuvveti = (((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl())
                            * tabanUzunlugu)/2.0);
                    ucgenMesafe = (cisim->baslangciKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu*(2.0/3.0));
                }else if (qFabs(cisim->baslangicKuvvetiAl()) > qFabs(cisim->bitisKuvvetiAl())) {
                    dikDortgenKuvveti = cisim->bitisKuvvetiAl() * tabanUzunlugu;
                    ucgenKuvveti = (1/2)*((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl())
                            * tabanUzunlugu);
                    ucgenMesafe = (cisim->baslangciKonumuAl() * METRE - noktaKonumu) + (tabanUzunlugu*(1.0/3.0));
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


double KMDiagramSahnesi::yayiliIcKuvvet(CisimModeli *cisim, int i)
{
    double dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * (i - cisim->baslangciKonumuAl());
    double ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                                                  (i-cisim->baslangciKonumuAl()))/2.0;


    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * (i - cisim->baslangciKonumuAl());
    }else {
        dikdortgenKuvveti = cisim->bitisKuvvetiAl() * (i - cisim->baslangciKonumuAl());
        ucgenKuvveti = ((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl()) *
                (i - cisim->baslangciKonumuAl()))/2.0;
    }
    return ((dikdortgenKuvveti+ucgenKuvveti) / 100.0);
}

double KMDiagramSahnesi::yayiliIcMoment(CisimModeli *cisim, int i)
{
    double dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * (i - cisim->baslangciKonumuAl());
    double dikdortgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+((i - cisim->baslangciKonumuAl())/2.0));
    double ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                                                  (i-cisim->baslangciKonumuAl()))/2.0;
    double ucgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+((i - cisim->baslangciKonumuAl()*2.0)/3.0));


    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * (i - cisim->baslangciKonumuAl());
    }else {
        dikdortgenKuvveti = cisim->bitisKuvvetiAl() * (i - cisim->baslangciKonumuAl());
        ucgenKuvveti = ((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl()) *
                (i - cisim->baslangciKonumuAl()))/2.0;
        ucgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+((i - cisim->baslangciKonumuAl())/3.0));
    }
    return (((dikdortgenKuvveti * dikdortgenKuvvetiKonumu) +
             (ucgenKuvveti * ucgenKuvvetiKonumu)) / 100.0);
}

double KMDiagramSahnesi::yayiliDisMoment(CisimModeli *cisim, int i)
{
    double dikdortgenKuvvetiKonumu = i -(cisim->baslangciKonumuAl()+(cisim->bitisKonumuAl()-cisim->baslangciKonumuAl())/2.0);
    double dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * (cisim->bitisKonumuAl() - cisim->baslangciKonumuAl());
    double ucgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+((cisim->bitisKonumuAl()-cisim->baslangciKonumuAl())*2.0)/3.0);
    double ucgenKuvveti = ((cisim->bitisKuvvetiAl() - cisim->baslangicKuvvetiAl()) *
                           (cisim->bitisKonumuAl()-cisim->baslangciKonumuAl()))/2.0;

    if (cisim->baslangicKuvvetiAl() == cisim->bitisKuvvetiAl()) {
        dikdortgenKuvveti = cisim->baslangicKuvvetiAl() * (cisim->bitisKonumuAl()-cisim->baslangciKonumuAl());

    }else if (qFabs(cisim->baslangicKuvvetiAl()) > qFabs(cisim->bitisKuvvetiAl())) {
        dikdortgenKuvveti = cisim->bitisKuvvetiAl() * (cisim->bitisKonumuAl() - cisim->baslangciKonumuAl());
        ucgenKuvvetiKonumu = i - (cisim->baslangciKonumuAl()+(cisim->bitisKonumuAl()-cisim->baslangciKonumuAl())/3.0);
        ucgenKuvveti = ((cisim->baslangicKuvvetiAl() - cisim->bitisKuvvetiAl()) *
                                    (cisim->bitisKonumuAl()-cisim->baslangciKonumuAl()))/2.0;
    }
    return ((((dikdortgenKuvveti * dikdortgenKuvvetiKonumu)) +
            (ucgenKuvveti * ucgenKuvvetiKonumu)) / 100.0);

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
