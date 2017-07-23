#ifndef CISIMMODELI_H
#define CISIMMODELI_H

#include <QObject>
#include <QMap>

class CisimModeli : public QObject
{
    Q_OBJECT
public:
    CisimModeli(int tip, int noktaKonumu,int noktaKuvveti,int baslangicKonumu,
                int bitisKonumu, int baslangicKuvveti,int bitisKuvveti,int moment, QObject *parent = 0);
    CisimModeli(QObject *parent = 0);
    QString tipIsmiAl() { return tipIsmim[_tip]; }
    int tipAl() const { return _tip; }
    int tipAl(QString tipIsmi) { return tipIsmim.key(tipIsmi); }
    double noktaKonumuAl() const { return _noktaKonumu; }
    double noktaKuvvetiAl() const { return _noktaKuvveti; }
    double baslangciKonumuAl() const { return _baslangicKonumu; }
    double bitisKonumuAl() const { return _bitisKonumu; }
    double baslangicKuvvetiAl() const { return _baslangicKuvveti; }
    double bitisKuvvetiAl() const { return _bitisKuvveti; }
    double momentAl() const { return _moment; }

    void tipIsmiAta(QString tipIsmi) { _tipIsmi = tipIsmi; }
    void tipAta(int tip) { _tip = tip; }
    void noktaKonumuAta(double noktaKonumu) { _noktaKonumu = noktaKonumu; }
    void noktaKuvvetiAta(double noktaKuvveti ) { _noktaKuvveti = noktaKuvveti; }
    void baslangciKonumuAta(double baslangicKonumu ) { _baslangicKonumu = baslangicKonumu; }
    void bitisKonumuAta(double bitisKonumu ) { _bitisKonumu = bitisKonumu; }
    void baslangicKuvvetiAta(double baslangicKuvveti ) { _baslangicKuvveti = baslangicKuvveti; }
    void bitisKuvvetiAta(double bitisKuvveti ) { _bitisKuvveti = bitisKuvveti; }
    void momentAta(double moment) { _moment = moment; }
private:
    QString _tipIsmi;
    int _tip;
    double _noktaKonumu;
    double _noktaKuvveti;
    double _baslangicKonumu;
    double _bitisKonumu;
    double _baslangicKuvveti;
    double _bitisKuvveti;
    double _moment;
    QMap<int,QString> tipIsmim;
};

#endif // CISIMMODELI_H
