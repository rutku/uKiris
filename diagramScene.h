#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "diagramItem.h"
#include "cisimmodeli.h"

#include <QGraphicsScene>
#include <QDebug>
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { CisimGir, CisimTasi};

    explicit DiagramScene(QMenu *itemMenu, QObject *parent = 0);
    QFont font() const { return fontum; }
    QColor cisimRengi() const { return cisimRengim;}
    void cisimRengiAta(const QColor &renk);

public slots:
    void kipAta(Mode kip);
    void cisimTipiAta(CisimOgesi::CisimTipi type);
    void cisimModeliAta(CisimModeli *cm);

signals:
    void cisimGirildi(CisimOgesi *cisim);
    void cisimSecildi(CisimOgesi *cisim);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool cisimDegisti(int tip);
    void cisimEkle();
    CisimOgesi::CisimTipi cisimTipim;
    CisimModeli *cisimModeli;
    CisimOgesi *cisimOgesi;
    QMenu *cisimMenum;
    Mode kipim;
    bool solButonAsagida;
    QPointF balangicNoktasi;
    QColor cisimRengim;
    QFont fontum;


};

#endif // DIAGRAMSCENE_H
