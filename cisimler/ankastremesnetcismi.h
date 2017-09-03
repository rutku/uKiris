#ifndef ANKASTREMESNETCISMI_H
#define ANKASTREMESNETCISMI_H

#include "cisimmodeli.h"
#include <QPainter>

class AnkastreMesnetCismi : public CisimModeli
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum { Tip = CisimModeli::AnkastreMesnet };
    AnkastreMesnetCismi(CisimModeli *parent = nullptr);
    int type() const override { return Tip; }
    virtual QRectF boundingRect() const override { return cisimAlani; }
    QPainterPath shape() const override;
    CisimModeli *cisimModeliAl(){ return cisimModelim; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
private:
    CisimModeli *cisimModelim;
    qreal x;
    qreal y;
    QRectF cisimAlani;

};

#endif // ANKASTREMESNETCISMI_H
