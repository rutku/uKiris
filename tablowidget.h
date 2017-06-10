#ifndef TABLOWIDGET_H
#define TABLOWIDGET_H

#include "QTableWidget"

class CisimModeli;

QT_BEGIN_NAMESPACE
class QTableWidgetItem;

QT_END_NAMESPACE

class TabloWidget : public QTableWidget
{
    Q_OBJECT

public:
    TabloWidget(QWidget *parent = 0);

public slots:
    void cisimEkle(CisimModeli *cisimModeli);

private:

};

#endif // TABLOWIDGET_H
