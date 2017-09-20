#ifndef YAYILIKUVVETCISMI_H
#define YAYILIKUVVETCISMI_H

#include "cisimmodeli.h"

#include <QPainter>
#include <QPainterPath>
#include <QtMath>

class YayiliKuvvetCismi : public CisimModeli
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum {Tip = CisimModeli::YayiliKuvvet };
    YayiliKuvvetCismi(CisimModeli *parent = nullptr);
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
    QPolygonF okGovdesiCiz(int x, int h);

    int tipim;
    int siram;

};

#endif // YAYILIKUVVETCISMI_H
