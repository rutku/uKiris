#include "tekilkuvvetekle.h"

#include <QtWidgets>

TekilKuvvetEkle::TekilKuvvetEkle(QWidget *parent)
    : QDialog(parent),yon(-1)
{
    btnTamam = new QPushButton(tr("Tamam"));
    btnIptal = new QPushButton(tr("İptal"));

    btnAsagi = new QToolButton;
    btnAsagi->setIcon(QIcon(":/simgeler/asagi.png"));
    btnAsagi->setIconSize(QSize(50,50));

    btnYukari = new QToolButton;
    btnYukari->setIcon(QIcon(":/simgeler/yukari.png"));
    btnYukari->setIconSize(QSize(50,50));

    btnYonGrubu = new QButtonGroup(this);
    btnYonGrubu->setExclusive(true);
    btnYonGrubu->addButton(btnAsagi,Asagi);
    btnYonGrubu->addButton(btnYukari,Yukari);
    btnAsagi->setCheckable(true);
    btnAsagi->setChecked(true);
    btnYukari->setCheckable(true);


    lblNoktaKonumu = new QLabel(tr("Nokta Konumu(cm) :"));
    lblTekilKuvvet = new QLabel(tr("Tekil Kuvvet(kN) :"));

    txtNoktaKonumu = new QLineEdit();
    txtNoktaKonumu->setValidator(new QIntValidator(-10000,10000,this));
    txtTekilKuvvet = new QLineEdit();
    txtTekilKuvvet->setValidator(new QIntValidator(-10000,10000,this));

    QHBoxLayout *yonButonKatmani = new QHBoxLayout;
    yonButonKatmani->addWidget(btnAsagi);
    yonButonKatmani->addWidget(btnYukari);

    QHBoxLayout *noktaKonumKatmani = new QHBoxLayout;
    noktaKonumKatmani->addWidget(lblNoktaKonumu,2,Qt::AlignRight);
    noktaKonumKatmani->addWidget(txtNoktaKonumu);

    QHBoxLayout *tekilKuvvetKatmani = new QHBoxLayout;
    tekilKuvvetKatmani->addWidget(lblTekilKuvvet,2,Qt::AlignRight);
    tekilKuvvetKatmani->addWidget(txtTekilKuvvet);

    QHBoxLayout *butonKatmani = new QHBoxLayout;
    butonKatmani->addWidget(btnTamam);
    butonKatmani->addWidget(btnIptal);

    QVBoxLayout *anaKatman = new QVBoxLayout;
    anaKatman->addLayout(yonButonKatmani);
    anaKatman->addLayout(noktaKonumKatmani);
    anaKatman->addLayout(tekilKuvvetKatmani);
    anaKatman->addLayout(butonKatmani);

    connect(btnTamam,SIGNAL(clicked(bool)),this,SLOT(tamamButonunaTiklandi()));
    connect(btnIptal,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(btnYonGrubu,SIGNAL(buttonClicked(int)),this,SLOT(yonGrubunaTiklandi(int)));

    setLayout(anaKatman);
    setWindowTitle(tr("Tekil Kuvvet"));
    setFixedHeight(200);
    setFixedWidth(270);

}

TekilKuvvetEkle::~TekilKuvvetEkle()
{

}

void TekilKuvvetEkle::tamamButonunaTiklandi()
{
    bool ok;

    noktaKonumu = txtNoktaKonumu->text().toInt(&ok);
    tekilKuvvet = txtTekilKuvvet->text().toInt(&ok) * yon;

    switch (kipim) {
    case DiagramScene::CisimGir:
        cisimModeli = new CisimModeli(DiagramItem::TekilKuvvet,noktaKonumu,
                                      tekilKuvvet,0,0,0,0,0);
        emit cisimEkle(cisimModeli);
        break;
    case DiagramScene::CisimDuzenle:
        cisimModeli->noktaKonumuAta(noktaKonumu);
        cisimModeli->noktaKuvvetiAta(tekilKuvvet);
        emit cisimEkle(cisimModeli);
        break;
    default:
        break;
    }

    QDialog::reject();

}

void TekilKuvvetEkle::yonGrubunaTiklandi(int id)
{
    switch (id) {
    case Asagi:
        yon = -1;
        break;
    case Yukari:
        yon = 1;
        break;
    default:
        break;
    }
}
