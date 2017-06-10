#include "mesnetekle.h"
#include <QtWidgets>

MesnetEkle::MesnetEkle(QWidget *parent)
    : QDialog(parent)
{
    btnEkle = new QPushButton(tr("Ekle"));
    btnIptal = new QPushButton(tr("İptal"));

    lblNokta = new QLabel(tr("Konum(cm)"));
    txtNokta = new QLineEdit();
    txtNokta->setValidator(new QIntValidator(-10000,10000,this));

    QGridLayout *katman = new QGridLayout;
    katman->setColumnStretch(1,2);

    katman->addWidget(lblNokta);
    katman->addWidget(txtNokta);

    QHBoxLayout *butonKatmani = new QHBoxLayout;
    butonKatmani->addWidget(btnEkle);
    butonKatmani->addWidget(btnIptal);

    katman->addLayout(butonKatmani,2,1,Qt::AlignRight);
    QVBoxLayout *anaKatman = new QVBoxLayout;
    anaKatman->addLayout(katman);

    connect(btnEkle, SIGNAL(clicked(bool)),this,SLOT(ekleButonunaTiklandi()));
    connect(btnIptal, SIGNAL(clicked(bool)),this,SLOT(close()));

    setLayout(anaKatman);
    setWindowTitle("Mesnet Ekle");

}

void MesnetEkle::ekleButonunaTiklandi()
{
    bool ok;
    int konum = txtNokta->text().toInt(&ok);
    cisimModeli = new CisimModeli(_tip,konum,0,0,0,0,0);
    emit cisimEkle(cisimModeli);
    QDialog::reject();
}
