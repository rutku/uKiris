#include "kirisCismi.h"

#include <QPen>
#include <QPainter>

KirisCismi::KirisCismi(int uzunluk, QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{

    kirisUzunlugu = uzunluk;
    rengim = Qt::black;
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setPen(QPen(rengim,2,Qt::SolidLine));
}


QPainterPath KirisCismi::shape() const
{
    QPainterPath path = QGraphicsPolygonItem::shape();
    path.addPolygon(cisim);
    return path;
}

void KirisCismi::konumuGuncelle()
{

}

void KirisCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen kalem = pen();
    kalem.setColor(rengim);
    painter->setPen(kalem);
    painter->setBrush(rengim);

    int x = kirisUzunlugu;

    cisim << QPointF(-x, -10) << QPointF(x, -10)
              << QPointF(x,-5) << QPointF((x-10),-5)
              << QPointF((x-10),0) << QPointF((x-10),5)
              << QPointF(x,5)
              << QPointF(x, 10) << QPointF(-x, 10)
              << QPointF(-x,5) << QPointF(-(x-10),5)
              << QPointF(-(x-10),0) << QPointF(-(x-10),-5)
              << QPointF(-x,-5) << QPointF(-x, -10);

    painter->drawPolygon(cisim);

}
