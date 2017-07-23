#ifndef KESMEDIAGRAMSAHNESI_H
#define KESMEDIAGRAMSAHNESI_H

#include "diagramItem.h"
#include "cisimmodeli.h"

#include <QGraphicsScene>
#include <QList>

QT_BEGIN_NAMESPACE
class QPen;
class DiagramItem;
class QLine;
QT_END_NAMESPACE


class KMDiagramSahnesi : public QGraphicsScene
{
    Q_OBJECT

public:
    KMDiagramSahnesi(QObject *parent = 0);

public slots:
    void kesmeDiagramiCiz(QList<CisimModeli *> _cisimModelListesi);

private:
    QList<CisimModeli*> cisimModelListesi;
    QList<CisimModeli*> enKucuktenCisimModelListesi;
    CisimModeli *_cisimModeli;
    void cisimleriSirala();
    double kuvvetleriTopla();
    void mesnetleriHesapla();
    double mesnetinKuvvetiniBul(DiagramItem::CisimTipi tip);
    void kesmeDiagraminiOlustur();
    void momentDiagraminiOlustur();
    double METRE = 0.01;
    double SANTIMETRE = 100;
    double kirisUzunlugu;
    double sabitMesnet;
    double hareketliMesnet;
    double ankastreMesnet;
    QMap<double,double> kesmeKuvvetlerininListesi;


};

#endif // KESMEDIAGRAMSAHNESI_H
