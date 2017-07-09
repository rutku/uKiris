#include "diagramItem.h"
#include "cisimmodeli.h"

#include <QPainter>
#include <QMetaEnum>
#include <QDebug>
#include <QtMath>

DiagramItem::DiagramItem(CisimModeli *cisimModeli, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    cisimTipim = CisimTipi(cisimModeli->tipAl());
    cisimModelim = cisimModeli;


}

DiagramItem::DiagramItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

DiagramItem::~DiagramItem()
{

}

QRectF DiagramItem::boundingRect() const
{
    return bound;
}

void DiagramItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    case AnkastreMesnet:
        if (cisimModelim->noktaKonumuAl() != 0) {
            painter->rotate(180);
        }
        painter->drawPolygon(ankastreMesnetCiz());
        for (int i = -30; i < 50; i+=10) {
            QPolygonF cizgi;
            cizgi << QPointF(-30,i-10) << QPointF (-20,i);
            painter->drawPolygon(cizgi);
        }
        break;
    case TekilKuvvet:
    {
        if (cisimModelim->noktaKuvvetiAl() > 0){
            painter->rotate(180);

        }

        painter->drawPolygon(okBasiCiz(0,0));
        painter->drawPolygon(okGovdesiCiz(0,-80));
        QString kuvvet = QString::number(cisimModelim->noktaKuvvetiAl());
        painter->drawText(QPointF(0,-80),kuvvet);
        x = cisimModelim->noktaKonumuAl();
        y = 0;
    }
        break;
    case YayiliKuvvet:
    {
        if (cisimModelim->baslangicKuvvetiAl() > 0) {
            painter->rotate(180);
        }
        int x1 = cisimModelim->baslangciKonumuAl();
        int x2 = cisimModelim->bitisKonumuAl();
        x = x1;
        y = 0;
        int y1 = -80;
        int y2 = -80;

        if (cisimModelim->baslangicKuvvetiAl() < cisimModelim->bitisKuvvetiAl()) {
            y1 = -40;
            y2 = -80;
        }else if (cisimModelim->baslangicKuvvetiAl() > cisimModelim->bitisKuvvetiAl()){
            y1 = -80;
            y2 = -40;
        }
        painter->drawPolygon(okBasiCiz(0,0));
        painter->drawPolygon(okGovdesiCiz(0,y1));

        painter->drawPolygon(okBasiCiz(x2-x1,0));
        painter->drawPolygon(okGovdesiCiz(x2-x1,y2));

        painter->drawLine(0,y1,x2-x1,y2);
    }
        break;
    case Moment:
    {
        QPointF O(0,15); // intersection of lines
        QPointF B(45,-180); // end point of horizontal line
        QPointF A(-150,200); // end point of other line

        float halfSide = B.x()-O.x();
        QRectF rectangle(O.x() - halfSide,
                         O.y() - halfSide,
                         O.x() + halfSide,
                         O.y() + halfSide);

        int startAngle = 1700;
        int spanAngle = (atan2(A.y()-O.y(),A.x()-O.x()) * -360 / M_PI) * 16;
        painter->drawArc(rectangle, startAngle, spanAngle);
        painter->rotate(80);// Bundan sonra x ve y aksıda bu açıya göre değişir.
        painter->drawPolygon(okBasiCiz(-32,52));

        x = cisimModelim->noktaKonumuAl();
        y = 0;
    }
        break;

    default:
        break;
    }

    setPos(xAl(),yAl());
}

QPolygonF DiagramItem::kirisCiz()
{
    QPolygonF kirisim;

    cisimModelim->tipAta(Kiris);
    x = cisimModelim->bitisKonumuAl();
    y = 0;

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

QPolygonF DiagramItem::sabitMesnetCiz()
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

QPolygonF DiagramItem::hareketliMesnetCiz()
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

QPolygonF DiagramItem::ankastreMesnetCiz()
{
    QPolygonF ankastreMesnetim;
    x = cisimModelim->noktaKonumuAl();
    y = 0;

    ankastreMesnetim<< QPointF(-20,-40)
                    << QPointF(-20,-10) << QPointF(0,-10)
                    << QPointF(0,-5) << QPointF(10,-5)
                    << QPointF(10,5) << QPointF(0,5)
                    << QPointF(0,10) << QPointF(-20,10)
                    << QPointF(-20,40);


    return ankastreMesnetim;
}

QPolygonF DiagramItem::okBasiCiz(int x,int y)
{
    QPolygonF okBasi;
    okBasi << QPointF(x-10,y-30) << QPointF(x,y-10)
           << QPointF(x+10,y-30);

    return okBasi;
}

QPolygonF DiagramItem::okGovdesiCiz(int x, int h)
{
    QPolygonF okGovdesi;
    okGovdesi << QPointF(x,-10) << QPointF(x,h);
    return okGovdesi;
}

