#include "diagramScene.h"

#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>

DiagramScene::DiagramScene(QObject *parent)
    : QGraphicsScene(parent)
{
    kipim = CisimTasi;
    cisimRengim  = Qt::white;

}

DiagramScene::~DiagramScene()
{

}

void DiagramScene::kipAta(DiagramScene::Mode kip)
{
    kipim = kip;
}

void DiagramScene::cisimIslemleri(CisimModeli *_cisimModeli)
{
    if (_cisimModeli == nullptr) {
        return;
    }
    switch (kipim) {
    case CisimGir:
    {
        {
            switch (_cisimModeli->tipAl()) {
            case CisimModeli::Kiris:
                kirisCismi = new KirisCismi(_cisimModeli);
                addItem(kirisCismi);
                kirisCismi->setPos(_cisimModeli->baslangciKonumuAl(),0);
                break;
            case CisimModeli::SabitMesnet:
                sabitMesnetCismi = new SabitMesnetCismi(_cisimModeli);
                addItem(sabitMesnetCismi);
                sabitMesnetCismi->setPos(_cisimModeli->noktaKonumuAl(),35);
                break;
            case CisimModeli::HareketliMesnet:
                hareketliMesnet = new HareketliMesnetCismi(_cisimModeli);
                addItem(hareketliMesnet);
                hareketliMesnet->setPos(_cisimModeli->noktaKonumuAl(),60);
                break;
            case CisimModeli::AnkastreMesnet:
                ankastreMesnetCismi = new AnkastreMesnetCismi(_cisimModeli);
                addItem(ankastreMesnetCismi);
                ankastreMesnetCismi->setPos(_cisimModeli->noktaKonumuAl(),0);
                break;
            case CisimModeli::TekilKuvvet:
                tekilKuvvetCismi = new TekilKuvvetCismi(_cisimModeli);
                addItem(tekilKuvvetCismi);
                tekilKuvvetCismi->setPos(_cisimModeli->noktaKonumuAl(),0);
                break;
            case CisimModeli::YayiliKuvvet:
                yayiliKuvvetCismi = new YayiliKuvvetCismi(_cisimModeli);
                addItem(yayiliKuvvetCismi);
                yayiliKuvvetCismi->setPos(_cisimModeli->baslangciKonumuAl(),0);
                break;
            case CisimModeli::Moment:
                momentCismi = new MomentCismi(_cisimModeli);
                addItem(momentCismi);
                momentCismi->setPos(_cisimModeli->noktaKonumuAl()+22,0);
                break;
            default:
                break;
            }
        }
        emit tabloyaCisimEkle(_cisimModeli);
    }
        break;
    case CisimDuzenle:
    {
        {
            switch (_cisimModeli->tipAl()) {
            case CisimModeli::Kiris:
                kirisCismi->setPos(_cisimModeli->baslangciKonumuAl(),0);
                break;
            case CisimModeli::SabitMesnet:
                sabitMesnetCismi->setPos(_cisimModeli->noktaKonumuAl(),35);
                break;
            case CisimModeli::HareketliMesnet:
                hareketliMesnet->setPos(_cisimModeli->noktaKonumuAl(),60);
                break;
            case CisimModeli::AnkastreMesnet:
                ankastreMesnetCismi->setPos(_cisimModeli->noktaKonumuAl(),0);
                break;
            case CisimModeli::TekilKuvvet:
                tekilKuvvetCismi->setPos(_cisimModeli->noktaKonumuAl(),0);
                break;
            case CisimModeli::YayiliKuvvet:
                yayiliKuvvetCismi->setPos(_cisimModeli->baslangciKonumuAl(),0);
                break;
            case CisimModeli::Moment:
                momentCismi->setPos(_cisimModeli->noktaKonumuAl()+22,0);
                break;
            default:
                break;
            }
        }
        emit tabloyuGuncelle(_cisimModeli);
        break;
    }
    case CisimSil:
    {
        {
            foreach (QGraphicsItem *cisim, items(Qt::AscendingOrder)) {
                switch (cisim->type()) {
                case CisimModeli::Kiris:
                {
                    kirisCismi = qgraphicsitem_cast<KirisCismi *>(cisim);
                    if (kirisCismi->tipAl() == _cisimModeli->tipAl() &&
                            kirisCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::SabitMesnet:
                {
                    sabitMesnetCismi = qgraphicsitem_cast<SabitMesnetCismi *>(cisim);
                      if (sabitMesnetCismi->tipAl() == _cisimModeli->tipAl() &&
                            sabitMesnetCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::HareketliMesnet:
                {
                    hareketliMesnet = qgraphicsitem_cast<HareketliMesnetCismi *>(cisim);
                    if (hareketliMesnet->tipAl() == _cisimModeli->tipAl() &&
                            hareketliMesnet->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::AnkastreMesnet:
                {
                    ankastreMesnetCismi = qgraphicsitem_cast<AnkastreMesnetCismi *>(cisim);
                    if (ankastreMesnetCismi->tipAl() == _cisimModeli->tipAl() &&
                            ankastreMesnetCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::TekilKuvvet:
                {
                    tekilKuvvetCismi = qgraphicsitem_cast<TekilKuvvetCismi *>(cisim);
                    if (tekilKuvvetCismi->tipAl() == _cisimModeli->tipAl() &&
                            tekilKuvvetCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::YayiliKuvvet:
                {
                    yayiliKuvvetCismi = qgraphicsitem_cast<YayiliKuvvetCismi *>(cisim);
                    if (yayiliKuvvetCismi->tipAl() == _cisimModeli->tipAl() &&
                            yayiliKuvvetCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                case CisimModeli::Moment:
                {
                    momentCismi = qgraphicsitem_cast<MomentCismi *>(cisim);
                    if (momentCismi->tipAl() == _cisimModeli->tipAl() &&
                            momentCismi->siraAl() == _cisimModeli->siraAl()) {
                        removeItem(cisim);
                    }
                }
                    break;
                default:
                    break;
                }
            }
        }
        break;
    }
    default:
        break;
    }
    update(0,-100,1000,1000);
}
