#ifndef YAYILIKUVVETEKLE_H
#define YAYILIKUVVETEKLE_H

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

class YayiliKuvvetEkle : public QDialog
{
    Q_OBJECT

public:
    enum yonGrubu { Asagi, Yukari};
    YayiliKuvvetEkle(QWidget *parent = nullptr);
    ~YayiliKuvvetEkle();
    int baslangiNoktasiAl() { return baslangicKonumu; }
    int bitisNoktasiAl() { return bitisKonumu; }
    int baslangicKuvvetiAl() { return baslangicKuvveti; }
    int bitisKuvvetiAl() { return bitisKuvveti; }
    CisimModeli *cisimModeliAl() { return cisimModeli; }
    void cisimModeliAta(CisimModeli *_cisimModeli) { cisimModeli = _cisimModeli; }
    void kipAta(DiagramScene::Mode _kip) { kipim = _kip; }

private slots:
    void tamamButonunaTiklandi();
    void yonGrubunaTiklandi(int id);

signals:
    void cisimEkle(CisimModeli *cisimModeli);

private:
    int baslangicKonumu;
    int bitisKonumu;
    int baslangicKuvveti;
    int bitisKuvveti;
    int yon;//Aşağı = -1, Yukarı = 1

    CisimModeli *cisimModeli;
    DiagramScene::Mode kipim;
    QLabel *lblBaslangicKonumu;
    QLabel *lblBitisKonumu;
    QLabel *lblBaslangicKuvveti;
    QLabel *lblBitisKuvveti;

    QLineEdit *txtBaslangicKonumu;
    QLineEdit *txtBitisKonumu;
    QLineEdit *txtBaslangicKuvveti;
    QLineEdit *txtBitisKuvveti;

    QPushButton *btnTamam;
    QPushButton *btnIptal;
    QToolButton *btnAsagi;
    QToolButton *btnYukari;

    QButtonGroup *btnYonGrubu;

};

#endif // YAYILIKUVVETEKLE_H
