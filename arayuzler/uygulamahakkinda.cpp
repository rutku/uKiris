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


#include "uygulamahakkinda.h"

#include <QtWidgets>

UygulamaHakkinda::UygulamaHakkinda(QWidget *parent)
    : QDialog(parent)
{
    btnKapat = new QPushButton(tr("Kapat"));
    QString uygulamaIsmi = tr("uKiriş");
    QString uygulamaSurumu = "1.0.1";
    QString hakkindaYazisi = tr("Bu uygulama basit kirişin kesme ve moment"
                                "\ndiyagramını çizer. Uygulama açık kaynak"
                                "\nkodlu ve kod türkçe olarak yazılmıştır."
                                "\nTürkçe yazılmasındaki amacım mümkün"
                                "\nolduğunca tecrübesi az,insanlara yardımcı "
                                "\nolabilmektir. İşleyiş hakkında daha iyin fikir"
                                "\nsahibi olmalarını sağlamaktır. Uygulama"
                                "\ngüncellemeleri ve yeni uygulamalar için"
                                "\ntakipte kalınız."
                                "\nBu uygulama BSD lisansı ile lisanslanmıştır."
                                "\n\n                  2017 - "
                                "\n                                            Ramazan Utku");

    lblUygulamaIsmi = new QLabel(uygulamaIsmi,this);
    lblUygulamaIsmi->setStyleSheet("font-weight: bold");
    lblUygulamaIsmi->setFixedWidth(40);
    lblUygulamaIsmi->setFixedHeight(20);

    lblUygulamaSurumu = new QLabel(uygulamaSurumu,this);
    lblUygulamaSurumu->setFixedWidth(35);
    lblUygulamaSurumu->setFixedHeight(20);

    lblHakkinda = new QLabel(hakkindaYazisi,this);
    lblHakkinda->setFixedHeight(200);
    QFont fontum;
    fontum.setPixelSize(12);
    lblHakkinda->setFont(fontum);

    btnKapat = new QPushButton(tr("Kapat"),this);
    btnKapat->setFixedWidth(70);
    btnGitHub = new QToolButton(this);
    btnGitHub->setIcon(QIcon(":/simgeler/github.png"));
    btnGitHub->setIconSize(QSize(50,50));

    btnTwitter = new QToolButton(this);
    btnTwitter->setIcon(QIcon(":/simgeler/twitter.png"));
    btnTwitter->setIconSize(QSize(50,50));

    btnLinkEdin = new QToolButton(this);
    btnLinkEdin->setIcon(QIcon(":/simgeler/linkedin.png"));
    btnLinkEdin->setIconSize(QSize(50,50));

    btnWebSitesi = new QToolButton(this);
    btnWebSitesi->setIcon(QIcon(":/simgeler/website.png"));
    btnWebSitesi->setIconSize(QSize(50,50));

    btnEPosta = new QToolButton(this);
    btnEPosta->setIcon(QIcon(":/simgeler/email.png"));
    btnEPosta->setIconSize(QSize(50,50));

    QVBoxLayout *butonKatmani = new QVBoxLayout();
    butonKatmani->addWidget(btnGitHub);
    butonKatmani->addWidget(btnTwitter);
    butonKatmani->addWidget(btnLinkEdin);
    butonKatmani->addWidget(btnWebSitesi);
    butonKatmani->addWidget(btnEPosta);

    QHBoxLayout *uygulamaBasligi = new QHBoxLayout();
    uygulamaBasligi->addItem(new QSpacerItem(30,10,QSizePolicy::Expanding,QSizePolicy::Expanding));
    uygulamaBasligi->addWidget(lblUygulamaIsmi);
    uygulamaBasligi->addWidget(lblUygulamaSurumu);
    uygulamaBasligi->addItem(new QSpacerItem(40,10,QSizePolicy::Expanding,QSizePolicy::Expanding));

    QHBoxLayout *butonKapatKatmani = new QHBoxLayout();
    butonKapatKatmani->addItem(new QSpacerItem(40,10,QSizePolicy::Expanding,QSizePolicy::Expanding));
    butonKapatKatmani->addWidget(btnKapat);

    QVBoxLayout *yaziKatmani = new QVBoxLayout();
    yaziKatmani->addLayout(uygulamaBasligi);
    yaziKatmani->addWidget(lblHakkinda);    
    yaziKatmani->addLayout(butonKapatKatmani);

    QHBoxLayout *anaKatman = new QHBoxLayout(this);
    anaKatman->addLayout(butonKatmani);
    anaKatman->addLayout(yaziKatmani);

    connect(btnGitHub, SIGNAL(clicked(bool)),this,SLOT(btnGitHubTiklandi()));
    connect(btnTwitter, SIGNAL(clicked(bool)),this,SLOT(btnTwitterTiklandi()));
    connect(btnLinkEdin, SIGNAL(clicked(bool)),this,SLOT(btnLinkEdinTiklandi()));
    connect(btnWebSitesi, SIGNAL(clicked(bool)),this,SLOT(btnWebSitesiTiklandi()));
    connect(btnEPosta, SIGNAL(clicked(bool)),this,SLOT(btnEPostaTiklandi()));

    connect(btnKapat, SIGNAL(clicked(bool)),this,SLOT(close()));

    setLayout(anaKatman);
    setWindowTitle(tr("Hakkında"));
    setFixedHeight(350);
    setFixedWidth(340);
}
UygulamaHakkinda::~UygulamaHakkinda()
{

}

void UygulamaHakkinda::btnGitHubTiklandi()
{

}

void UygulamaHakkinda::btnWebSitesiTiklandi()
{
    QString adres = "http://rmznutku.blogspot.com.tr/";
    QDesktopServices::openUrl(QUrl(adres));
}

void UygulamaHakkinda::btnEPostaTiklandi()
{
    QString adres = "mailto:ramazanutku@gmail.com";
    QDesktopServices::openUrl(QUrl(adres));

}

void UygulamaHakkinda::btnLinkEdinTiklandi()
{
    QString adres = "https://www.linkedin.com/in/ramazan-utku-78a767a8/";
    QDesktopServices::openUrl(QUrl(adres));
}

void UygulamaHakkinda::btnTwitterTiklandi()
{
    QString adres = "https://twitter.com/rmznutku";
    QDesktopServices::openUrl(QUrl(adres));

}
