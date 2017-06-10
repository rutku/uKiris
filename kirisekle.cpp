#include "kirisekle.h"
#include "cisimmodeli.h"

#include <QtWidgets>

KirisEkle::KirisEkle(QWidget *parent)
    : QDialog(parent)
{
    btnEkle = new QPushButton(tr("Ekle"));
    btnIptal = new QPushButton(tr("İptal"));

    lblUzunluk = new QLabel(tr("Uzunluk (cm) :"));
    txtUzunluk = new QLineEdit();
    txtUzunluk->setValidator(new QIntValidator(-10000,10000,this));

    QGridLayout *katman = new QGridLayout;
    katman->setColumnStretch(1,2);

    katman->addWidget(lblUzunluk);
    katman->addWidget(txtUzunluk);

    QHBoxLayout *butonKatmani = new QHBoxLayout;
    butonKatmani->addWidget(btnEkle);
    butonKatmani->addWidget(btnIptal);

    katman->addLayout(butonKatmani,2,1,Qt::AlignRight);
    QVBoxLayout *anaKatman = new QVBoxLayout;
    anaKatman->addLayout(katman);

    connect(btnEkle,SIGNAL(clicked(bool)),this,SLOT(ekleButonunaTiklandi()));
    connect(btnIptal,SIGNAL(clicked(bool)),this,SLOT(close()));
    setLayout(anaKatman);
    setWindowTitle(tr("Kiriş Ekle"));
}


void KirisEkle::ekleButonunaTiklandi()
{
    bool ok;
    uzunluk = txtUzunluk->text().toInt(&ok);
    cisimModeli = new CisimModeli(_tip,0,0,0,uzunluk,0,0);
    emit cisiModeliAta(cisimModeli);
    QDialog::reject();
}
