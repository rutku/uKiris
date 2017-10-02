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


#ifndef CISIMMODELI_H
#define CISIMMODELI_H

#include <QObject>
#include <QGraphicsItem>
#include <QMap>

class CisimModeli : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum CisimTipi {Kiris, SabitMesnet, HareketliMesnet, AnkastreMesnet,
                    TekilKuvvet, YayiliKuvvet, Moment};
    enum Degerler {Tip, Sira,NoktaKonumu, NoktaKuvveti, BaslangicKonumu, BaslangicKuvveti,
                  BitisKonumu, BitisKuvveti, MomentDegeri};

    CisimModeli(int tip, int noktaKonumu,int noktaKuvveti,int baslangicKonumu,
                int bitisKonumu, int baslangicKuvveti,int bitisKuvveti,int moment, QGraphicsItem *parent = 0);
    CisimModeli(QGraphicsItem *parent = 0);
    QString tipIsmiAl() { return tipIsmim[_tip]; }
    QMap<int,QString> tipIsimleriAl() { return tipIsmim; }
    QMap<int,QString> degerlerinIsimleriniAl() { return degerlerim; }
    QString degerIsmiAl(int deger) { return degerlerim.value(deger); }
    int tipAl() const { return _tip; }
    int tipAl(QString tipIsmi) { return tipIsmim.key(tipIsmi); }
    int siraAl() const { return _sira; }
    double noktaKonumuAl() const { return _noktaKonumu; }
    double noktaKuvvetiAl() const { return _noktaKuvveti; }
    double baslangicKonumuAl() const { return _baslangicKonumu; }
    double bitisKonumuAl() const { return _bitisKonumu; }
    double baslangicKuvvetiAl() const { return _baslangicKuvveti; }
    double bitisKuvvetiAl() const { return _bitisKuvveti; }
    double momentAl() const { return _moment; }


    void tipIsmiAta(QString tipIsmi) { _tipIsmi = tipIsmi; }
    void tipAta(int tip) { _tip = tip; }
    void siraAta(int sira) { _sira = sira; }
    void noktaKonumuAta(double noktaKonumu) { _noktaKonumu = noktaKonumu; }
    void noktaKuvvetiAta(double noktaKuvveti ) { _noktaKuvveti = noktaKuvveti; }
    void baslangciKonumuAta(double baslangicKonumu ) { _baslangicKonumu = baslangicKonumu; }
    void bitisKonumuAta(double bitisKonumu ) { _bitisKonumu = bitisKonumu; }
    void baslangicKuvvetiAta(double baslangicKuvveti ) { _baslangicKuvveti = baslangicKuvveti; }
    void bitisKuvvetiAta(double bitisKuvveti ) { _bitisKuvveti = bitisKuvveti; }
    void momentAta(double moment) { _moment = moment; }
    void tipIsimleriOlustur();
    void degerlerinIsimleriniOlustur();

protected:
    virtual QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
private:
    QString _tipIsmi;
    int _tip;
    int _sira;
    double _noktaKonumu;
    double _noktaKuvveti;
    double _baslangicKonumu;
    double _bitisKonumu;
    double _baslangicKuvveti;
    double _bitisKuvveti;
    double _moment;
    QMap<int,QString> tipIsmim;
    QMap<int,QString> degerlerim;

};

#endif // CISIMMODELI_H
