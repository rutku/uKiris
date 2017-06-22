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
        emit tabloyaCisimEkle(_cisimModeli);
        break;
    case CisimDuzenle:
        emit tabloyuGuncelle(_cisimModeli);
        break;
    default:
        ;
    }
    QGraphicsScene::update(0,0,0,0);
}

void DiagramScene::cisimBul(CisimModeli *_cisimModeli)
{
    foreach (QGraphicsItem *cisim, items(Qt::AscendingOrder)) {
        DiagramItem *_cisim = qgraphicsitem_cast<DiagramItem *>(cisim);

        if (_cisim->cisimModeliAl() == _cisimModeli) {
            qDebug() << "Cisim : " << _cisim->scenePos() << " Tipi : " << _cisim->cisimTipi();
        }
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

        qDebug() << "Cisim : " << _cisim->cisimModeliAl()->bitisKonumuAl() << " Tipi : " << _cisim->cisimTipi();
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

