#ifndef HAREKETLIMESNET_H
#define HAREKETLIMESNET_H

#include "cisimmodeli.h"

#include <QPainter>

class HareketliMesnetCismi : public CisimModeli
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum {Tip = CisimModeli::HareketliMesnet };
    HareketliMesnetCismi(CisimModeli *parent = nullptr);
    int type() const override { return Tip; }
    virtual QRectF boundingRect() const override { return cisimAlani; }
    QPainterPath shape() const override;
    CisimModeli *cisimModeliAl(){ return cisimModelim; }
    void konumuGuncelle();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    CisimModeli *cisimModelim;
    qreal x;
    qreal y;
    QRectF cisimAlani;

};

#endif // HAREKETLIMESNET_H
