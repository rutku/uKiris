#include "cisimmodeli.h"
#include "diagramScene.h"
#include "cisimekle.h"
#include "mainwindow.h"
#include "kirisekle.h"
#include "mesnetekle.h"
#include "cisimmodeli.h"
#include "tablowidget.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    eylemlerOlustur();
    aracKutusuOlustur();
    menulerOlustur();

    scene = new DiagramScene(cisimMenusu,this);
    scene->setSceneRect(-scene->width(),-scene->height(),scene->width()*2,scene->height()*2);


    cisimTablosu = new TabloWidget(this);
    cisimTablosu->setFixedHeight(200);
    cisimTablosu->setColumnCount(7);

    QStringList cisimTabloBasligi;
    cisimTabloBasligi << tr("Tip") << tr("Nokta\nKonumu (m)") << tr("Nokta Kuvveti\nkN veya kN-m")
                      <<tr("Başlangıç\nNoktası(m)")<<tr("Bitiş\nNoktası(m)")
                     <<tr("Başlangıç\nKuvveti(kN/m)")<<tr("Bitiş\nKuvveti(kN/m)");

    cisimTablosu->setHorizontalHeaderLabels(cisimTabloBasligi);

    connect(scene, SIGNAL(cisimGirildi(CisimOgesi*)),
            this, SLOT(cisimGirildi(CisimOgesi*)));
    connect(scene, SIGNAL(cisimSecildi(CisimOgesi*)),
            this, SLOT(cisimSecildi(CisimOgesi*)));

    aracCubuguOlustur();

    QHBoxLayout *katman = new QHBoxLayout;
    katman->addWidget(aracKutusu);

    QVBoxLayout *yatayKatman = new QVBoxLayout;

    view = new QGraphicsView(scene);
    yatayKatman->addWidget(view);
    yatayKatman->addWidget(cisimTablosu);

    katman->addLayout(yatayKatman);
    QWidget *widget = new QWidget;
    widget->setLayout(katman);

    setCentralWidget(widget);

    setWindowTitle(tr("uKiriş 1.0"));
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::cisimSecildi(CisimOgesi *cisim)
{
    Q_UNUSED(cisim)
}

void MainWindow::butonGrubuTiklandi(int id)
{
    QList<QAbstractButton *> butonlar = butonGrubu->buttons();
    foreach (QAbstractButton *buton, butonlar) {
        if (butonGrubu->button(id) != buton) {
            buton->setChecked(false);
        }
    }

    KirisEkle k(CisimOgesi::CisimTipi(id),this);
    MesnetEkle m(CisimOgesi::CisimTipi(id),this);

    switch (CisimOgesi::CisimTipi(id)) {
    case CisimOgesi::Kiris:
        k.exec();
        scene->cisimModeliAta(k.cisimModeliAl());
        break;
    case CisimOgesi::SabitMesnet:
        m.exec();
        scene->cisimModeliAta(m.cisimModeliAl());
        break;
    case CisimOgesi::HareketliMesnet:
        m.exec();
        scene->cisimModeliAta(m.cisimModeliAl());
        break;
    case CisimOgesi::AnkastreMesnet:
        m.exec();
        scene->cisimModeliAta(m.cisimModeliAl());
        break;
    default:
        break;
    }


    qDebug() << "ID : " << id << " Tip : " << CisimOgesi::CisimTipi(id);
    scene->cisimTipiAta(CisimOgesi::CisimTipi(id));//Buton ID si DiagramType dan alınıyor.
    scene->kipAta(DiagramScene::CisimGir);

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

void MainWindow::cisimGirildi(CisimOgesi *cisim)
{
    scene->kipAta(DiagramScene::Mode(DiagramScene::CisimTasi));
    butonGrubu->button(cisim->cisimTipi())->setChecked(false);
    qDebug() << "Eklenen Cisim : " << cisim->pos();
    cisimTablosu->cisimEkle(cisim->cisimTipi(),0,0,0,0,0,0);
}

void MainWindow::sceneOlcegiDegisti(const QString &olcek)
{
    double yeniOlcek = olcek.left(olcek.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix eskiMatriks = view->matrix();
    view->resetMatrix();
    view->translate(eskiMatriks.dx(),eskiMatriks.dy());
    view->scale(yeniOlcek,yeniOlcek);
}

void MainWindow::cisimEkle(CisimOgesi *cisim)
{
    qDebug() << "Eklenen Cisim " << cisim->pos();
}

void MainWindow::aracKutusuOlustur()
{
    butonGrubu = new QButtonGroup(this);
    butonGrubu->setExclusive(false);

    connect(butonGrubu,SIGNAL(buttonClicked(int)),
            this,SLOT(butonGrubuTiklandi(int)));
    QGridLayout *katman = new QGridLayout;
    katman->addWidget(cisimHucresiOlustur(tr("Kiriş"),CisimOgesi::Kiris),0,0);
    katman->addWidget(cisimHucresiOlustur(tr("Sabit Mesnet"),CisimOgesi::SabitMesnet),0,1);
    katman->addWidget(cisimHucresiOlustur(tr("Hareketli Mesnet"),CisimOgesi::HareketliMesnet),1,0);

    katman->setRowStretch(2, 10);
    katman->setColumnStretch(1,10);

    QWidget *cisimWidget = new QWidget;
    cisimWidget->setLayout(katman);

    aracKutusu = new QToolBox;
    aracKutusu->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    aracKutusu->setMinimumWidth(cisimWidget->sizeHint().width());
    aracKutusu->addItem(cisimWidget,tr("Elemanlar"));

}

void MainWindow::eylemlerOlustur()
{

}

void MainWindow::menulerOlustur()
{
    dosyaMenusu = menuBar()->addMenu(tr("&Dosya"));
    dosyaMenusu->addAction(cikisEylemi);

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


QWidget *MainWindow::cisimHucresiOlustur(const QString &yazi, CisimOgesi::CisimTipi tip)
{
    QToolButton *buton = new QToolButton;
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
