#ifndef CISIMMODELI_H
#define CISIMMODELI_H

#include <QObject>
#include <QMap>

class CisimModeli : public QObject
{
    Q_OBJECT
public:
    CisimModeli(int tip, int noktaKonumu,int noktaYuku,int baslangicKonumu,
                int bitisKonumu, int baslangicYuku,int bitisYuku, QObject *parent = 0);
    QString tipIsmiAl() { return tipIsmim[_tip]; }
    int tipAl() const { return _tip; }
    int tipAl(QString tipIsmi) { return tipIsmim.key(tipIsmi); }
    int noktaKonumuAl() const { return _noktaKonumu; }
    int noktaYukuAl() const { return _noktaYuku; }
    int baslangciKonumuAl() const { return _baslangicKonumu; }
    int bitisKonumuAl() const { return _bitisKonumu; }
    int baslangicYukuAl() const { return _baslangicYuku; }
    int bitisYukuAl() const { return _bitisYuku; }

    void tipIsmiAta(QString tipIsmi) { _tipIsmi = tipIsmi; }
    void tipAta(int tip) { _tip = tip; }
    void noktaKonumuAta(int noktaKonumu) { _noktaKonumu = noktaKonumu; }
    void noktaYukuAta(int noktaYuku ) { _noktaYuku = noktaYuku; }
    void baslangciKonumuAta(int baslangicKonumu ) { _baslangicKonumu = baslangicKonumu; }
    void bitisKonumuAta(int bitisKonumu ) { _bitisKonumu = bitisKonumu; }
    void baslangicYukuAta(int baslangicYuku ) { _baslangicYuku = baslangicYuku; }
    void bitisYukuAta(int bitisYuku ) { _bitisYuku = bitisYuku; }
private:
    QString _tipIsmi;
    int _tip;
    int _noktaKonumu;
    int _noktaYuku;
    int _baslangicKonumu;
    int _bitisKonumu;
    int _baslangicYuku;
    int _bitisYuku;
    QMap<int,QString> tipIsmim;
};

#endif // CISIMMODELI_H
