#ifndef MESNETEKLE_H
#define MESNETEKLE_H

#include "cisimmodeli.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class MesnetEkle : public QDialog
{
    Q_OBJECT

public:
    MesnetEkle(QWidget *parent = 0);
    CisimModeli *cisimModeliAl() { return cisimModeli; }
    void tipAta(int tip) { _tip = tip; }

private slots:
    void ekleButonunaTiklandi();

signals:
    void cisimEkle(CisimModeli *cisimModeli);

private:
    QLabel *lblNokta;
    QLineEdit *txtNokta;
    QPushButton *btnEkle;
    QPushButton *btnIptal;
    int _tip;
    CisimModeli *cisimModeli;
};

#endif // MESNETEKLE_H
