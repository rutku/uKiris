#include "ankastremesnetekle.h"
#include <QtWidgets>
AnkastreMesnetEkle::AnkastreMesnetEkle(QWidget *parent)
    : QDialog(parent),yon(0)
{
    btnTamam = new QPushButton(tr("Tamam"));
    btnIptal = new QPushButton(tr("İptal"));

    btnSol = new QToolButton;
    btnSol->setIcon(QIcon(":/simgeler/ankastreMesnetSol.png"));
    btnSol->setIconSize(QSize(75,75));

    btnSag = new QToolButton;
    btnSag->setIcon(QIcon(":/simgeler/ankastreMesnetSag.png"));
    btnSag->setIconSize(QSize(75,75));

    btnYonGrubu = new QButtonGroup(this);
    btnYonGrubu->setExclusive(true);
    btnYonGrubu->addButton(btnSol,Sol);
    btnYonGrubu->addButton(btnSag,Sag);
    btnSag->setCheckable(true);
    btnSol->setCheckable(true);
    btnSol->setChecked(true);

    QHBoxLayout *yonButonKatmani = new QHBoxLayout;
    yonButonKatmani->addWidget(btnSol);
    yonButonKatmani->addWidget(btnSag);

    QHBoxLayout *durumKatmani = new QHBoxLayout;
    durumKatmani->addWidget(btnTamam);
    durumKatmani->addWidget(btnIptal);

    QVBoxLayout *anaKatman = new QVBoxLayout;
    anaKatman->addLayout(yonButonKatmani);
    anaKatman->addLayout(durumKatmani);

    connect(btnTamam,SIGNAL(clicked(bool)),this,SLOT(tamamButonunaTiklandi()));
    connect(btnIptal,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(btnYonGrubu,SIGNAL(buttonClicked(int)),this,SLOT(yonGrubunaTiklandi(int)));

    setLayout(anaKatman);
    setWindowTitle(tr("Ankastre Mesnet"));
    setFixedHeight(150);
    setFixedWidth(240);
}

AnkastreMesnetEkle::~AnkastreMesnetEkle()
{

}

void AnkastreMesnetEkle::tamamButonunaTiklandi()
{
    if (yon == 0) {
        noktaKonumu = 0;
    }else {
        noktaKonumu = kirisUzunlugu;
    }
    switch (kipim) {
    case DiagramScene::CisimGir:
        cisimModeli = new CisimModeli(CisimModeli::AnkastreMesnet,noktaKonumu,
                                      0,0,0,0,0,0);
        emit cisimEkle(cisimModeli);
        break;
    case DiagramScene::CisimDuzenle:
        cisimModeli->noktaKonumuAta(noktaKonumu);
        emit cisimEkle(cisimModeli);
        break;
    default:
        break;
    }
    QDialog::reject();

}

void AnkastreMesnetEkle::yonGrubunaTiklandi(int id)
{
    switch (id) {
    case Sol:
        yon = 0;
        break;
    case Sag:
        yon = 1;
        break;
    default:
        break;
    }
}
