#ifndef CISIMEKLE_H
#define CISIMEKLE_H

#include <QDialog>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class CisimEkle : public QDialog
{
    Q_OBJECT

public:
    CisimEkle(int id, QWidget *parent = 0);

private:
    QLabel *lbl_uzunluk;
    QLabel *lbl_sagYon;
    QLabel *lbl_solYon;

    QLineEdit *txt_uzunlukGir;
    QLineEdit *txt_tekilYukGir;

    QPushButton *ekleButonu;
    QPushButton *iptalButonu;
    QWidget *kirisEkle();
    QWidget *sabitMesnetEkle();


};

#endif // CISIMEKLE_H
