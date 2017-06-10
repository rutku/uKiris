#ifndef KIRIS_H
#define KIRIS_H

#include <QGraphicsPolygonItem>

#include "diagramitem.h"

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QPainterPath;
class QWidget;
class QPolygonF;
class QPainter;
class QGraphicsItem;
class QStyleOptionGraphicsItem;
QT_END_NAMESPACE

class KirisCismi : public QGraphicsPolygonItem
{
public:
    enum {Type = UserType + 15};

    KirisCismi(int uzunluk, QGraphicsItem *parent = 0);

    int type() const override { return Type; }
    QPainterPath shape() const override;
    void renkBelirle(const QColor &renk) { rengim = renk;}
    void konumuGuncelle();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
    QColor rengim;
    QPolygonF cisim;
    int kirisUzunlugu;
};

#endif // KIRIS_H
