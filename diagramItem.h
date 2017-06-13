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

class DiagramItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum {Tip = UserType + 15};
    enum CisimTipi {Kiris, SabitMesnet, HareketliMesnet, AnkastreMesnet,
                    TekilYuk, YayiliYuk, Moment};

    DiagramItem(CisimModeli *cisimModeli, QGraphicsItem *parent = nullptr);
    DiagramItem(QGraphicsItem *parent = nullptr);

    virtual ~DiagramItem();

    CisimTipi cisimTipi() const { return cisimTipim;  }

    int xAl() const { return x; }
    int yAl() const { return y; }
    int type() const override { return Tip; }
    QMap<int,QString> tipIsmiAl() { return tipIsmim; }

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

    QMap<int,QString> tipIsmim;
    QPolygonF kirisCiz();
    QPolygonF sabitMesnetCiz();
    QPolygonF hareketliMesnetCiz();

};

#endif // CISIMOGESI_H
