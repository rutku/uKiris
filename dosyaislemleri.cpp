#include "dosyaislemleri.h"

#include <QDebug>

DosyaIslemleri::DosyaIslemleri(QObject *parent)
    : QObject(parent)
{

}

void DosyaIslemleri::xmlOlarakKaydet(QString &dosyaYolu, QList<CisimModeli *> &cisimModeliListesi)
{

}

QList<CisimModeli *> DosyaIslemleri::xmlAc(QString &dosyaYolu)
{
    QList<CisimModeli*> cisimModelListesi;


    return cisimModelListesi;

}

void DosyaIslemleri::goruntuOlarakKaydet(QString &dosyaYolu, QGraphicsScene *sahne)
{
    sahne->clearSelection();
    sahne->setSceneRect(sahne->itemsBoundingRect());
    QImage goruntu(sahne->sceneRect().size().toSize(),QImage::Format_ARGB32);
    goruntu.fill(Qt::white);

    QPainter boyaci(&goruntu);
    sahne->render(&boyaci);
    goruntu.save(dosyaYolu);

}
