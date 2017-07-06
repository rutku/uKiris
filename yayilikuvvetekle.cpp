#include "yayilikuvvetekle.h"

#include <QtWidgets>

YayiliKuvvetEkle::YayiliKuvvetEkle(QWidget *parent)
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

    lblBaslangicKonumu = new QLabel(tr("Başlangıç Konumu(cm) :"));
    lblBitisKonumu = new QLabel(tr("Bitiş Konumu(cm) :"));
    lblBaslangicKuvveti = new QLabel(tr("Başlangıç Kuvveti(kN) :"));
    lblBitisKuvveti = new QLabel(tr("Bitiş Kuvveti(kN) :"));

    txtBaslangicKonumu = new QLineEdit();
    txtBaslangicKonumu->setValidator(new QIntValidator(-10000,10000,this));
    txtBitisKonumu = new QLineEdit();
    txtBitisKonumu->setValidator(new QIntValidator(-10000,10000,this));
    txtBaslangicKuvveti = new QLineEdit();
    txtBaslangicKuvveti->setValidator(new QIntValidator(-10000,10000,this));
    txtBitisKuvveti = new QLineEdit();
    txtBitisKuvveti->setValidator(new QIntValidator(-10000,10000,this));

    QHBoxLayout *yonButonKatmani = new QHBoxLayout;
    yonButonKatmani->addWidget(btnAsagi);
    yonButonKatmani->addWidget(btnYukari);

    QHBoxLayout *baslangicKatmani = new QHBoxLayout;
    baslangicKatmani->addWidget(lblBaslangicKonumu,2,Qt::AlignRight);
    baslangicKatmani->addWidget(txtBaslangicKonumu);

    QHBoxLayout *bitisKatmani = new QHBoxLayout;
    bitisKatmani->addWidget(lblBitisKonumu,2,Qt::AlignRight);
    bitisKatmani->addWidget(txtBitisKonumu);

    QHBoxLayout *baslangicKuvvetKatmani = new QHBoxLayout;
    baslangicKuvvetKatmani->addWidget(lblBaslangicKuvveti,2,Qt::AlignRight);
    baslangicKuvvetKatmani->addWidget(txtBaslangicKuvveti);

    QHBoxLayout *bitisKuvvetKatmani = new QHBoxLayout;
    bitisKuvvetKatmani->addWidget(lblBitisKuvveti,2,Qt::AlignRight);
    bitisKuvvetKatmani->addWidget(txtBitisKuvveti);

    QHBoxLayout *durumKatmani = new QHBoxLayout;
    durumKatmani->addWidget(btnTamam);
    durumKatmani->addWidget(btnIptal);

    QVBoxLayout *anaKatman = new QVBoxLayout;
    anaKatman->addLayout(yonButonKatmani);
    anaKatman->addLayout(baslangicKatmani);
    anaKatman->addLayout(bitisKatmani);
    anaKatman->addLayout(baslangicKuvvetKatmani);
    anaKatman->addLayout(bitisKuvvetKatmani);
    anaKatman->addLayout(durumKatmani);

    connect(btnTamam,SIGNAL(clicked(bool)),this,SLOT(tamamButonunaTiklandi()));
    connect(btnIptal,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(btnYonGrubu,SIGNAL(buttonClicked(int)),this,SLOT(yonGrubunaTiklandi(int)));

    setLayout(anaKatman);
    setWindowTitle(tr("Yayılı Kuvvet"));
    setFixedHeight(300);
    setFixedWidth(270);
}

YayiliKuvvetEkle::~YayiliKuvvetEkle()
{

}

void YayiliKuvvetEkle::tamamButonunaTiklandi()
{
    bool ok;

    baslangicKonumu = txtBaslangicKonumu->text().toInt(&ok);
    bitisKonumu = txtBitisKonumu->text().toInt(&ok);
    baslangicKuvveti = txtBaslangicKuvveti->text().toInt(&ok) * yon;
    bitisKuvveti = txtBitisKuvveti->text().toInt(&ok) * yon;

    switch (kipim) {
    case DiagramScene::CisimGir:
        cisimModeli = new CisimModeli(DiagramItem::YayiliKuvvet,0,0,baslangicKonumu,
                                      bitisKonumu,baslangicKuvveti,bitisKuvveti,0);
        emit cisimEkle(cisimModeli);
        break;
    case DiagramScene::CisimDuzenle:
        cisimModeli->baslangciKonumuAta(baslangicKonumu);
        cisimModeli->bitisKonumuAta(bitisKonumu);
        cisimModeli->baslangicKuvvetiAta(baslangicKuvveti);
        cisimModeli->bitisKuvvetiAta(bitisKuvveti);
        emit cisimEkle(cisimModeli);
        break;
    default:
        break;
    }
    QDialog::reject();
}

void YayiliKuvvetEkle::yonGrubunaTiklandi(int id)
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
