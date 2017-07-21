#include "cisimmodeli.h"
#include "diagramScene.h"
#include "mainwindow.h"
#include "kirisekle.h"
#include "mesnetekle.h"
#include "tekilkuvvetekle.h"
#include "cisimmodeli.h"
#include "tablowidget.h"
#include "yayilikuvvetekle.h"
#include "momentEkle.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), kipim(DiagramScene::CisimGir)
{
    eylemlerOlustur();
    aracKutusuOlustur();
    diagramlariOlustur();
    menulerOlustur();

    scene = new DiagramScene(cisimMenusu,this);
    scene->setSceneRect(-scene->width(),-scene->height(),scene->width()*2,scene->height()*2);

    kirisEkle = new KirisEkle(this);
    mesnetEkle = new MesnetEkle(this);
    tekilKuvvetEkle  = new TekilKuvvetEkle(this);
    yayiliKuvvetEkle = new YayiliKuvvetEkle(this);
    momentEkle = new MomentEkle(this);

    connect(kirisEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimEkle(CisimModeli*)));
    connect(mesnetEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimEkle(CisimModeli*)));
    connect(tekilKuvvetEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimEkle(CisimModeli*)));
    connect(yayiliKuvvetEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimEkle(CisimModeli*)));
    connect(momentEkle,SIGNAL(cisimEkle(CisimModeli*)),
            scene,SLOT(cisimEkle(CisimModeli*)));
    connect(scene,SIGNAL(tabloyaCisimEkle(CisimModeli*)),
            cisimTablosu,SLOT(tabloyaCisimEkle(CisimModeli*)));
    connect(scene,SIGNAL(tabloyuGuncelle(CisimModeli*)),
            cisimTablosu,SLOT(tabloyuGuncelle(CisimModeli*)));
    connect(cisimTablosu,SIGNAL(cisimDuzenle(CisimModeli*)),
            this,SLOT(cisimDuzenle(CisimModeli*)));
    connect(btnCalistir,SIGNAL(clicked(bool)),
            cisimTablosu,SLOT(diagramCiz()));
    connect(cisimTablosu,SIGNAL(kesmeDiagramCiz(QList<CisimModeli*>)),
            kesmeDiagramSahnesi,SLOT(kesmeDiagramiCiz(QList<CisimModeli*>)));




    aracCubuguOlustur();

    QHBoxLayout *katman = new QHBoxLayout;
    katman->addWidget(aracKutusu);

    QVBoxLayout *yatayKatman = new QVBoxLayout;

    view = new QGraphicsView(scene);
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
    delete kesmeDiagramGorunumu;
    delete kesmeDiagramSahnesi;
    delete momenDiagramGorunumu;
    delete momentDiagramSahnesi;

}

void MainWindow::butonGrubuTiklandi(int id)
{
    scene->kipAta(kipim);
    switch (DiagramItem::CisimTipi(id)) {
    case DiagramItem::Kiris:
        kirisEkle->kipAta(kipim);
        kirisEkle->exec();
        break;
    case DiagramItem::SabitMesnet:
        mesnetEkle->kipAta(kipim);
        mesnetEkle->tipAta(id);
        mesnetEkle->exec();
        break;
    case DiagramItem::HareketliMesnet:
        mesnetEkle->kipAta(kipim);
        mesnetEkle->tipAta(id);
        mesnetEkle->exec();
        break;
    case DiagramItem::AnkastreMesnet:
        mesnetEkle->kipAta(kipim);
        mesnetEkle->tipAta(id);
        mesnetEkle->exec();
        break;
    case DiagramItem::TekilKuvvet:
        tekilKuvvetEkle->kipAta(kipim);
        tekilKuvvetEkle->exec();
        break;
    case DiagramItem::YayiliKuvvet:
        yayiliKuvvetEkle->kipAta(kipim);
        yayiliKuvvetEkle->exec();
        break;
    case DiagramItem::Moment:
        momentEkle->kipAta(kipim);
        momentEkle->exec();
        break;
    default:
        break;
    }
    butonGrubu->button(id)->setChecked(false);
}

void MainWindow::cisimSil()
{
    foreach (QGraphicsItem *cisim, scene->selectedItems()) {
        scene->removeItem(cisim);
        delete cisim;
    }

}

void MainWindow::isaretciGrubuTiklandi(int id)
{
    Q_UNUSED(id)
    scene->kipAta(DiagramScene::Mode(isaretciTipiGrubu->checkedId()));

}

void MainWindow::sceneOlcegiDegisti(const QString &olcek)
{
    double yeniOlcek = olcek.left(olcek.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix eskiMatriks = view->matrix();
    view->resetMatrix();
    view->translate(eskiMatriks.dx(),eskiMatriks.dy());
    view->scale(yeniOlcek,yeniOlcek);
}

void MainWindow::cisimDuzenle(CisimModeli *_cisimModeli)
{
    scene->kipAta(DiagramScene::CisimDuzenle);
    switch (_cisimModeli->tipAl()) {
    case DiagramItem::Kiris:
        kirisEkle->kipAta(DiagramScene::CisimDuzenle);
        kirisEkle->cisimModeliAta(_cisimModeli);
        kirisEkle->exec();
        break;
    case DiagramItem::SabitMesnet:
        mesnetEkle->kipAta(DiagramScene::CisimDuzenle);
        mesnetEkle->cisimModeliAta(_cisimModeli);
        mesnetEkle->tipAta(_cisimModeli->tipAl());
        mesnetEkle->exec();
        break;
    case DiagramItem::HareketliMesnet:
        mesnetEkle->kipAta(DiagramScene::CisimDuzenle);
        mesnetEkle->cisimModeliAta(_cisimModeli);
        mesnetEkle->tipAta(_cisimModeli->tipAl());
        mesnetEkle->exec();
        break;
    case DiagramItem::AnkastreMesnet:
        mesnetEkle->kipAta(DiagramScene::CisimDuzenle);
        mesnetEkle->cisimModeliAta(_cisimModeli);
        mesnetEkle->tipAta(_cisimModeli->tipAl());
        mesnetEkle->exec();
        break;
    case DiagramItem::TekilKuvvet:
        tekilKuvvetEkle->kipAta(DiagramScene::CisimDuzenle);
        tekilKuvvetEkle->cisimModeliAta(_cisimModeli);
        tekilKuvvetEkle->exec();
        break;
    case DiagramItem::YayiliKuvvet:
        yayiliKuvvetEkle->kipAta(DiagramScene::CisimDuzenle);
        yayiliKuvvetEkle->cisimModeliAta(_cisimModeli);
        yayiliKuvvetEkle->exec();
        break;
    case DiagramItem::Moment:
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
    butonGrubu = new QButtonGroup(this);
    butonGrubu->setExclusive(false);

    connect(butonGrubu,SIGNAL(buttonClicked(int)),
            this,SLOT(butonGrubuTiklandi(int)));
    QGridLayout *elemanlarKatmani = new QGridLayout;
    elemanlarKatmani->addWidget(cisimHucresiOlustur(tr("Kiriş"),DiagramItem::Kiris,":/simgeler/kiris.png"),0,0);
    elemanlarKatmani->addWidget(cisimHucresiOlustur(tr("Sabit Mesnet"),DiagramItem::SabitMesnet,":/simgeler/sabitMesnet.png"),0,1);
    elemanlarKatmani->addWidget(cisimHucresiOlustur(tr("Hareketli Mesnet"),DiagramItem::HareketliMesnet,":/simgeler/hareketliMesnet.png"),1,0);
    elemanlarKatmani->addWidget(cisimHucresiOlustur(tr("Ankastre Mesnet"),DiagramItem::AnkastreMesnet,":/simgeler/ankastreMesnet.png"),1,1);

    elemanlarKatmani->setRowStretch(2, 10);
    elemanlarKatmani->setColumnStretch(1,10);

    QWidget *elemanlarWidget = new QWidget;
    elemanlarWidget->setLayout(elemanlarKatmani);

    QGridLayout *kuvvetlerKatmani = new QGridLayout;
    kuvvetlerKatmani->addWidget(cisimHucresiOlustur(tr("Tekil Kuvvet"),DiagramItem::TekilKuvvet,":/simgeler/tekilKuvvet.png"),0,0);
    kuvvetlerKatmani->addWidget(cisimHucresiOlustur(tr("Yayılı Kuvvet"),DiagramItem::YayiliKuvvet,":/simgeler/yayiliKuvvet.png"),0,1);
    kuvvetlerKatmani->addWidget(cisimHucresiOlustur(tr("Moment"),DiagramItem::Moment,":/simgeler/momentSol.png"),1,0);

    kuvvetlerKatmani->setRowStretch(2,10);
    kuvvetlerKatmani->setColumnStretch(1,10);

    QWidget *kuvvetlerWidget = new QWidget;
    kuvvetlerWidget->setLayout(kuvvetlerKatmani);

    aracKutusu = new QToolBox;
    aracKutusu->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    aracKutusu->setMinimumWidth(elemanlarWidget->sizeHint().width());
    aracKutusu->addItem(elemanlarWidget,tr("Elemanlar"));
    aracKutusu->addItem(kuvvetlerWidget,tr("Kuvvetler"));

    btnCalistir = new QToolButton;
    btnCalistir->setIconSize(QSize(50,50));
    btnCalistir->setIcon(QIcon(":/simgeler/calistir.png"));

    projeAracCubugu = addToolBar(tr("Proje"));
    projeAracCubugu->addWidget(btnCalistir);
}

void MainWindow::diagramlariOlustur()
{
    kesmeDiagramSahnesi = new KMDiagramSahnesi(this);
    kesmeDiagramGorunumu = new QGraphicsView(kesmeDiagramSahnesi);

    momentDiagramSahnesi = new QGraphicsScene(this);
    momenDiagramGorunumu = new QGraphicsView(momentDiagramSahnesi);


    cisimTablosu = new TabloWidget(this);
    QStringList cisimTabloBasligi;
    cisimTabloBasligi << tr("Tip") << tr("Nokta\nKonumu (m)") << tr("Nokta Kuvveti\nkN veya kN-m")
                      <<tr("Başlangıç\nNoktası(m)")<<tr("Bitiş\nNoktası(m)")
                     <<tr("Başlangıç\nKuvveti(kN/m)")<<tr("Bitiş\nKuvveti(kN/m)")
                    <<tr("Moment\n(kN.m)");

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

    cisimMenusu = menuBar()->addMenu(tr("&Cisim"));

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


QWidget *MainWindow::cisimHucresiOlustur(const QString &yazi, DiagramItem::CisimTipi tip, const QString &simge)
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
