#include "hareketlimesnetCismi.h"
#include <QDebug>

HareketliMesnetCismi::HareketliMesnetCismi(CisimModeli *parent)
    : cisimModelim(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    tipim = cisimModelim->tipAl();
    siram = cisimModelim->siraAl();
}

QPainterPath HareketliMesnetCismi::shape() const
{
    QPainterPath yol;
    yol.addRect(boundingRect());
    return yol;
}

void HareketliMesnetCismi::konumuGuncelle()
{
//    qDebug() << "Değişti";

//    QGraphicsItem *cisim = mapToItem(children().first(),cisimAlani.x(),cisimAlani.y(),cisimAlani.width(),cisimAlani.height());
//    setParentItem(cisim);
}

void HareketliMesnetCismi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    prepareGeometryChange();
    painter->setRenderHint(QPainter::Antialiasing);
    QPolygonF hareketliMesnetim;
    x = cisimModelim->noktaKonumuAl();
    y = 60;
    cisimModelim->tipAta(CisimModeli::HareketliMesnet);

    cisimAlani.setRect(x-50,y-25,150,50);
    QPainterPath yol;
    yol.arcTo(-25, 0, 50, -50, 90, 360);
    yol.addRect(-50,0,100,10);
    hareketliMesnetim = yol.toFillPolygon();
    painter->drawPolygon(hareketliMesnetim);
}

QVariant HareketliMesnetCismi::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        konumuGuncelle();
    }

    return value;
}
