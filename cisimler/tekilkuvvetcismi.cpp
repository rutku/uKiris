#include "tekilkuvvetcismi.h"

TekilKuvvetCismi::TekilKuvvetCismi(CisimModeli *parent)
    : cisimModelim(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    tipim = cisimModelim->tipAl();
    siram = cisimModelim->siraAl();
}

QPainterPath TekilKuvvetCismi::shape() const
{
    QPainterPath yol;
    yol.addRect(boundingRect());
    return yol;
}

void TekilKuvvetCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    painter->setRenderHint(QPainter::Antialiasing);
    cisimModelim->tipAta(CisimModeli::TekilKuvvet);

    if (cisimModelim->noktaKuvvetiAl() > 0){
        painter->rotate(180);

    }

    painter->drawPolygon(okBasiCiz(0,0));
    painter->drawPolygon(okGovdesiCiz(0,-80));
    QString kuvvet = QString::number(cisimModelim->noktaKuvvetiAl());
    painter->drawText(QPointF(0,-80),kuvvet);
    x = cisimModelim->noktaKonumuAl();
    y = 0;
    cisimAlani.setRect(x,y,20,-100);
}

QPolygonF TekilKuvvetCismi::okBasiCiz(int x, int y)
{
    QPolygonF okBasi;
    okBasi << QPointF(x-10,y-30) << QPointF(x,y-10)
           << QPointF(x+10,y-30);

    return okBasi;
}

QPolygonF TekilKuvvetCismi::okGovdesiCiz(int x, int h)
{
    QPolygonF okGovdesi;
    okGovdesi << QPointF(x,-30) << QPointF(x,h);
    return okGovdesi;
}
