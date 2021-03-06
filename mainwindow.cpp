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

#include "cisimmodeli.h"
#include "diagramScene.h"
#include "mainwindow.h"
#include "arayuzler/kirisekle.h"
#include "arayuzler/mesnetekle.h"
#include "arayuzler/tekilkuvvetekle.h"
#include "arayuzler/yayilikuvvetekle.h"
#include "arayuzler/momentEkle.h"
#include "arayuzler/ankastremesnetekle.h"
#include "arayuzler/uygulamahakkinda.h"
#include "cisimmodeli.h"
#include "tablowidget.h"
#include "dosyaislemleri.h"

#include <QtWidgets>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), kipim(DiagramScene::CisimGir)
{

    eylemleriOlustur();
    aracKutusuOlustur();
    diagramlariOlustur();
    menulerOlustur();


    kirisEkle = new KirisEkle(this);
    mesnetEkle = new MesnetEkle(this);
    tekilKuvvetEkle  = new TekilKuvvetEkle(this);
    yayiliKuvvetEkle = new YayiliKuvvetEkle(this);
    momentEkle = new MomentEkle(this);
    ankastreMesnetEkle = new AnkastreMesnetEkle(this);
    uygulamaHakkinda = new UygulamaHakkinda(this);
    dosyaIslemleri = new DosyaIslemleri(this);

    connect(this,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimIslemleri(CisimModeli*)));
    connect(kirisEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimIslemleri(CisimModeli*)));
    connect(mesnetEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimIslemleri(CisimModeli*)));
    connect(ankastreMesnetEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimIslemleri(CisimModeli*)));
    connect(tekilKuvvetEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimIslemleri(CisimModeli*)));
    connect(yayiliKuvvetEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimIslemleri(CisimModeli*)));
    connect(momentEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimIslemleri(CisimModeli*)));
    connect(scene,SIGNAL(tabloyaCisimEkle(CisimModeli*)),
            cisimTablosu,SLOT(tabloyaCisimEkle(CisimModeli*)));
    connect(scene,SIGNAL(tabloyuGuncelle(CisimModeli*)),
            cisimTablosu,SLOT(tabloyuGuncelle(CisimModeli*)));
    connect(cisimTablosu,SIGNAL(cisimDuzenle(CisimModeli*)),
            this,SLOT(cisimDuzenle(CisimModeli*)));
    connect(cisimTablosu,SIGNAL(Sil(CisimModeli*)),
            scene,SLOT(cisimIslemleri(CisimModeli*)));
    connect(cisimTablosu,SIGNAL(kesmeDiagramiCiz(QList<CisimModeli*>)),
            kesmeDiagramSahnesi,SLOT(kesmeDiagramiCiz(QList<CisimModeli*>)));
    connect(cisimTablosu,SIGNAL(momentDiagramiCiz(QList<CisimModeli*>)),
            momentDiagramSahnesi,SLOT(momentDiagramiCiz(QList<CisimModeli*>)));
    connect(this,SIGNAL(diagramCiz()),
            cisimTablosu,SLOT(diagramCiz()));

    aracCubuguOlustur();

    QHBoxLayout *katman = new QHBoxLayout;
    katman->addWidget(aracKutusu);

    QVBoxLayout *yatayKatman = new QVBoxLayout;

    yatayKatman->addWidget(view);
    yatayKatman->addWidget(diagramlarinKutusu);

    katman->addLayout(yatayKatman);
    QWidget *widget = new QWidget;
    widget->setLayout(katman);

    setCentralWidget(widget);

    setWindowTitle(tr("uKiriş"));
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete view;
    delete cisimTablosu;
    delete kirisEkle;
    delete mesnetEkle;
    delete tekilKuvvetEkle;
    delete yayiliKuvvetEkle;
    delete momentEkle;
    delete ankastreMesnetEkle;
    delete kesmeDiagramGorunumu;
    delete kesmeDiagramSahnesi;
    delete momenDiagramGorunumu;
    delete momentDiagramSahnesi;
    delete dosyaIslemleri;
    delete uygulamaHakkinda;

}

void MainWindow::butonGrubunaTiklandi(int id)
{
    scene->kipAta(kipim);
    switch (CisimModeli::CisimTipi(id)) {
    case CisimModeli::Kiris:
        kirisEkle->kipAta(kipim);
        kirisEkle->exec();
        kirisUzunlugu = kirisEkle->uzunlukAl();
        break;
    case CisimModeli::SabitMesnet:
        mesnetEkle->kipAta(kipim);
        mesnetEkle->tipAta(id);
        mesnetEkle->exec();
        break;
    case CisimModeli::HareketliMesnet:
        mesnetEkle->kipAta(kipim);
        mesnetEkle->tipAta(id);
        mesnetEkle->exec();
        break;
    case CisimModeli::AnkastreMesnet:
        ankastreMesnetEkle->kipAta(kipim);
        ankastreMesnetEkle->kirisUzunluguAta(kirisUzunlugu);
        ankastreMesnetEkle->exec();
        break;
    case CisimModeli::TekilKuvvet:
        tekilKuvvetEkle->kipAta(kipim);
        tekilKuvvetEkle->exec();
        break;
    case CisimModeli::YayiliKuvvet:
        yayiliKuvvetEkle->kipAta(kipim);
        yayiliKuvvetEkle->exec();
        break;
    case CisimModeli::Moment:
        momentEkle->kipAta(kipim);
        momentEkle->exec();
        break;
    default:
        break;
    }
    butonGrubu->button(id)->setChecked(false);
    scene->update();
    view->update();

}

void MainWindow::projeGrubunaTiklandi(int id)
{
    switch (aracCubugu(id)) {
    case Calistir:
        emit diagramCiz();
        break;
    case Yeni:
        scene->kipAta(DiagramScene::CisimSil);
        yeniProje();
        break;
    case Ac:
        dosyaAc();
        break;
    case Kaydet:
        dosyaKaydet();
        break;
    case GoruntuyuKaydet:
        goruntuOlarakKaydet();
        break;
    case Sil:
        scene->kipAta(DiagramScene::CisimSil);
        cisimTablosu->cisimSil();
        break;
    default:
        break;
    }
    scene->update();
    view->update();
}


void MainWindow::cisimDuzenle(CisimModeli *_cisimModeli)
{
    scene->kipAta(DiagramScene::CisimDuzenle);
    switch (_cisimModeli->tipAl()) {
    case CisimModeli::Kiris:
        kirisEkle->kipAta(DiagramScene::CisimDuzenle);
        kirisEkle->cisimModeliAta(_cisimModeli);
        kirisEkle->exec();
        break;
    case CisimModeli::SabitMesnet:
        mesnetEkle->kipAta(DiagramScene::CisimDuzenle);
        mesnetEkle->cisimModeliAta(_cisimModeli);
        mesnetEkle->tipAta(_cisimModeli->tipAl());
        mesnetEkle->exec();
        break;
    case CisimModeli::HareketliMesnet:
        mesnetEkle->kipAta(DiagramScene::CisimDuzenle);
        mesnetEkle->cisimModeliAta(_cisimModeli);
        mesnetEkle->tipAta(_cisimModeli->tipAl());
        mesnetEkle->exec();
        break;
    case CisimModeli::AnkastreMesnet:
        ankastreMesnetEkle->kipAta(DiagramScene::CisimDuzenle);
        ankastreMesnetEkle->cisimModeliAta(_cisimModeli);
        ankastreMesnetEkle->kirisUzunluguAta(kirisUzunlugu);
        ankastreMesnetEkle->exec();
        break;
    case CisimModeli::TekilKuvvet:
        tekilKuvvetEkle->kipAta(DiagramScene::CisimDuzenle);
        tekilKuvvetEkle->cisimModeliAta(_cisimModeli);
        tekilKuvvetEkle->exec();
        break;
    case CisimModeli::YayiliKuvvet:
        yayiliKuvvetEkle->kipAta(DiagramScene::CisimDuzenle);
        yayiliKuvvetEkle->cisimModeliAta(_cisimModeli);
        yayiliKuvvetEkle->exec();
        break;
    case CisimModeli::Moment:
        momentEkle->kipAta(DiagramScene::CisimDuzenle);
        momentEkle->cisimModeliAta(_cisimModeli);
        momentEkle->exec();
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent *olay)
{
    if (cisimTablosu->cisimModelListesiAl().size() == 0) {
        return;
    }
    QMessageBox msgBox;
    msgBox.setText("Programdan Çıkış Uyarısı");
    msgBox.setInformativeText("Değişikliği kaydetmek ister misiniz?");
    btnKaydet = msgBox.addButton(QMessageBox::Save);
    btnKaydetme = msgBox.addButton(QMessageBox::Discard);
    btnVazgec = msgBox.addButton(QMessageBox::Cancel);

    btnKaydet->setText(tr("Kaydet"));
    btnKaydetme->setText(tr("Kaydetme"));
    btnVazgec->setText(tr("Vazgeç"));

    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.exec();

    if (msgBox.clickedButton() == btnKaydet) {
        dosyaKaydet();
        olay->accept();
    }else if (msgBox.clickedButton() == btnKaydetme) {
        olay->accept();
    }else {
        olay->ignore();
    }
}

void MainWindow::aracKutusuOlustur()
{
    butonGrubu = new QButtonGroup(this); //Elemanlar ve Mesnetlerin dizisini oluşturuyoruz.
    butonGrubu->setExclusive(false);

    projeGrubu = new QButtonGroup(this);
    projeGrubu->setExclusive(false);

    connect(butonGrubu,SIGNAL(buttonClicked(int)),//Sinyalleri kuruyoruz ...
            this,SLOT(butonGrubunaTiklandi(int)));
    connect(projeGrubu,SIGNAL(buttonClicked(int)),
            this,SLOT(projeGrubunaTiklandi(int)));

    QGridLayout *elemanlarKatmani = new QGridLayout;
    elemanlarKatmani->addWidget(cisimHucresiOlustur(tr("Kiriş"),CisimModeli::Kiris,":/simgeler/kiris.png"),0,0);
    elemanlarKatmani->addWidget(cisimHucresiOlustur(tr("Sabit Mesnet"),CisimModeli::SabitMesnet,":/simgeler/sabitMesnet.png"),0,1);
    elemanlarKatmani->addWidget(cisimHucresiOlustur(tr("Hareketli Mesnet"),CisimModeli::HareketliMesnet,":/simgeler/hareketliMesnet.png"),1,0);
    elemanlarKatmani->addWidget(cisimHucresiOlustur(tr("Ankastre Mesnet"),CisimModeli::AnkastreMesnet,":/simgeler/ankastreMesnetSol.png"),1,1);

    elemanlarKatmani->setRowStretch(2, 10);
    elemanlarKatmani->setColumnStretch(1,10);

    QWidget *elemanlarWidget = new QWidget;
    elemanlarWidget->setLayout(elemanlarKatmani);

    QGridLayout *kuvvetlerKatmani = new QGridLayout;
    kuvvetlerKatmani->addWidget(cisimHucresiOlustur(tr("Tekil Kuvvet"),CisimModeli::TekilKuvvet,":/simgeler/tekilKuvvet.png"),0,0);
    kuvvetlerKatmani->addWidget(cisimHucresiOlustur(tr("Yayılı Kuvvet"),CisimModeli::YayiliKuvvet,":/simgeler/yayiliKuvvet.png"),0,1);
    kuvvetlerKatmani->addWidget(cisimHucresiOlustur(tr("Moment"),CisimModeli::Moment,":/simgeler/momentSol.png"),1,0);

    kuvvetlerKatmani->setRowStretch(2,10);
    kuvvetlerKatmani->setColumnStretch(1,10);

    QWidget *kuvvetlerWidget = new QWidget;
    kuvvetlerWidget->setLayout(kuvvetlerKatmani);

    aracKutusu = new QToolBox;
    aracKutusu->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    aracKutusu->setMinimumWidth(elemanlarWidget->sizeHint().width());
    aracKutusu->addItem(elemanlarWidget,tr("Elemanlar"));
    aracKutusu->addItem(kuvvetlerWidget,tr("Kuvvetler"));

    projeAracCubugu = addToolBar(tr("Proje"));
    projeAracCubugu->setMinimumHeight(50);
    projeAracCubugu->addWidget(aracCubuguButonuOlustur(tr("Çalıştır"),Calistir,":/simgeler/calistir.png"));
    projeAracCubugu->addSeparator();
    projeAracCubugu->addWidget(aracCubuguButonuOlustur(tr("Yeni"),Yeni,":/simgeler/yeni.png"));
    projeAracCubugu->addWidget(aracCubuguButonuOlustur(tr("Kaydet"),Kaydet,":/simgeler/kaydet.png"));
    projeAracCubugu->addWidget(aracCubuguButonuOlustur(tr("Aç"),Ac,":/simgeler/ac.png"));
    projeAracCubugu->addWidget(aracCubuguButonuOlustur(tr("Çözümü Görüntü Olarak Kaydet"),GoruntuyuKaydet,":/simgeler/goruntu.png"));
    projeAracCubugu->addSeparator();
    projeAracCubugu->addWidget(aracCubuguButonuOlustur(tr("Sil"),Sil,":/simgeler/sil.png"));



}

void MainWindow::diagramlariOlustur()
{
    scene = new DiagramScene(this);
    scene->setSceneRect(QRectF(0,0,width(),0));
    view = new QGraphicsView(scene);
    kesmeDiagramSahnesi = new KMDiagramSahnesi(this);
    kesmeDiagramGorunumu = new QGraphicsView(kesmeDiagramSahnesi);

    momentDiagramSahnesi = new KMDiagramSahnesi(this);
    momenDiagramGorunumu = new QGraphicsView(momentDiagramSahnesi);

    cisimTablosu = new TabloWidget(this);
    QStringList cisimTabloBasligi;
    CisimModeli cisim;
    foreach (auto isim, cisim.degerlerinIsimleriniAl().values()) {
        isim = isim.replace(" ","\n");
        cisimTabloBasligi.append(isim);
    }


    cisimTablosu->setFixedHeight(200);
    cisimTablosu->setColumnCount(cisimTabloBasligi.size());
    cisimTablosu->setHorizontalHeaderLabels(cisimTabloBasligi);



    diagramlarinKutusu = new QToolBox;
    diagramlarinKutusu->addItem(cisimTablosu,tr("Elemanların Tablosu"));
    diagramlarinKutusu->addItem(kesmeDiagramGorunumu,tr("Kesme Diagramı"));
    diagramlarinKutusu->addItem(momenDiagramGorunumu,tr("Moment Diagramı"));

}

void MainWindow::eylemleriOlustur()
{
    //Dosya Menüsü
    projeAc = new QAction(tr("Proje &Aç"),this);
    projeAc->setShortcuts(QKeySequence::Open);
    projeAc->setStatusTip(tr("Kayıtlı olan Projeyi Aç"));
    connect(projeAc,&QAction::triggered,this,&MainWindow::dosyaAc);

    projeyiKaydet = new QAction(tr("Projeyi &Kaydet"),this);
    projeyiKaydet->setShortcuts(QKeySequence::Save);
    projeyiKaydet->setStatusTip(tr("Çalışmakta Olduğunuz Projeyi Kaydeder"));
    connect(projeyiKaydet,&QAction::triggered,this,&MainWindow::dosyaKaydet);

    yeniProjeOlustur = new QAction(tr("Yeni Proje &Oluştur"),this);
    yeniProjeOlustur->setShortcuts(QKeySequence::New);
    yeniProjeOlustur->setStatusTip(tr("Çalışmakta Olduğunuz Projeyi Kaydeder"));
    connect(yeniProjeOlustur,&QAction::triggered,this,&MainWindow::yeniProje);

    cikis = new QAction(tr("&Çıkış"),this);
    cikis->setShortcuts(QKeySequence::Quit);
    cikis->setStatusTip(tr("Uygulamadan Çıkış"));
    connect(cikis,&QAction::triggered,this,&MainWindow::close);

    //Proje Menüsü
    kirisEkleme = new QAction(tr("&Kiriş Ekle"),this);
    kirisEkleme->setStatusTip(tr("Yüklerin konulanacağı kiriş"));
    connect(kirisEkleme,&QAction::triggered,this,&MainWindow::kirisEklemeTiklandi);

    sabitMesnetEkleme = new QAction(tr("&Sabit Mesnet Ekle"),this);
    sabitMesnetEkleme->setStatusTip(tr("Düşey yükleri taşıyan eleman"));
    connect(sabitMesnetEkleme,&QAction::triggered,this,&MainWindow::sabitMesnetEklemeTiklandi);

    hareketliMesnetEkleme = new QAction(tr("&Hareketli Mesnet Ekle"),this);
    hareketliMesnetEkleme->setStatusTip(tr("Düşey yükleri taşıyan kayıcı eleman"));
    connect(hareketliMesnetEkleme,&QAction::triggered,this,&MainWindow::hareketliMesnetEklemeTiklandi);

    ankastreMesnetEkleme = new QAction(tr("&Ankastre Mesnet Ekle"),this);
    ankastreMesnetEkleme->setStatusTip(tr("Düşey yükleri taşıyan eleman"));
    connect(ankastreMesnetEkleme,&QAction::triggered,this,&MainWindow::ankastreMesnetEklemeTiklandi);

    tekilKuvvetEkleme = new QAction(tr("&Tekil Kuvvet Ekle"),this);
    tekilKuvvetEkleme->setStatusTip(tr("Nokta birime etki eden kuvvet"));
    connect(tekilKuvvetEkleme,&QAction::triggered,this,&MainWindow::tekilKuvvetEklemeTiklandi);

    yayiliYukEkleme = new QAction(tr("&Yayılı Kuvvet Ekle"),this);
    yayiliYukEkleme->setStatusTip(tr("Belirli bir alana etki eden kuvvet"));
    connect(yayiliYukEkleme,&QAction::triggered,this,&MainWindow::yayiliYukEklemeTiklandi);

    momentEkleme = new QAction(tr("&Moment Ekle"),this);
    momentEkleme->setStatusTip(tr("Döndürme kuvveti"));
    connect(momentEkleme,&QAction::triggered,this,&MainWindow::momentEklemeTiklandi);

    //Hakkında Menüsü
    hakkinda = new QAction(tr("Uygulama &Hakkında"),this);
    hakkinda->setStatusTip(tr("Uygulama hakkında bilgiler verir"));
    connect(hakkinda,&QAction::triggered,this,&MainWindow::hakkindaPenceresiniAc);

    qtHakkinda = new QAction(tr("&Qt Hakkında"),this);
    qtHakkinda->setStatusTip(tr("Uygulamanın Geliştirildiği Çatının Bilgisi"));
    connect(qtHakkinda,&QAction::triggered,qApp,&QApplication::aboutQt);


}

void MainWindow::menulerOlustur()
{
    dosyaMenusu = menuBar()->addMenu(tr("&Dosya"));
    dosyaMenusu->addAction(projeAc);
    dosyaMenusu->addAction(projeyiKaydet);
    dosyaMenusu->addAction(yeniProjeOlustur);
    dosyaMenusu->addAction(cikis);

    projeMenusu = menuBar()->addMenu(tr("&Proje"));
    projeMenusu->addAction(kirisEkleme);
    projeMenusu->addAction(sabitMesnetEkleme);
    projeMenusu->addAction(hareketliMesnetEkleme);
    projeMenusu->addAction(ankastreMesnetEkleme);
    projeMenusu->addAction(tekilKuvvetEkleme);
    projeMenusu->addAction(yayiliYukEkleme);
    projeMenusu->addAction(momentEkleme);

    hakkindaMenusu = menuBar()->addMenu(tr("&Hakkında"));
    hakkindaMenusu->addAction(hakkinda);
    hakkindaMenusu->addAction(qtHakkinda);

}

void MainWindow::aracCubuguOlustur()
{
    QToolButton *isaretciButonu = new QToolButton;
    isaretciButonu->setCheckable(true);
    isaretciButonu->setChecked(true);

    isaretciTipiGrubu = new QButtonGroup(this);
    isaretciTipiGrubu->addButton(isaretciButonu,int(DiagramScene::CisimTasi));
}

void MainWindow::cisimBilgisiGir(int id)
{
    Q_UNUSED(id)
}

void MainWindow::yeniProje()
{
    projeyiSil();
}

void MainWindow::dosyaAc()
{
    QString dosyaIsmi = QFileDialog::getOpenFileName(this,tr("Proje Aç"),"",
                                                     tr("XML (*.xml);;"));

    if (dosyaIsmi.isEmpty()) {
        return;
    }

    QFile dosya(dosyaIsmi);

    if (!dosya.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("uKiriş"),
                             tr("Dosya Okunamadı %1:\n%2.")
                             .arg(dosyaIsmi)
                             .arg(dosya.errorString()));
        return;
    }

    if (dosyaIslemleri->cisimModelListesiAl().size() != 0) {
        scene->kipAta(DiagramScene::CisimSil);
        projeyiSil();
    }
    if (dosyaIslemleri->xmlAc(&dosya) == 0) {
        foreach (auto cisim, dosyaIslemleri->cisimModelListesiAl()) {
            scene->kipAta(DiagramScene::CisimGir);
            emit cisimEkle(cisim);
        }
    }
}

void MainWindow::dosyaKaydet()
{
    QString dosyaIsmi = QFileDialog::getSaveFileName(this,tr("Projeyi Kaydet"),""
                                                     ,tr("XML (*.xml);;"));
    if (dosyaIsmi.isEmpty()) {
        return;
    }
    dosyaIsmi.append(".xml");
    QFile dosya(dosyaIsmi);
    if (!dosya.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("uKiriş"),
                             tr("Dosya Yazılamadı %1:\n%2.")
                             .arg(dosyaIsmi)
                             .arg(dosya.errorString()));
        return;
    }

    dosyaIslemleri->xmlOlarakKaydet(&dosya,cisimTablosu->cisimModelListesiAl());
}

void MainWindow::goruntuOlarakKaydet()
{

    QString dosyaIsmi = QFileDialog::getSaveFileName(this,tr("Kaydet"),QDir::homePath()
                                                     ,tr("PNG (*.png)"));
    if (dosyaIsmi.isEmpty()) {
        return;
    }
    QString proje = dosyaIsmi;
    proje.append(".png");
    QString kesmeDiagrami = dosyaIsmi;
    kesmeDiagrami.append("_kesmenDiagrami.png");
    QString momentDiagrami = dosyaIsmi;
    momentDiagrami.append("_momentDiagrami.png");

    dosyaIslemleri->goruntuOlarakKaydet(proje,scene);
    dosyaIslemleri->goruntuOlarakKaydet(kesmeDiagrami,kesmeDiagramSahnesi);
    dosyaIslemleri->goruntuOlarakKaydet(momentDiagrami,momentDiagramSahnesi);

}

void MainWindow::projeyiSil()
{
    cisimTablosu->tumCisimleriSil();
    kesmeDiagramSahnesi->sonuclariSil();
    momentDiagramSahnesi->sonuclariSil();
    dosyaIslemleri->verileriTemizle();
}

void MainWindow::hakkindaPenceresiniAc()
{
    uygulamaHakkinda->exec();
}


QWidget *MainWindow::cisimHucresiOlustur(const QString &yazi, CisimModeli::CisimTipi tip, const QString &simge)
{
    QToolButton *buton = new QToolButton;
    buton->setIcon(QIcon(simge));
    buton->setIconSize(QSize(50,50));
    buton->setCheckable(true);
    butonGrubu->addButton(buton,int(tip));

    QGridLayout *katman = new QGridLayout;
    katman->addWidget(buton,0,0,Qt::AlignCenter);
    katman->addWidget(new QLabel(yazi),1,0,Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(katman);

    return widget;
}

QToolButton *MainWindow::aracCubuguButonuOlustur(const QString &Yazi, MainWindow::aracCubugu tip, const QString &simge)
{
    QToolButton *buton = new QToolButton;
    buton->setIcon(QIcon(simge));
    buton->setIconSize(QSize(50,50));
    buton->setCheckable(true);
    buton->setToolTip(Yazi);
    projeGrubu->addButton(buton,int(tip));

    return buton;
}
