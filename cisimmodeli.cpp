#include "cisimmodeli.h"

CisimModeli::CisimModeli(int tip, int noktaKonumu, int noktaYuku, int baslangicKonumu, int bitisKonumu, int baslangicYuku, int bitisYuku, QObject *parent)
    : QObject(parent)
{
    _tip = tip;
    _noktaKonumu = noktaKonumu;
    _noktaYuku = noktaYuku;
    _baslangicKonumu = baslangicKonumu;
    _bitisKonumu = bitisKonumu;
    _baslangicYuku = baslangicYuku;
    _bitisYuku = bitisYuku;
}
