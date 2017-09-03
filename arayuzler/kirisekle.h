#ifndef KIRISEKEL_H
#define KIRISEKEL_H

#include "cisimmodeli.h"
#include "diagramScene.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class KirisEkle : public QDialog
{
    Q_OBJECT

public:
    KirisEkle(QWidget *parent = 0);
    ~KirisEkle();
    int uzunlukAl() { return uzunluk; }
    CisimModeli *cisimModeliAl() { return cisimModeli; }
    void cisimModeliAta(CisimModeli *_cisimModeli);
    void kipAta(DiagramScene::Mode _kip) { kipim = _kip; }

private slots:
    void ekleButonunaTiklandi();

signals:
    void cisimEkle(CisimModeli *cisimModeli);

private:
    DiagramScene::Mode kipim;
    QLabel *lblUzunluk;
    QLineEdit *txtUzunluk;
    QPushButton *btnEkle;
    QPushButton *btnIptal;
    CisimModeli *cisimModeli;
    int uzunluk;
};

#endif // KIRISEKEL_H
