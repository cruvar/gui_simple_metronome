#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <portaudio.h>
#include "metronome.h"

#include <QDialog>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(Metronome *metronome, QWidget *parent=0);

private:
    Metronome   *metronome;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *closeButton;
    QLabel      *freqLabel;
    QSpinBox    *freqSpinbox;
    QSlider     *freqSlider;
    QLabel      *bpmLabel;
    QSpinBox    *bpmSpinbox;
    QSlider     *bpmSlider;
    QWidget     *window;
    QHBoxLayout *allLayout;
    QHBoxLayout *bpmLayout;
    QHBoxLayout *freqLayout;
    QVBoxLayout *bfLayout;
    QVBoxLayout *buttonLayout;

private slots:
    void StartClicked();
    void StopClicked();
    void CloseClicked();
    void bpmChanged(int);
    void freqChanged(int);

signals:


};

#endif // MAINWINDOW_H
