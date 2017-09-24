#include "cisimmodeli.h"
#include "diagramScene.h"
#include "mainwindow.h"
#include "arayuzler/kirisekle.h"
#include "arayuzler/mesnetekle.h"
#include "arayuzler/tekilkuvvetekle.h"
#include "arayuzler/yayilikuvvetekle.h"
#include "arayuzler/momentEkle.h"
#include "arayuzler/ankastremesnetekle.h"
#include "cisimmodeli.h"
#include "tablowidget.h"
#include "dosyaislemleri.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), kipim(DiagramScene::CisimGir)
{

    eylemlerOlustur();
    aracKutusuOlustur();
    diagramlariOlustur();
    menulerOlustur();


    kirisEkle = new KirisEkle(this);
    mesnetEkle = new MesnetEkle(this);
    tekilKuvvetEkle  = new TekilKuvvetEkle(this);
    yayiliKuvvetEkle = new YayiliKuvvetEkle(this);
    momentEkle = new MomentEkle(this);
    ankastreMesnetEkle = new AnkastreMesnetEkle(this);
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
    scene->update(0,0,1000,1000);
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
    scene->setSceneRect(0,-100,width(),height()/2);
    view = new QGraphicsView(scene);
    view->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);

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
//    cisimTabloBasligi << tr("Tip") << tr("Nokta\nKonumu (m)") << tr("Nokta Kuvveti\nkN veya kN-m")
//                      <<tr("Başlangıç\nNoktası(m)")<<tr("Bitiş\nNoktası(m)")
//                     <<tr("Başlangıç\nKuvveti(kN/m)")<<tr("Bitiş\nKuvveti(kN/m)")
//                    <<tr("Moment\n(kN.m)");

    cisimTablosu->setFixedHeight(200);
    cisimTablosu->setColumnCount(cisimTabloBasligi.size());
    cisimTablosu->setHorizontalHeaderLabels(cisimTabloBasligi);



    diagramlarinKutusu = new QToolBox;
    diagramlarinKutusu->addItem(cisimTablosu,tr("Elemanların Tablosu"));
    diagramlarinKutusu->addItem(kesmeDiagramGorunumu,tr("Kesme Diagramı"));
    diagramlarinKutusu->addItem(momenDiagramGorunumu,tr("Moment Diagramı"));

}

void MainWindow::eylemlerOlustur()
{

}

void MainWindow::menulerOlustur()
{
    dosyaMenusu = menuBar()->addMenu(tr("&Dosya"));
    hakkindaMenusu = menuBar()->addMenu(tr("&Hakkında"));

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

    qDebug() << dosyaIslemleri->cisimModelListesiAl().size();
    if (dosyaIslemleri->cisimModelListesiAl().size() != 0) {
        scene->kipAta(DiagramScene::CisimSil);
        cisimTablosu->tumCisimleriSil();
        dosyaIslemleri->verileriTemizle();
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
