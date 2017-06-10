#include "cisimogesi.h"
#include "cisimmodeli.h"

#include <QPainter>

CisimOgesi::CisimOgesi(CisimTipi cisimTipi,CisimModeli *cisimModeli, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    cisimTipim = cisimTipi;
    cisimModelim = cisimModeli;
}

CisimOgesi::CisimOgesi(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

CisimOgesi::~CisimOgesi()
{

}

QRectF CisimOgesi::boundingRect() const
{
    return bound;
}

void CisimOgesi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    switch (cisimTipim) {
    case Kiris:
        painter->drawPolygon(kirisCiz());
        break;
    case SabitMesnet:
        painter->drawPolygon(sabitMesnetCiz());
        break;
    case HareketliMesnet:
        painter->drawPolygon(hareketliMesnetCiz());
        break;
    default:
        break;
    }

    setPos(xAl(),yAl());
}

QPolygonF CisimOgesi::kirisCiz()
{
    QPolygonF kirisim;

    cisimModelim->tipAta(Kiris);
    x = cisimModelim->bitisKonumuAl();
    y = 0;

//    kirisim << QPointF(-x, -10) << QPointF(x, -10)
//              << QPointF(x,-5) << QPointF((x-10),-5)
//              << QPointF((x-10),0) << QPointF((x-10),5)
//              << QPointF(x,5)
//              << QPointF(x, 10) << QPointF(-x, 10)
//              << QPointF(-x,5) << QPointF(-(x-10),5)
//              << QPointF(-(x-10),0) << QPointF(-(x-10),-5)
//              << QPointF(-x,-5) << QPointF(-x, -10);

    kirisim << QPointF(-x, -10) << QPointF(0,-10)
              << QPointF(0,-5) << QPointF(-10,-5)
              << QPointF(-10,0) << QPointF(-10,5)
              << QPointF(0,5)
              << QPointF(0, 10) << QPointF(-x, 10)
              << QPointF(-x,5) << QPointF(-(x-10),5)
              << QPointF(-(x-10),0) << QPointF(-(x-10),-5)
              << QPointF(-x,-5) << QPointF(-x, -10);

    return kirisim;
}

QPolygonF CisimOgesi::sabitMesnetCiz()
{
    QPolygonF sabitMesnetim;
    x = cisimModelim->noktaKonumuAl();
    y = 35;
    QPainterPath yol;
    yol.addRect(-50,25,100,10);
    sabitMesnetim = yol.toFillPolygon();
    sabitMesnetim << QPointF(-40,25) << QPointF(40,25)
              << QPointF(0,-25) << QPointF(-40,25);
    return sabitMesnetim;
}

QPolygonF CisimOgesi::hareketliMesnetCiz()
{
    QPolygonF hareketliMesnetim;
    x = cisimModelim->noktaKonumuAl();
    y = 60;
    QPainterPath yol;
    yol.arcTo(-25, 0, 50, -50, 90, 360);
    yol.addRect(-50,0,100,10);
    hareketliMesnetim = yol.toFillPolygon();

    return hareketliMesnetim;
}
