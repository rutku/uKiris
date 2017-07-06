#ifndef TEKILKUVVETEKLE_H
#define TEKILKUVVETEKLE_H

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

class TekilKuvvetEkle : public QDialog
{

    Q_OBJECT

public:
    enum yonGrubu { Asagi, Yukari};
    TekilKuvvetEkle(QWidget *parent = nullptr);
    ~TekilKuvvetEkle();
    int noktaKonumuAl() { return noktaKonumu; }
    int tekilKuvvetAl() { return tekilKuvvet; }
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
    int tekilKuvvet;
    int yon;//Aşağı = -1, Yukarı=1
    CisimModeli *cisimModeli;
    DiagramScene::Mode kipim;
    QLabel *lblNoktaKonumu;
    QLabel *lblTekilKuvvet;

    QLineEdit *txtNoktaKonumu;
    QLineEdit *txtTekilKuvvet;

    QPushButton *btnTamam;
    QPushButton *btnIptal;
    QToolButton *btnAsagi;
    QToolButton *btnYukari;

    QButtonGroup *btnYonGrubu;
};

#endif // TEKILKUVVETEKLE_H
