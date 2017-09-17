#ifndef AYARLAR_H
#define AYARLAR_H

#include <QObject>
#include <QMap>

class Ayarlar : public QObject
{
    Q_OBJECT
public:
    explicit Ayarlar(QObject *parent = nullptr);
    enum Birimler {UzunlugunBirimi, KuvvetinBirimi, MomentinBirimi};

    QMap<int,QString> ayarlarinIsimleriniAl() { return ayarlarinIsimleri; }

signals:

public slots:

private:
    QString uzunlugunBirimi;
    QString kuvvetinBirimi;
    QString momentinBirimi;

    QMap<int,QString> ayarlarinIsimleri;

    void ayarlariOlustur();
};

#endif // AYARLAR_H
