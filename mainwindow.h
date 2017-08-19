#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diagramItem.h"
#include "diagramScene.h"
#include "KMDiagramSahnesi.h"

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
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void butonGrubuTiklandi(int id);
    void cisimSil();
    void isaretciGrubuTiklandi(int id);
    void sceneOlcegiDegisti(const QString &olcek);
    void cisimDuzenle(CisimModeli *_cisimModeli);

private:
    void aracKutusuOlustur();
    void diagramlariOlustur();
    void eylemlerOlustur();
    void menulerOlustur();
    void aracCubuguOlustur();
    void cisimBilgisiGir(int id);


    QWidget *cisimHucresiOlustur(const QString &Yazi,
                                  DiagramItem::CisimTipi tip, const QString &simge);
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

    QMenu *dosyaMenusu;
    QMenu *cisimMenusu;
    QMenu *hakkindaMenusu;

    QToolBar *isaretciAracCubugu;
    QToolBar *projeAracCubugu;

    QComboBox *sceneScaleCombo;
    QComboBox *cisimRenkCombo;

    QToolBox *aracKutusu;
    QToolBox *diagramlarinKutusu;

    QButtonGroup *butonGrubu;
    QButtonGroup *isaretciTipiGrubu;
    QButtonGroup *projeTipiGrubu;

    QToolButton *btnCalistir;

    DiagramScene::Mode kipim;
};

#endif // MAINWINDOW_H
