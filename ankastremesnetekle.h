#ifndef ANKASTREMESNETEKLE_H
#define ANKASTREMESNETEKLE_H

#include "cisimmodeli.h"
#include "diagramScene.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QButtonGroup;
class QToolButton;
QT_END_NAMESPACE

class AnkastreMesnetEkle : public QDialog
{
    Q_OBJECT

public:
    enum yonGrubu {Sol, Sag};
    AnkastreMesnetEkle(QWidget *parent = nullptr);
    ~AnkastreMesnetEkle();
    int noktaKonumuAl() { return noktaKonumu; }
    void kirisUzunluguAta(int uzunluk) { kirisUzunlugu = uzunluk; }
    CisimModeli *cisimModeliAl() { return cisimModeli; }
    void cisimModeliAta(CisimModeli *_cisimModeli) { cisimModeli = _cisimModeli; }
    void kipAta(DiagramScene::Mode _kip) { kipim = _kip; }

private slots:
    void tamamButonunaTiklandi();
    void yonGrubunaTiklandi(int id);

signals:
    void cisimEkle(CisimModeli *cisimModeli);

private:
    int noktaKonumu;
    int yon;//Sağ = -1, Sol = 1
    int kirisUzunlugu;
    CisimModeli *cisimModeli;
    DiagramScene::Mode kipim;

    QPushButton *btnTamam;
    QPushButton *btnIptal;
    QToolButton *btnSag;
    QToolButton *btnSol;


    QButtonGroup *btnYonGrubu;


};

#endif // ANKASTREMESNETEKLE_H
