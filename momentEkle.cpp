#include "momentEkle.h"

#include <QtWidgets>

MomentEkle::MomentEkle(QWidget *parent)
    : QDialog(parent),yon(1)
{
    btnTamam = new QPushButton(tr("Tamam"));
    btnIptal = new QPushButton(tr("İptal"));

    btnSag = new QToolButton;
    btnSag->setIcon(QIcon(":/simgeler/asagi.png"));
    btnSag->setIconSize(QSize(50,50));

    btnSol = new QToolButton;
    btnSol->setIcon(QIcon(":/simgeler/yukari.png"));
    btnSol->setIconSize(QSize(50,50));

    btnYonGrubu = new QButtonGroup(this);
    btnYonGrubu->setExclusive(true);
    btnYonGrubu->addButton(btnSag,Sag);
    btnYonGrubu->addButton(btnSol,Sol);
    btnSag->setCheckable(true);
    btnSag->setChecked(true);
    btnSol->setCheckable(true);

    lblNoktaKonumu = new QLabel(tr("Nokta Konumu(cm) :"));
    lblMoment = new QLabel(tr("Moment(kN.m) :"));

    txtNoktaKonumu = new QLineEdit();
    txtNoktaKonumu->setValidator(new QIntValidator(-10000,10000,this));

    txtMoment = new QLineEdit();
    txtMoment->setValidator(new QIntValidator(-10000,10000,this));

    QHBoxLayout *yonButonKatmani = new QHBoxLayout;
    yonButonKatmani->addWidget(btnSag);
    yonButonKatmani->addWidget(btnSol);

    QHBoxLayout *noktaKonumuKatmani = new QHBoxLayout;
    noktaKonumuKatmani->addWidget(lblNoktaKonumu,2,Qt::AlignRight);
    noktaKonumuKatmani->addWidget(txtNoktaKonumu);

    QHBoxLayout *momentKatmani = new QHBoxLayout;
    momentKatmani->addWidget(lblMoment,2,Qt::AlignRight);
    momentKatmani->addWidget(txtMoment);

    QHBoxLayout *durumKatmani = new QHBoxLayout;
    durumKatmani->addWidget(btnTamam);
    durumKatmani->addWidget(btnIptal);

    QVBoxLayout *anaKatman = new QVBoxLayout;
    anaKatman->addLayout(yonButonKatmani);
    anaKatman->addLayout(noktaKonumuKatmani);
    anaKatman->addLayout(momentKatmani);
    anaKatman->addLayout(durumKatmani);

    connect(btnTamam,SIGNAL(clicked(bool)),this,SLOT(tamamButonunaTiklandi()));
    connect(btnIptal,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(btnYonGrubu,SIGNAL(buttonClicked(int)),this,SLOT(yonGrubunaTiklandi(int)));

    setLayout(anaKatman);
    setWindowTitle(tr("Moment"));
    setFixedHeight(150);
    setFixedWidth(270);

}

MomentEkle::~MomentEkle()
{

}

void MomentEkle::tamamButonunaTiklandi()
{
    bool ok;

    noktaKonumu = txtNoktaKonumu->text().toInt(&ok);
    moment = txtMoment->text().toInt(&ok) * yon;

    switch (kipim) {
    case DiagramScene::CisimGir:
        cisimModeli = new CisimModeli(DiagramItem::Moment,noktaKonumu,
                                      0,0,0,0,0,moment);
        emit cisimEkle(cisimModeli);
        break;
    case DiagramScene::CisimDuzenle:
        cisimModeli->noktaKonumuAta(noktaKonumu);
        cisimModeli->momentAta(moment);

        emit cisimEkle(cisimModeli);
        break;
    default:
        break;
    }
    QDialog::reject();
}

void MomentEkle::yonGrubunaTiklandi(int id)
{
    switch (id) {
    case Sag:
        yon = -1;
        break;
    case Sol:
        yon = 1;
        break;
    default:
        break;
    }

}
