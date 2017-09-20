#ifndef TABLOWIDGET_H
#define TABLOWIDGET_H

#include "KMDiagramSahnesi.h"
#include <QMetaType>
#include <QTableWidget>
#include <QList>

class CisimModeli;
class DiagramItem;

QT_BEGIN_NAMESPACE
class QTableWidgetItem;
class QMouseEvent;
QT_END_NAMESPACE

class TabloWidget : public QTableWidget
{
    Q_OBJECT

public:
    TabloWidget(QWidget *parent = 0);
    QList<CisimModeli*> cisimModelListesiAl() { return cisimModelListesi; }
    void cisimSil();

public slots:
    void tabloyaCisimEkle(CisimModeli *cisimModeli);
    void tabloyuGuncelle(CisimModeli *cisimModeli);
    void diagramCiz();
signals:
    void cisimDuzenle(CisimModeli *_cisimModeli);
    void Sil(CisimModeli *_cisimModeli);
    void kesmeDiagramiCiz(QList<CisimModeli*> _cisimModelListesi);
    void momentDiagramiCiz(QList<CisimModeli*> _cisimModelListesi);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QList<CisimModeli*> cisimModelListesi;

    int simdikiSatir;
    int simdikiSutun;
    void tabloyaEkle(int satir,CisimModeli *cisimModeli);
    void siraAl(CisimModeli *cisim);
};

#endif // TABLOWIDGET_H
