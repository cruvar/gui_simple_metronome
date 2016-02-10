#include "mainwindow.h"
#include <portaudio.h>
#include "metronome.h"

#include <QDebug>

MainWindow :: MainWindow(Metronome *metronome, QWidget *parent) : metronome(metronome), QDialog(parent)
{
    startButton    = new QPushButton("Start");
    stopButton     = new QPushButton("Stop");
    closeButton    = new QPushButton("Close");
    startButton->setDefault(true);

    freqLabel        = new QLabel("Freq");
    freqSlider         = new QSlider(Qt::Horizontal);
    freqSpinbox         = new QSpinBox;
    freqSpinbox->setMinimum(500);
    freqSpinbox->setMaximum(2000);
    freqSlider->setMinimum(500);
    freqSlider->setMaximum(2000);
    freqSpinbox->setValue(metronome->getFreq());
    freqSlider->setValue(metronome->getFreq());

    bpmLabel         = new QLabel("BPM ");
    bpmSlider          = new QSlider(Qt::Horizontal);
    bpmSpinbox          = new QSpinBox;
    bpmSpinbox->setMinimum(40);
    bpmSpinbox->setMaximum(240);
    bpmSlider->setMinimum(40);
    bpmSlider->setMaximum(240);
    bpmSpinbox->setValue(metronome->getBpm());
    bpmSlider->setValue(metronome->getBpm());

    window         = new QWidget;
    allLayout      = new QHBoxLayout;
    bpmLayout      = new QHBoxLayout;
    freqLayout     = new QHBoxLayout;
    bfLayout       = new QVBoxLayout;
    buttonLayout   = new QVBoxLayout;

    freqLayout->addWidget(freqLabel);
    freqLayout->addWidget(freqSpinbox);
    freqLayout->addWidget(freqSlider);

    bpmLayout->addWidget(bpmLabel);
    bpmLayout->addWidget(bpmSpinbox);
    bpmLayout->addWidget(bpmSlider);

    bfLayout->addLayout(freqLayout);
    bfLayout->addLayout(bpmLayout);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(closeButton);

    allLayout->addLayout(bfLayout);
    allLayout->addLayout(buttonLayout);

    setLayout(allLayout);
    setWindowTitle("Metronome");

    connect(startButton,    SIGNAL(clicked(bool)),      this, SLOT(StartClicked()));
    connect(stopButton,     SIGNAL(clicked(bool)),      this, SLOT(StopClicked()));
    connect(closeButton,    SIGNAL(clicked()),          this, SLOT(CloseClicked()));
    connect(freqSpinbox,    SIGNAL(valueChanged(int)),  freqSlider, SLOT(setValue(int)));
    connect(freqSlider,     SIGNAL(valueChanged(int)),  freqSpinbox, SLOT(setValue(int)));
    connect(bpmSpinbox,     SIGNAL(valueChanged(int)),  bpmSlider, SLOT(setValue(int)));
    connect(bpmSlider,      SIGNAL(valueChanged(int)),  bpmSpinbox, SLOT(setValue(int)));
    connect(freqSpinbox,    SIGNAL(valueChanged(int)),  this, SLOT(freqChanged(int)));
    connect(bpmSpinbox,     SIGNAL(valueChanged(int)),  this, SLOT(bpmChanged(int)));
    connect(freqSlider,     SIGNAL(valueChanged(int)),  this, SLOT(freqChanged(int)));
    connect(bpmSlider,      SIGNAL(valueChanged(int)),  this, SLOT(bpmChanged(int)));

}

void MainWindow::StartClicked()
{

    metronome->start();
}

void MainWindow::StopClicked()
{

    metronome->stop();
}

void MainWindow::CloseClicked()
{
    metronome->close();
    Pa_Terminate();
    this->close();

}

void MainWindow::bpmChanged(int bpm)
{
    metronome->setBpm(bpm);
}

void MainWindow::freqChanged(int freq)
{
    metronome->setFreq(freq);
}
