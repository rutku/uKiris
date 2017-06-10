#include "diagramScene.h"
#include "kirisCismi.h"

#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    cisimMenum = itemMenu;
    kipim = CisimTasi;
    cisimTipim = CisimOgesi::Kiris;
    cisimRengim  = Qt::white;
}

void DiagramScene::kipAta(DiagramScene::Mode kip)
{
    kipim = kip;
}

void DiagramScene::cisimTipiAta(CisimOgesi::CisimTipi type)
{
    cisimTipim = type;
}

void DiagramScene::cisimModeliAta(CisimModeli *cm)
{
    cisimModeli = cm;
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    switch (kipim) {
    case CisimGir:
        cisimOgesi = new CisimOgesi(cisimTipim,cisimModeli);
        addItem(cisimOgesi);
        emit cisimGirildi(cisimOgesi);
        break;
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    foreach (QGraphicsItem *cisim, items(Qt::AscendingOrder)) {
        CisimOgesi *_cisim = qgraphicsitem_cast<CisimOgesi *>(cisim);

        qDebug() << "Cisim : " << _cisim->scenePos() << " Tipi : " << _cisim->cisimTipi();
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::cisimDegisti(int tip)
{
    foreach (QGraphicsItem *cisim, selectedItems()) {
        if (cisim->type() == tip) {
            return true;
        }
    }
    return false;
}

void DiagramScene::cisimEkle()
{

}

