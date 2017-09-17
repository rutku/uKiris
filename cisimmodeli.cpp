#include "cisimmodeli.h"
#include "diagramItem.h"

CisimModeli::CisimModeli(int tip, int noktaKonumu, int noktaKuvveti, int baslangicKonumu, int bitisKonumu, int baslangicKuvveti, int bitisKuvveti, int moment, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    _tip = tip;
    _noktaKonumu = noktaKonumu;
    _noktaKuvveti = noktaKuvveti;
    _baslangicKonumu = baslangicKonumu;
    _bitisKonumu = bitisKonumu;
    _baslangicKuvveti = baslangicKuvveti;
    _bitisKuvveti = bitisKuvveti;
    _moment = moment;
    
    tipIsimleriOlustur();
    degerlerinIsimleriniOlustur();
}

CisimModeli::CisimModeli(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    tipIsimleriOlustur();
    degerlerinIsimleriniOlustur();
}

void CisimModeli::tipIsimleriOlustur()
{
    tipIsmim[Kiris] = tr("Kiriş");
    tipIsmim[SabitMesnet] = tr("Sabit Mesnet");
    tipIsmim[HareketliMesnet] = tr("Hareketli Mesnet");
    tipIsmim[AnkastreMesnet] = tr("Ankastre Mesnet");
    tipIsmim[TekilKuvvet] = tr("Tekil Kuvvet");
    tipIsmim[YayiliKuvvet] = tr("Yayılı Kuvvet");
    tipIsmim[Moment] = tr("Moment");

}

void CisimModeli::degerlerinIsimleriniOlustur()
{
    degerlerim.insert(Tip,tr("Tip"));
    degerlerim.insert(Sira,tr("Sıra"));
    degerlerim.insert(NoktaKonumu,tr("Nokta Konumu"));
    degerlerim.insert(NoktaKuvveti,tr("Nokta Kuvveti"));
    degerlerim.insert(BaslangicKonumu,tr("Başlangıç Konumu"));
    degerlerim.insert(BaslangicKuvveti,tr("Başlangıç Kuvveti"));
    degerlerim.insert(BitisKonumu,tr("Bitiş Konumu"));
    degerlerim.insert(BitisKuvveti,tr("Bitiş Kuvveti"));
    degerlerim.insert(MomentDegeri,tr("Moment"));
}

QRectF CisimModeli::boundingRect() const
{

}

void CisimModeli::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

}
