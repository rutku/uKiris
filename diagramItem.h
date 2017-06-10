#ifndef CISIMOGESI_H
#define CISIMOGESI_H

#include "cisimmodeli.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>

QT_BEGIN_NAMESPACE
class QPainter;
class QPolygonF;
class QPen;
QT_END_NAMESPACE

class CisimOgesi : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum {Tip = UserType + 15};
    enum CisimTipi {Kiris, SabitMesnet, HareketliMesnet, AnkastreMesnet,
                    TekilYuk, YayiliYuk, Moment};

    CisimOgesi(CisimTipi cisimTipi, CisimModeli *cisimModeli, QGraphicsItem *parent = nullptr);
    CisimOgesi(QGraphicsItem *parent = nullptr);

    virtual ~CisimOgesi();

    CisimTipi cisimTipi() const { return cisimTipim;  }
    int xAl() const { return x; }
    int yAl() const { return y; }
    int type() const override { return Tip; }

protected:
    virtual QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    CisimTipi cisimTipim;
    CisimModeli *cisimModelim;
    QGraphicsItem *cisimim;
    QRectF bound;
    int x;
    int y;

    QPolygonF kirisCiz();
    QPolygonF sabitMesnetCiz();
    QPolygonF hareketliMesnetCiz();

};

#endif // CISIMOGESI_H
