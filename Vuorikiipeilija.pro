#-------------------------------------------------
#
# Project created by QtCreator 2011-04-07T19:44:25
#
#-------------------------------------------------

#LIBS += -lopengl32
#LIBS += -lgdi32
LIBS +=-lGL
LIBS +=-lGLU
LIBS +=-lglut

QT       += core
QT       -= gui

TARGET = Vuorikiipeilija
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    vuoristo.cpp \
    sidos.cpp \
    poly.cpp \
    piste.cpp \
    mate.cpp \
    liiketaulukko.cpp \
    lihas.cpp \
    fyysinenmaailma.cpp \
    aly.cpp

HEADERS += \
    vuoristo.h \
    tekoaly.h \
    sidos.h \
    poly.h \
    piste.h \
    mate.h \
    liiketaulukko.h \
    lihas.h \
    fyysinenmaailma.h \
    aly.h
