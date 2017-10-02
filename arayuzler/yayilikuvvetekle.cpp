/****************************************************************************
**
** Copyright (C) 2017 Ramazan Utku
** Contact: ramazanutku@gmail.com
**
** This file is part of the examples of the Qt Toolkit.
**
** $UKIRIS_BEGIN_LICENSE:BSD$
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** TURKISH
** Her hakkı saklıdır.
** Değişiklik yapılarak veya yapılmaksızın, yeniden dağıtmak veya kaynak ve ikili biçimlerde
** kullanmak, aşağıdaki koşullar yerine getirildiği takdirde serbesttir:
**
**  * Kaynak kodun yeniden dağıtımı; yukarıdaki telif hakkı uyarısını, şartlar listesini ve
**    aşağıdaki ret yazısını muhafaza etmelidir.
**  * İkili biçimde yeniden dağıtımında; yukarıdaki telif hakkı uyarısı, şartlar listesi ve
**    aşağıdaki ret yazısı dağıtımla birlikte gelen belgelendirmede ve/veya diğer materyallerde
**    tekrarlanmalıdır.
**
** İŞBU YAZILIM TELİF HAKKI SAHİPLERİ VE KATKIDA BULUNANLAR TARAFINDAN OLDUĞU GİBİ” SAĞLANMIŞTIR
** VE TİCARETE ELVERİŞLİLİK VE ÖZEL BİR AMACA UYGUNLUK İÇİN KAPALI BİR TAAHHÜT DE DAHİL OLMAK ÜZERE
** VE BUNUNLA KISITLI OLMAKSIZIN HER TÜRLÜ AÇIK YA DA KAPALI TAAHHÜT REDDEDİLMİŞTİR.
** HİÇBİR KOŞULDA TELİF HAKKI SAHİPLERİ VE KATKIDA BULUNANLAR; HER NE SEBEPLE OLUŞMUŞSA VE SÖZLEŞMEDE,
** KUSURSUZ SORUMLULUKTA, VEYA TAZMİNAT YÜKÜMLÜLÜĞÜNDE OLMAK ÜZERE HANGİ YÜKÜMLÜLÜK KURAMINDA
** YER ALIRSA ALSIN,İŞBU YAZILIMIN KULLANIMIYLA ORTAYA ÇIKAN DOĞRUDAN, DOLAYLI, TESADÜFİ, ÖZEL,
** CEZAİ VEYA BİR SEBEP SONUCUNDA OLUŞAN (YEDEK PARÇA VEYA HİZMETLERİN TEMİNİ; KULLANIM,
** VERİ VEYA RANDIMAN KAYBI; YA DA İŞ KESİNTİSİ DE DAHİL OLMAK ÜZERE VE BUNUNLA KISITLI KALMAKSIZIN)
** HERHANGİ BİR ZARAR İÇİN, BU GİBİ HASARLARIN OLASILIĞI HAKKINDA UYARILMIŞ OLSALAR BİLE, SİZE KARŞI
** SORUMLU DEĞİLLERDİR.
**
** $UKIRIS_END_LICENSE$
**
****************************************************************************/


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
        cisimModeli = new CisimModeli(CisimModeli::YayiliKuvvet,0,0,baslangicKonumu,
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
