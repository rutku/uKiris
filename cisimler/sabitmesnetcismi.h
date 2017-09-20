#ifndef SABITMESNETCISMI_H
#define SABITMESNETCISMI_H

#include "cisimmodeli.h"

#include <QPainter>

class SabitMesnetCismi : public CisimModeli
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum {Tip = CisimModeli::SabitMesnet};
    SabitMesnetCismi(CisimModeli *parent = nullptr);
    int type() const override { return Tip; }
    int tipAl() { return tipim;}
    int siraAl() { return siram; }
    virtual QRectF boundingRect() const override { return cisimAlani; }
    QPainterPath shape() const override;
    CisimModeli *cisimModeliAl(){ return cisimModelim; }
    void konumuGuncelle();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    CisimModeli *cisimModelim;
    qreal x;
    qreal y;
    QRectF cisimAlani;

    int tipim;
    int siram;
};

#endif // SABITMESNETCISMI_H
