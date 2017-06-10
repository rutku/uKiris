#include "diagramScene.h"

#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    cisimMenum = itemMenu;
    kipim = CisimTasi;
    cisimRengim  = Qt::white;

}

void DiagramScene::kipAta(DiagramScene::Mode kip)
{
    kipim = kip;
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
        cisimOgesi = new DiagramItem(cisimModeli);
        addItem(cisimOgesi);
        emit cisimGirildi(cisimOgesi);
        emit tabloyaCisimEkle(cisimModeli);
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
        DiagramItem *_cisim = qgraphicsitem_cast<DiagramItem *>(cisim);

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

