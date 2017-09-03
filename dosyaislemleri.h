#ifndef DOSYAISLEMLERI_H
#define DOSYAISLEMLERI_H

#include "cisimmodeli.h"

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QGraphicsScene>
#include <QPainter>

class DosyaIslemleri : QObject
{
    Q_OBJECT

public:
    DosyaIslemleri(QObject *parent = 0);
    void xmlOlarakKaydet(QString &dosyaYolu,QList<CisimModeli*> &cisimModeliListesi);
    QList<CisimModeli *> xmlAc(QString &dosyaYolu);
    void goruntuOlarakKaydet(QString &dosyaYolu,QGraphicsScene *sahne);
};

#endif // DOSYAISLEMLERI_H
