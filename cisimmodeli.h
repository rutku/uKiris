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
    QString tipIsmiAl() { return tipIsmim[_tip]; }
    int tipAl() const { return _tip; }
    int tipAl(QString tipIsmi) { return tipIsmim.key(tipIsmi); }
    int noktaKonumuAl() const { return _noktaKonumu; }
    int noktaKuvvetiAl() const { return _noktaKuvveti; }
    int baslangciKonumuAl() const { return _baslangicKonumu; }
    int bitisKonumuAl() const { return _bitisKonumu; }
    int baslangicKuvvetiAl() const { return _baslangicKuvveti; }
    int bitisKuvvetiAl() const { return _bitisKuvveti; }

    void tipIsmiAta(QString tipIsmi) { _tipIsmi = tipIsmi; }
    void tipAta(int tip) { _tip = tip; }
    void noktaKonumuAta(int noktaKonumu) { _noktaKonumu = noktaKonumu; }
    void noktaKuvvetiAta(int noktaKuvveti ) { _noktaKuvveti = noktaKuvveti; }
    void baslangciKonumuAta(int baslangicKonumu ) { _baslangicKonumu = baslangicKonumu; }
    void bitisKonumuAta(int bitisKonumu ) { _bitisKonumu = bitisKonumu; }
    void baslangicKuvvetiAta(int baslangicKuvveti ) { _baslangicKuvveti = baslangicKuvveti; }
    void bitisKuvvetiAta(int bitisKuvveti ) { _bitisKuvveti = bitisKuvveti; }
private:
    QString _tipIsmi;
    int _tip;
    int _noktaKonumu;
    int _noktaKuvveti;
    int _baslangicKonumu;
    int _bitisKonumu;
    int _baslangicKuvveti;
    int _bitisKuvveti;
    int _moment;
    QMap<int,QString> tipIsmim;
};

#endif // CISIMMODELI_H
