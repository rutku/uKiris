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

    qDebug() << "Cisim Sayısı : " << _cisimModelListesi.size();

    int enBuyukKonum = 0;

    foreach (CisimModeli *cisim, _cisimModelListesi) {
        int konum = 0;

        if (cisim->tipAl() == DiagramItem::YayiliKuvvet) {
            konum = cisim->baslangciKonumuAl();
        }else
        {
            if (cisim->tipAl() != DiagramItem::Kiris) {
                konum = cisim->noktaKonumuAl();
            }
        }

        if (enBuyukKonum < konum) {
            enBuyukKonum = konum;
            _cisimModeli = cisim;
        }
    }

    _cisimModelListesi.removeOne(_cisimModeli);

    qDebug() << "En Büyük Konum"<< enBuyukKonum;


}
