#ifndef DOSYAISLEMLERI_H
#define DOSYAISLEMLERI_H

#include "cisimmodeli.h"

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
    QList<CisimModeli *> xmlAc(QIODevice *dosya);
    void goruntuOlarakKaydet(QString &dosyaYolu,QGraphicsScene *sahne);

private:
    QXmlStreamWriter xmlAkisiYaz;
    QXmlStreamReader xmlAkisiOku;

    double elemaninDegerleriniOku(QDomElement &eleman,QString &ozellikIsmi);
    QDomDocument domBelgesi;
};

#endif // DOSYAISLEMLERI_H
