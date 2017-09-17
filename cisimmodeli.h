#ifndef CISIMMODELI_H
#define CISIMMODELI_H

#include <QObject>
#include <QGraphicsItem>
#include <QMap>

class CisimModeli : public QObject,public QGraphicsItem
{
    Q_OBJECT
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
    int tipAl() const { return _tip; }
    int tipAl(QString tipIsmi) { return tipIsmim.key(tipIsmi); }
    int siraAl() const { return _sira; }
    double noktaKonumuAl() const { return _noktaKonumu; }
    double noktaKuvvetiAl() const { return _noktaKuvveti; }
    double baslangciKonumuAl() const { return _baslangicKonumu; }
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
