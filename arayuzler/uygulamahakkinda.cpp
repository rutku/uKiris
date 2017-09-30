#include "uygulamahakkinda.h"

#include <QtWidgets>

UygulamaHakkinda::UygulamaHakkinda(QWidget *parent)
    : QDialog(parent)
{
    btnKapat = new QPushButton(tr("Kapat"));
    QString uygulamaIsmi = tr("uKiriş");
    QString uygulamaSurumu = "1.0";
    QString hakkindaYazisi = tr("Bu uygulama basit kirişin kesme ve moment"
                                "\ndiyagramını çizer. Uygulama açık kaynak"
                                "\nkodlu ve kod türkçe olarak yazılmıştır."
                                "\nTürkçe yazılmasındaki amacım mümkün"
                                "\nolduğunca tecrübesi az,insanlara yardımcı "
                                "\nolabilmektir. İşleyiş hakkında daha iyin fikir"
                                "\nsahibi olmalarını sağlamaktır."
                                "\nBu uygulama BSD lisansı ile lisanlanmıştır.");

    lblUygulamaIsmi = new QLabel(uygulamaIsmi,this);
    lblUygulamaIsmi->setStyleSheet("font-weight: bold");
    lblUygulamaIsmi->setFixedWidth(40);
    lblUygulamaIsmi->setFixedHeight(20);

    lblUygulamaSurumu = new QLabel(uygulamaSurumu,this);
    lblUygulamaSurumu->setFixedWidth(20);
    lblUygulamaSurumu->setFixedHeight(20);

    lblHakkinda = new QLabel(hakkindaYazisi,this);
    lblHakkinda->setFixedHeight(200);

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
    setFixedWidth(400);
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
