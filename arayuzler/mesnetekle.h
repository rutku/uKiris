#ifndef MESNETEKLE_H
#define MESNETEKLE_H

#include "cisimmodeli.h"
#include "diagramScene.h"

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
    ~MesnetEkle();
    CisimModeli *cisimModeliAl() { return cisimModeli; }
    void cisimModeliAta(CisimModeli *_cisimModeli) { cisimModeli = _cisimModeli; }
    void kipAta(DiagramScene::Mode kip) { kipim = kip; }
    void tipAta(int tip) { _tip = tip; }
    void kirisUzunluguGir(int uzunluk) { kirisUzunlugu = uzunluk; }

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
    int kirisUzunlugu;
    CisimModeli *cisimModeli;
    DiagramScene::Mode kipim;
};

#endif // MESNETEKLE_H
