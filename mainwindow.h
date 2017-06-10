#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diagramitem.h"
#include "cisimogesi.h"

class DiagramScene;
class Cisim;
class KirisEkle;
class MesnetEkle;
class CisimlerinTabloModeli;
class TabloWidget;

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
    void cisimGirildi(CisimOgesi *cisim);
    void cisimSecildi(CisimOgesi *cisim);
    void butonGrubuTiklandi(int id);
    void cisimSil();
    void isaretciGrubuTiklandi(int id);
    void sceneOlcegiDegisti(const QString &olcek);
    void cisimEkle(CisimOgesi *cisim);

private:
    void aracKutusuOlustur();
    void eylemlerOlustur();
    void menulerOlustur();
    void aracCubuguOlustur();
    void cisimBilgisiGir(int id);


    QWidget *cisimHucresiOlustur(const QString &Yazi,
                                  CisimOgesi::CisimTipi tip);
    DiagramScene *scene;
    QGraphicsView *view;
    TabloWidget *cisimTablosu;

    QAction *cikisEylemi;
    QAction *ekleEylemi;
    QAction *silEylemi;

    QMenu *dosyaMenusu;
    QMenu *cisimMenusu;
    QMenu *hakkindaMenusu;

    QToolBar *isaretciAracCubugu;

    QComboBox *sceneScaleCombo;
    QComboBox *cisimRenkCombo;

    QToolBox *aracKutusu;

    QButtonGroup *butonGrubu;
    QButtonGroup *isaretciTipiGrubu;
};

#endif // MAINWINDOW_H
