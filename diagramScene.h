#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "diagramItem.h"
#include "cisimmodeli.h"
#include "cisimler/kirisCismi.h"
#include "cisimler/sabitmesnetcismi.h"
#include "cisimler/hareketlimesnetCismi.h"
#include "cisimler/ankastremesnetcismi.h"
#include "cisimler/tekilkuvvetcismi.h"
#include "cisimler/yayilikuvvetcismi.h"
#include "cisimler/momentcismi.h"


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
    enum Mode { CisimGir, CisimDuzenle, CisimSil ,CisimTasi};
    DiagramScene(QObject *parent = 0);

    QFont font() const { return fontum; }
    QColor cisimRengi() const { return cisimRengim;}
    void cisimRengiAta(const QColor &renk);
    ~DiagramScene();

public slots:
    void kipAta(Mode kip);
    void cisimIslemleri(CisimModeli *_cisimModeli = nullptr);

signals:
    void tabloyaCisimEkle(CisimModeli *cisimModeli);
    void tabloyuGuncelle(CisimModeli *cisimModeli);

private:
    CisimModeli *cisimModeli;
    DiagramItem *diagramItem;
    KirisCismi *kirisCismi;
    SabitMesnetCismi *sabitMesnetCismi;
    HareketliMesnetCismi *hareketliMesnet;
    AnkastreMesnetCismi *ankastreMesnetCismi;
    TekilKuvvetCismi *tekilKuvvetCismi;
    YayiliKuvvetCismi *yayiliKuvvetCismi;
    MomentCismi *momentCismi;
    Mode kipim;
    bool solButonAsagida;
    QPointF balangicNoktasi;
    QColor cisimRengim;
    QFont fontum;


};

#endif // DIAGRAMSCENE_H
