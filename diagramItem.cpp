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
        int x1 = cisimModelim->baslangciKonumuAl();
        int x2 = cisimModelim->bitisKonumuAl();
        x = x1;
        y = 0;
        int y1 = -80;
        int y2 = -80;
        int yaziAcisi = 0;
        if (cisimModelim->baslangicKuvvetiAl() > 0) {
            painter->rotate(180);
            yaziAcisi = -180;
            x = x2;
        }

        if (abs(cisimModelim->baslangicKuvvetiAl()) < abs(cisimModelim->bitisKuvvetiAl())) {
            y1 = -40;
            y2 = -80;
        }else if (abs(cisimModelim->baslangicKuvvetiAl()) > abs(cisimModelim->bitisKuvvetiAl())){
            y1 = -80;
            y2 = -40;
        }

        if (yaziAcisi != 0) {
            int tmpY1 = y1;
            y1 = y2;
            y2 = tmpY1;
        }
        painter->drawPolygon(okBasiCiz(0,0));
        painter->drawPolygon(okGovdesiCiz(0,y1));

        painter->drawPolygon(okBasiCiz(x2-x1,0));
        painter->drawPolygon(okGovdesiCiz(x2-x1,y2));

        painter->drawLine(0,y1,x2-x1,y2);

        int yaziY1 = y1-10;
        int yaziY2 = y2-10;
        int yaziX1 = 0;
        int yaziX2 = x2-x1;
        if (yaziAcisi != 0) {
            yaziY1 = y2 * -1 + 15;
            yaziY2 = y1 * -1 + 15;
            yaziX1 = x1-x2;
            yaziX2 = 0;
        }

        painter->rotate(yaziAcisi);
        QString kuvvet1 = QString::number(cisimModelim->baslangicKuvvetiAl());
        painter->drawText(QPointF(yaziX1,yaziY1),kuvvet1);

        QString kuvvet2 = QString::number(cisimModelim->bitisKuvvetiAl());
        painter->drawText(QPointF(yaziX2,yaziY2),kuvvet2);


    }
        break;
    case Moment:
    {
        int derece = -360;
        int okBasiX = -32;
        int okBasiY = 52;
        int okAcisi = 80;
        int yaziAcisi = -80;
        int yaziX = -45;
        int yaziY = -45;
        qDebug() << "Moment "<<cisimModelim->momentAl();
        if (cisimModelim->momentAl() > 0) {
            derece = 360;
            okBasiX = 12;
            okBasiY = 55;
            okAcisi = 160;
            yaziAcisi = -160;
            yaziX = -30;
            yaziY = -45;
        }
        //https://stackoverflow.com/questions/19197381/how-to-draw-an-arc-with-qt
        //Yukarıdaki adresten faydalandım. Cuk oturdu.

        QPointF O(0,15); // intersection of lines
        QPointF B(45,-180); // end point of horizontal line
        QPointF A(-150,200); // end point of other line

        float halfSide = B.x()-O.x();
        QRectF rectangle(O.x() - halfSide,
                         O.y() - halfSide,
                         O.x() + halfSide,
                         O.y() + halfSide);

        int startAngle = 1700;
        int spanAngle = (atan2(A.y()-O.y(),A.x()-O.x()) * derece / M_PI) * 16;


        painter->drawArc(rectangle, startAngle, spanAngle);
        painter->rotate(okAcisi);// Bundan sonra x ve y aksıda bu açıya göre değişir.
        painter->drawPolygon(okBasiCiz(okBasiX,okBasiY));

        painter->rotate(yaziAcisi);
        QString moment = QString::number(cisimModelim->momentAl());
        painter->drawText(QPointF(yaziX,yaziY),moment);


        x = cisimModelim->noktaKonumuAl()+22;
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
    okGovdesi << QPointF(x,-30) << QPointF(x,h);
    return okGovdesi;
}

