#ifndef TEKILKUVVETCISMI_H
#define TEKILKUVVETCISMI_H

#include "cisimmodeli.h"

#include <QPainter>

class TekilKuvvetCismi : public CisimModeli
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum {Tip = CisimModeli::TekilKuvvet };
    TekilKuvvetCismi(CisimModeli *parent = nullptr);
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

    QPolygonF okBasiCiz(int x,int y);
    QPolygonF okGovdesiCiz(int x, int h);


};

#endif // TEKILKUVVETCISMI_H
