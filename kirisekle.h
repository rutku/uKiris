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
    KirisEkle(QWidget *parent = 0);
    int uzunlukAl() { return uzunluk; }
    CisimModeli *cisimModeliAl() { return cisimModeli; }
    void tipAta(int tip) { _tip = tip; }

private slots:
    void ekleButonunaTiklandi();
signals:
    void cisimEkle(CisimModeli *cisimModeli);

private:
    QLabel *lblUzunluk;
    QLineEdit *txtUzunluk;
    QPushButton *btnEkle;
    QPushButton *btnIptal;
    CisimModeli *cisimModeli;
    int _tip;
    int uzunluk;
};

#endif // KIRISEKEL_H
