#ifndef MOMENTCISMI_H
#define MOMENTCISMI_H

#include "cisimmodeli.h"

#include <QPainter>
#include <QtMath>

class MomentCismi : public CisimModeli
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum {Tip = CisimModeli::Moment };
    MomentCismi(CisimModeli *parent = nullptr);
    int type() const override { return Tip; }
    int tipAl() { return tipim;}
    int siraAl() { return siram; }
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

    QPolygonF okBasiCiz(int x,int y);
    int tipim;
    int siram;


};

#endif // MOMENTCISMI_H
