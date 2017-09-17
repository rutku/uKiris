#-------------------------------------------------
#
# Project created by QtCreator 2017-05-20T16:49:56
#
#-------------------------------------------------

QT       += core gui widgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uKiris
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    cisimmodeli.cpp \
    tablowidget.cpp \
    diagramItem.cpp \
    diagramScene.cpp \
    KMDiagramSahnesi.cpp \
    dosyaislemleri.cpp \
    arayuzler/kirisekle.cpp \
    arayuzler/mesnetekle.cpp \
    arayuzler/tekilkuvvetekle.cpp \
    arayuzler/yayilikuvvetekle.cpp \
    arayuzler/momentEkle.cpp \
    arayuzler/ankastremesnetekle.cpp \
    cisimler/kirisCismi.cpp \
    cisimler/sabitmesnetcismi.cpp \
    cisimler/ankastremesnetcismi.cpp \
    cisimler/tekilkuvvetcismi.cpp \
    cisimler/yayilikuvvetcismi.cpp \
    cisimler/momentcismi.cpp \
    cisimler/hareketlimesnetCismi.cpp \
    ayarlar.cpp

HEADERS  += mainwindow.h \
    cisimmodeli.h \
    tablowidget.h \
    diagramItem.h \
    diagramScene.h \
    KMDiagramSahnesi.h \
    dosyaislemleri.h \
    arayuzler/kirisekle.h \
    arayuzler/mesnetekle.h \
    arayuzler/tekilkuvvetekle.h \
    arayuzler/yayilikuvvetekle.h \
    arayuzler/momentEkle.h \
    arayuzler/ankastremesnetekle.h \
    cisimler/kirisCismi.h \
    cisimler/sabitmesnetcismi.h \
    cisimler/ankastremesnetcismi.h \
    cisimler/tekilkuvvetcismi.h \
    cisimler/yayilikuvvetcismi.h \
    cisimler/momentcismi.h \
    cisimler/hareketlimesnetCismi.h \
    ayarlar.h

RESOURCES += \
    simgeler.qrc

DISTFILES +=
