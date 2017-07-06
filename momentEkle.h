#ifndef MOMENTEKLE_H
#define MOMENTEKLE_H

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

class MomentEkle : public QDialog
{
    Q_OBJECT

public:
    enum yonGrubu {Sag, Sol};
    MomentEkle(QWidget *parent = nullptr);
    ~MomentEkle();
    int noktaKonumuAl() { return noktaKonumu; }
    int momentAl() { return moment; }
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
    int moment;
    int yon;//Sağ = -1, Sol = 1
    CisimModeli *cisimModeli;
    DiagramScene::Mode kipim;

    QLabel *lblNoktaKonumu;
    QLabel *lblMoment;

    QLineEdit *txtNoktaKonumu;
    QLineEdit *txtMoment;
    QPushButton *btnTamam;
    QPushButton *btnIptal;
    QToolButton *btnSag;
    QToolButton *btnSol;

    QButtonGroup *btnYonGrubu;



};

#endif // MOMENTEKLE_H
