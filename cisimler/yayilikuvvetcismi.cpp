#include "yayilikuvvetcismi.h"

YayiliKuvvetCismi::YayiliKuvvetCismi(CisimModeli *parent)
    : cisimModelim(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

QPainterPath YayiliKuvvetCismi::shape() const
{
    QPainterPath yol;
    yol.addRect(boundingRect());
    return yol;
}

void YayiliKuvvetCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    painter->setRenderHint(QPainter::Antialiasing);
    int x1 = cisimModelim->baslangciKonumuAl();
    int x2 = cisimModelim->bitisKonumuAl();
    x = x1;
    y = 0;
    cisimModelim->tipAta(CisimModeli::YayiliKuvvet);

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
    cisimAlani.setRect(x,y,(x2-x1),yaziY2);
}

QPolygonF YayiliKuvvetCismi::okBasiCiz(int x, int y)
{
    QPolygonF okBasi;
    okBasi << QPointF(x-10,y-30) << QPointF(x,y-10)
           << QPointF(x+10,y-30);

    return okBasi;
}

QPolygonF YayiliKuvvetCismi::okGovdesiCiz(int x, int h)
{
    QPolygonF okGovdesi;
    okGovdesi << QPointF(x,-30) << QPointF(x,h);
    return okGovdesi;
}
