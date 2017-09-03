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
    tipIsmim[DiagramItem::Kiris] = tr("Kiriş");
    tipIsmim[DiagramItem::SabitMesnet] = tr("Sabit Mesnet");
    tipIsmim[DiagramItem::HareketliMesnet] = tr("Hareketli Mesnet");
    tipIsmim[DiagramItem::AnkastreMesnet] = tr("Ankastre Mesnet");
    tipIsmim[DiagramItem::TekilKuvvet] = tr("Tekil Kuvvet");
    tipIsmim[DiagramItem::YayiliKuvvet] = tr("Yayılı Kuvvet");
    tipIsmim[DiagramItem::Moment] = tr("Moment");


}

CisimModeli::CisimModeli(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

QRectF CisimModeli::boundingRect() const
{

}

void CisimModeli::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

}
