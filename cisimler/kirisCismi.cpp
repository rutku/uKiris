#include "kirisCismi.h"

#include <QPainter>
#include <QDebug>

KirisCismi::KirisCismi(CisimModeli *parent)
    : cisimModelim(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    tipim = cisimModelim->tipAl();
    siram = cisimModelim->siraAl();
}

QRectF KirisCismi::boundingRect() const
{
    return cisimAlani;
}

QPainterPath KirisCismi::shape() const
{
    QPainterPath yol;
    yol.addRect(boundingRect());
    return yol;
}

void KirisCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    painter->setRenderHint(QPainter::Antialiasing);
    QPolygonF kirisim;

    x = cisimModelim->baslangciKonumuAl();
    int uzunluk = cisimModelim->bitisKonumuAl() - cisimModelim->baslangciKonumuAl();
    y = 0;
    cisimAlani.setRect(x-1,-11,uzunluk+3,23);
    kirisim << QPointF(uzunluk, -10) << QPointF(0,-10)
              << QPointF(0,-5) << QPointF(10,-5)
              << QPointF(10,0) << QPointF(10,5)
              << QPointF(0,5)
              << QPointF(0, 10) << QPointF(uzunluk, 10)
              << QPointF(uzunluk,5) << QPointF((uzunluk-10),5)
              << QPointF((uzunluk-10),0) << QPointF((uzunluk-10),-5)
              << QPointF(uzunluk,-5) << QPointF(uzunluk, -10);
    painter->drawPolygon(kirisim);
}

KirisCismi::~KirisCismi()
{
    delete cisimModelim;
}
