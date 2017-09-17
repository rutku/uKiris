#include "ayarlar.h"

Ayarlar::Ayarlar(QObject *parent) : QObject(parent)
{
    ayarlariOlustur();
}

void Ayarlar::ayarlariOlustur()
{
    ayarlarinIsimleri.insert(Birimler::UzunlugunBirimi,tr("Uzunluğun Birimi"));
    ayarlarinIsimleri.insert(Birimler::KuvvetinBirimi,tr("Kuvvetin Birimi"));
    ayarlarinIsimleri.insert(Birimler::MomentinBirimi,tr("Momentin Birimi"));
}
