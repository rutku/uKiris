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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
class UygulamaHakkinda;
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
    void eylemleriOlustur();
    void menulerOlustur();
    void aracCubuguOlustur();
    void cisimBilgisiGir(int id);
    void yeniProje();
    void dosyaAc();
    void dosyaKaydet();
    void goruntuOlarakKaydet();
    void projeyiSil();
    void hakkindaPenceresiniAc();
    void kirisEklemeTiklandi() {emit butonGrubunaTiklandi(CisimModeli::Kiris); }
    void sabitMesnetEklemeTiklandi() {emit butonGrubunaTiklandi(CisimModeli::SabitMesnet); }
    void hareketliMesnetEklemeTiklandi() {emit butonGrubunaTiklandi(CisimModeli::HareketliMesnet); }
    void ankastreMesnetEklemeTiklandi() {emit butonGrubunaTiklandi(CisimModeli::AnkastreMesnet); }
    void tekilKuvvetEklemeTiklandi() {emit butonGrubunaTiklandi(CisimModeli::TekilKuvvet); }
    void yayiliYukEklemeTiklandi() {emit butonGrubunaTiklandi(CisimModeli::YayiliKuvvet); }
    void momentEklemeTiklandi() {emit butonGrubunaTiklandi(CisimModeli::Moment); }


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
    UygulamaHakkinda *uygulamaHakkinda;

    QMenu *dosyaMenusu;
    QMenu *projeMenusu;
    QMenu *hakkindaMenusu;

    //Dosya Menüsü
    QAction *projeAc;
    QAction *projeyiKaydet;
    QAction *yeniProjeOlustur;
    QAction *cikis;

    //ProjeMenüsü
    QAction *kirisEkleme;
    QAction *sabitMesnetEkleme;
    QAction *hareketliMesnetEkleme;
    QAction *ankastreMesnetEkleme;
    QAction *tekilKuvvetEkleme;
    QAction *yayiliYukEkleme;
    QAction *momentEkleme;

    //Hakkında
    QAction *hakkinda;
    QAction *qtHakkinda;

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
