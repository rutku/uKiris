#ifndef KIRISEKEL_H
#define KIRISEKEL_H

#include "cisimmodeli.h"
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
    KirisEkle(int tip, QWidget *parent = 0);
    int uzunlukAl() { return uzunluk; }
    CisimModeli *cisimModeliAl() { return cisimModeli; }

private slots:
    void ekleButonunaTiklandi();

private:
    QLabel *lblUzunluk;
    QLineEdit *txtUzunluk;
    QPushButton *btnEkle;
    QPushButton *btnIptal;
    int _tip;
    int uzunluk;
    CisimModeli *cisimModeli;
};

#endif // KIRISEKEL_H
