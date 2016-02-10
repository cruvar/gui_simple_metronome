#-------------------------------------------------
#
# Project created by QtCreator 2016-01-26T11:34:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_pa_metronome
TEMPLATE = app


SOURCES += main.cpp\
    metronome.cpp \
    mainwindow.cpp

HEADERS  += \
    metronome.h \
    mainwindow.h

FORMS    +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/portaudio-bin/ -lportaudio_x86
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/portaudio-bin/ -lportaudio_x86
else:unix: LIBS += -L$$PWD/portaudio-bin/ -lportaudio_x86

INCLUDEPATH += $$PWD/portaudio-bin
DEPENDPATH += $$PWD/portaudio-bin
