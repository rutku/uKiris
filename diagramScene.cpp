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

void DiagramScene::cisimEkle(CisimModeli *_cisimModeli)
{
    if (_cisimModeli == nullptr) {
        return;
    }
    switch (kipim) {
    case CisimGir:
        diagramItem = new DiagramItem(_cisimModeli);
        addItem(diagramItem);
        emit cisimGirildi(diagramItem);
        emit tabloyaCisimEkle(_cisimModeli);
        break;
    default:
        ;
    }
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) {
        return;
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

