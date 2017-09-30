#include "sabitmesnetcismi.h"

SabitMesnetCismi::SabitMesnetCismi(CisimModeli *parent)
    : cisimModelim(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    tipim = cisimModelim->tipAl();
    siram = cisimModelim->siraAl();
}

QPainterPath SabitMesnetCismi::shape() const
{
    QPainterPath yol;
    yol.addRect(boundingRect());
    return yol;
}

void SabitMesnetCismi::konumuGuncelle()
{
//    setPos(x,y);
}

void SabitMesnetCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    painter->setRenderHint(QPainter::Antialiasing);
    QPolygonF sabitMesnetim;
    x = cisimModelim->noktaKonumuAl();
    y = 35;
    cisimModelim->tipAta(CisimModeli::SabitMesnet);

    cisimAlani.setRect(x-50,y-25,150,50);
    QPainterPath yol;
    yol.addRect(-50,25,100,10);
    sabitMesnetim = yol.toFillPolygon();
    sabitMesnetim << QPointF(-40,25) << QPointF(40,25)
              << QPointF(0,-25) << QPointF(-40,25);
    painter->drawPolygon(sabitMesnetim);
}
