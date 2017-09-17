#ifndef DOSYAISLEMLERI_H
#define DOSYAISLEMLERI_H

#include "cisimmodeli.h"
#include "ayarlar.h"

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QGraphicsScene>
#include <QPainter>

class DosyaIslemleri : QObject
{
    Q_OBJECT

public:
    DosyaIslemleri(QObject *parent = 0);
    void xmlOlarakKaydet(QIODevice *dosya, QList<CisimModeli *> cisimModeliListesi);
    int xmlAc(QIODevice *dosya);
    void goruntuOlarakKaydet(QString &dosyaYolu,QGraphicsScene *sahne);
    QList<CisimModeli *> cisimModelListesiAl() { return cisimModelListesi; }
    QMap<int,QString> ayarlariAl() { return ayarlar; }

private:
    QXmlStreamWriter xmlAkisiYaz;
    QXmlStreamReader xmlAkisiOku;

    void cisimleriOku(QDomElement &kok);
    double elemaninDegerleriniOku(QDomElement &eleman,QString &ozellikIsmi);
    void ayarlariOku(QDomElement &kok);

    QDomDocument domBelgesi;
    QList<CisimModeli *> cisimModelListesi;
    QMap<int,QString> ayarlar;
};

#endif // DOSYAISLEMLERI_H
