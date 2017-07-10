#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diagramItem.h"
#include "diagramScene.h"

class Cisim;
class KirisEkle;
class MesnetEkle;
class TekilKuvvetEkle;
class YayiliKuvvetEkle;
class MomentEkle;
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
    void eylemlerOlustur();
    void menulerOlustur();
    void aracCubuguOlustur();
    void cisimBilgisiGir(int id);


    QWidget *cisimHucresiOlustur(const QString &Yazi,
                                  DiagramItem::CisimTipi tip, const QString &simge);
    DiagramScene *scene;
    DiagramScene *kesmeDiagramSahnesi;
    DiagramScene *momentDiagramSahnesi;
    QGraphicsView *view;
    QGraphicsView *kesmeDiagramGorunumu;
    QGraphicsView *momenDiagramGorunumu;

    TabloWidget *cisimTablosu;
    CisimModeli *cisimModeli;
    KirisEkle *kirisEkle;
    MesnetEkle *mesnetEkle;
    TekilKuvvetEkle *tekilKuvvetEkle;
    YayiliKuvvetEkle *yayiliKuvvetEkle;
    MomentEkle *momentEkle;

    QMenu *dosyaMenusu;
    QMenu *cisimMenusu;
    QMenu *hakkindaMenusu;

    QToolBar *isaretciAracCubugu;
    QToolBar *projeAracCubugu;

    QComboBox *sceneScaleCombo;
    QComboBox *cisimRenkCombo;

    QToolBox *aracKutusu;

    QButtonGroup *butonGrubu;
    QButtonGroup *isaretciTipiGrubu;
    QButtonGroup *projeTipiGrubu;

    QToolButton *calistir;

    DiagramScene::Mode kipim;
};

#endif // MAINWINDOW_H
