#include "momentcismi.h"

MomentCismi::MomentCismi(CisimModeli *parent)
    : cisimModelim(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    tipim = cisimModelim->tipAl();
    siram = cisimModelim->siraAl();
}

QPainterPath MomentCismi::shape() const
{
    QPainterPath yol;
    yol.addRect(boundingRect());
    return yol;
}

void MomentCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    cisimModelim->tipAta(CisimModeli::Moment);
    painter->setRenderHint(QPainter::Antialiasing);
    int derece = -360;
    int okBasiX = -32;
    int okBasiY = 52;
    int okAcisi = 80;
    int yaziAcisi = -80;
    int yaziX = -45;
    int yaziY = -45;
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
    cisimAlani.setRect(x,y,200,200);
}

QPolygonF MomentCismi::okBasiCiz(int x, int y)
{
    QPolygonF okBasi;
    okBasi << QPointF(x-10,y-30) << QPointF(x,y-10)
           << QPointF(x+10,y-30);

    return okBasi;
}
