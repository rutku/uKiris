#ifndef TABLOWIDGET_H
#define TABLOWIDGET_H

#include "QTableWidget"

QT_BEGIN_NAMESPACE
class QTableWidgetItem;

QT_END_NAMESPACE

class TabloWidget : public QTableWidget
{
public:
    TabloWidget(QWidget *parent = 0);
    void cisimEkle(int tip, int noktaKonumu,int noktaYuku,int baslangicKonumu,
                    int bitisKonumu, int baslangicYuku,int bitisYuku);

private:

};

#endif // TABLOWIDGET_H
