#include "ankastremesnetcismi.h"

AnkastreMesnetCismi::AnkastreMesnetCismi(CisimModeli *parent)
    : cisimModelim(parent)
{
    tipim = cisimModelim->tipAl();
    siram = cisimModelim->siraAl();
}

QPainterPath AnkastreMesnetCismi::shape() const
{
    QPainterPath yol;
    yol.addRect(boundingRect());
    return yol;
}

void AnkastreMesnetCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    painter->setRenderHint(QPainter::Antialiasing);
    x = cisimModelim->noktaKonumuAl();
    y = 0;
    cisimModelim->tipAta(CisimModeli::AnkastreMesnet);

    qreal _x = x-40;
    qreal _y = -40;
    qreal w = 60;
    qreal h = 100;
    if (cisimModelim->noktaKonumuAl() != 0) {
        painter->rotate(180);
        _x = -1 * _x;
        _y = -1 * _y;
        w = -1*w;
        h = -1*h;
    }
    QPolygonF ankastreMesnetim;
    cisimAlani.setRect(_x,_y,w,h);

    ankastreMesnetim<< QPointF(-20,-40)
                    << QPointF(-20,-10) << QPointF(0,-10)
                    << QPointF(0,-5) << QPointF(10,-5)
                    << QPointF(10,5) << QPointF(0,5)
                    << QPointF(0,10) << QPointF(-20,10)
                    << QPointF(-20,40);

    painter->drawPolygon(ankastreMesnetim);
    for (int i = -30; i < 50; i+=10) {
        QPolygonF cizgi;
        cizgi << QPointF(-30,i-10) << QPointF (-20,i);
        painter->drawPolygon(cizgi);
    }
}
