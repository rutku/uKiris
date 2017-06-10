#include "cisimekle.h"
#include "diagramitem.h"

#include <QtWidgets>

CisimEkle::CisimEkle(int id, QWidget *parent)
    : QDialog(parent)
{
    ekleButonu = new QPushButton(tr("Ekle"));
    iptalButonu = new QPushButton(tr("İptal"));

    QGridLayout *gKatman = new QGridLayout;
    gKatman->setColumnStretch(1,2);



    switch (DiagramItem::DiagramType(id)) {
    case DiagramItem::Kiris:
        qDebug() << "Kiriş";
        gKatman->addWidget(kirisEkle());
        setWindowTitle(tr("Sabit Mesnet Ekle"));
        break;
    case DiagramItem::SabitMesnet:
        qDebug() << "Sabit Mesnet";
//        gKatman->addWidget(sabitMesnetEkle());
        setWindowTitle(tr("Sabit Mesnet Ekle"));
        break;
    case DiagramItem::HareketliMesnet:
        qDebug() << "Hareketli Mesnet";
        break;
    default:
        break;
    }

    QHBoxLayout *butonKatmani = new QHBoxLayout;
    butonKatmani->addWidget(ekleButonu);
    butonKatmani->addWidget(iptalButonu);

    gKatman->addLayout(butonKatmani,2,1,Qt::AlignRight);
    QVBoxLayout *anaKatman = new QVBoxLayout;
    anaKatman->addLayout(gKatman);
    setLayout(anaKatman);
}

QWidget *CisimEkle::kirisEkle()
{
    QGridLayout *katman = new QGridLayout;
    katman->setColumnStretch(1,2);

    QLabel *uzunluk = new QLabel(tr("Uzunluk(m) : "));
    QLineEdit *uzunlukGir = new QLineEdit;

    katman->addWidget(uzunluk,0,0,Qt::AlignCenter);
    katman->addWidget(uzunlukGir,0,1,Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(katman);
    return widget;
}

QWidget *CisimEkle::sabitMesnetEkle()
{
    QGridLayout *katman = new QGridLayout;
    katman->setColumnStretch(1,2);

    lbl_uzunluk = new QLabel(tr("Konum(m) : "));
    txt_uzunlukGir = new QLineEdit;

    katman->addWidget(lbl_uzunluk,0,0,Qt::AlignCenter);
    katman->addWidget(txt_uzunlukGir,0,1,Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(katman);
    return widget;
}

