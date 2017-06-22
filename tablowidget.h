#ifndef TABLOWIDGET_H
#define TABLOWIDGET_H

#include "QTableWidget"

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

public slots:
    void tabloyaCisimEkle(CisimModeli *cisimModeli);
    void tabloyuGuncelle(CisimModeli *cisimModeli);
signals:
    void cisimDuzenle(CisimModeli *_cisimModeli);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QList<CisimModeli*> cisimModelListesi;
    int simdikiSatir;
    int simdikiSutun;
    void tabloyaEkle(int satir,CisimModeli *cisimModeli);
};

#endif // TABLOWIDGET_H
