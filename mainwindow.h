#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "diagramItem.h"
#include "diagramScene.h"
#include "KMDiagramSahnesi.h"

#include <QMainWindow>
#include <QFileDialog>
class Cisim;
class KirisEkle;
class MesnetEkle;
class TekilKuvvetEkle;
class YayiliKuvvetEkle;
class MomentEkle;
class AnkastreMesnetEkle;
class CisimlerinTabloModeli;
class TabloWidget;
class CisimModeli;
class DosyaIslemleri;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
class QTableWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum aracCubugu {Calistir,Yeni,Kaydet,Ac,GoruntuyuKaydet,Sil};
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void butonGrubunaTiklandi(int id);
    void projeGrubunaTiklandi(int id);
    void cisimDuzenle(CisimModeli *_cisimModeli);

signals:
    void diagramCiz();
    void cisimEkle(CisimModeli *_cisimModeli);

private:
    void aracKutusuOlustur();
    void diagramlariOlustur();
    void eylemlerOlustur();
    void menulerOlustur();
    void aracCubuguOlustur();
    void cisimBilgisiGir(int id);
    void yeniProje();
    void dosyaAc();
    void dosyaKaydet();
    void goruntuOlarakKaydet();
    void projeyiSil();

    QWidget *cisimHucresiOlustur(const QString &Yazi,
                                  CisimModeli::CisimTipi tip, const QString &simge);
    QToolButton *aracCubuguButonuOlustur(const QString &Yazi,
                                  aracCubugu tip, const QString &simge);

    DiagramScene *scene;
    KMDiagramSahnesi *kesmeDiagramSahnesi;
    KMDiagramSahnesi *momentDiagramSahnesi;
    QGraphicsView *view;
    QGraphicsView *kesmeDiagramGorunumu;
    QGraphicsView *momenDiagramGorunumu;


    int kirisUzunlugu;

    TabloWidget *cisimTablosu;
    CisimModeli *cisimModeli;
    KirisEkle *kirisEkle;
    MesnetEkle *mesnetEkle;
    TekilKuvvetEkle *tekilKuvvetEkle;
    YayiliKuvvetEkle *yayiliKuvvetEkle;
    MomentEkle *momentEkle;
    AnkastreMesnetEkle *ankastreMesnetEkle;
    DosyaIslemleri *dosyaIslemleri;

    QMenu *dosyaMenusu;
    QMenu *hakkindaMenusu;

    QToolBar *isaretciAracCubugu;
    QToolBar *projeAracCubugu;

    QComboBox *sceneScaleCombo;
    QComboBox *cisimRenkCombo;

    QToolBox *aracKutusu;
    QToolBox *diagramlarinKutusu;

    QButtonGroup *butonGrubu;
    QButtonGroup *isaretciTipiGrubu;
    QButtonGroup *projeGrubu;

    DiagramScene::Mode kipim;
};

#endif // MAINWINDOW_H
