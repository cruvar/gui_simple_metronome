#include <portaudio.h>
#include "metronome.h"
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc,argv);

    Metronome metronome;

    MainWindow *window = new MainWindow(&metronome);
    window->show();


    return a.exec();

}

