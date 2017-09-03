#ifndef KIRIS_H
#define KIRIS_H

#include "cisimmodeli.h"

#include <QPainter>

class KirisCismi : public CisimModeli
{
    Q_OBJECT

public:
    enum {Tip = CisimModeli::Kiris };
    KirisCismi(CisimModeli *parent = nullptr);
    int type() const override { return Tip; }
    virtual QRectF boundingRect() const override;
    QPainterPath shape() const override;
    CisimModeli *cisimModeliAl(){ return cisimModelim; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    virtual ~KirisCismi();
    CisimModeli *cisimModelim;
    qreal x;
    qreal y;
    QRectF cisimAlani;
};

#endif // KIRIS_H
