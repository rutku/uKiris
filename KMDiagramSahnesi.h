#ifndef KESMEDIAGRAMSAHNESI_H
#define KESMEDIAGRAMSAHNESI_H

#include "diagramItem.h"
#include "cisimmodeli.h"

#include <QGraphicsScene>
#include <QList>
#include <QtMath>

QT_BEGIN_NAMESPACE
class QPen;
class DiagramItem;
class QLine;
QT_END_NAMESPACE


class KMDiagramSahnesi : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Diagram { KesmeDiagrami, MomentDiagrami };
    KMDiagramSahnesi(QObject *parent = 0);

public slots:
    void kesmeDiagramiCiz(QList<CisimModeli *> _cisimModelListesi);
    void momentDiagramiCiz(QList<CisimModeli *> _cisimModelListesi);

private:
    QList<CisimModeli*> cisimModelListesi;
    QList<CisimModeli*> enKucuktenCisimModelListesi;    

    QList<QVector2D> kesmeKuvvetleri;
    QList<QVector2D> momentler;
    QList<QVector2D> ucKuvvetler;
    QList<QVector2D> ucMomentler;

    CisimModeli *_cisimModeli;
    Diagram diagramim;
    void cisimleriSirala();
    double kuvvetleriTopla();
    void mesnetleriHesapla();
    double mesnetinKuvvetiniBul(CisimModeli::CisimTipi tip);
    void diagramlariCiz();
    void kesmeDiagraminiOlustur();
    void momentDiagraminiOlustur();
    void eksenleriCiz();
    void sinirlardakiKuvvetleriCiz();
    double enBuyukKuvvetiAl(QList<QVector2D> kuvvetListesi);
    double enKucukKuvvetiAl(QList<QVector2D> kuvvetListesi);
    double yayiliIcKuvvet(CisimModeli *cisim, int i);
    double yayiliIcMoment(CisimModeli *cisim, int i);
    double yayiliDisMoment(CisimModeli *cisim, int i);
    QVector2D enBuyukMomentiAl();
    double METRE = 0.01;
    double SANTIMETRE = 100;
    double kirisUzunlugu;
    double sabitMesnet;
    double hareketliMesnet;
    double ankastreMesnet;
    QList<double> kesmeKuvvetlerininListesi;
    void hesapla();
    QPolygonF okCiz(int yon/*-1 = Kuvvet || Moment ; 0 = x*/);

};

#endif // KESMEDIAGRAMSAHNESI_H
