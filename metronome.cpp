#include "metronome.h"
#include <iostream>
#include <vector>
#include <portaudio.h>
#include <math.h>

#define SAMPLE_RATE (44100)

Metronome::Metronome()
{
    pa_init();
    open(Pa_GetDefaultOutputDevice());
}

void Metronome::setBar(std::vector<Beat> bar)
{
    this->bar = bar;

}

void Metronome::setFreq(int f)
{
    frequencyTick = f;
}

void Metronome::setBpm(int b)
{
    bpm = b;
}

int Metronome::getFreq()
{
    return frequencyTick;
}

int Metronome::getBpm()
{
    return bpm;
}

bool Metronome::open(PaDeviceIndex index)
{
    PaStreamParameters outputParameters;
    //Metronome *metronome;
    outputParameters.device = index;
    if (outputParameters.device == paNoDevice)
    {
        return false;
    }

    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    PaError err = Pa_OpenStream(&stream,
        NULL,              /* No input. */
        &outputParameters, /* As above. */
        SAMPLE_RATE,
        256,               /* Frames per buffer. */
        paClipOff,         /* No out of range samples expected. */
        paCallback,
        this);

    return true;
}



bool Metronome::start()
{
    if (stream == 0)
        return false;

    PaError err = Pa_StartStream(stream);
    return (err == paNoError);
}

void Metronome::pa_init()
{
    PaError err = Pa_Initialize();
    if (err != paNoError) Pa_Terminate();

}


bool Metronome::close()
{
    if (stream == 0)
        return false;

    PaError err = Pa_CloseStream(stream);
    stream = 0;

    return (err == paNoError);
}



bool Metronome::stop()
{
    if (stream == 0)
        return false;

    PaError err = Pa_StopStream(stream);

    return (err == paNoError);
}


void Metronome::HandleError(PaError &err)
{
    Pa_Terminate();
    std::cout << "Произошла ошибка во время использования потока Portaudio" << std::endl;
    std::cout << "Номер ошибки: " << err << std::endl;
    std::cout << "Сообщение об ошибке: " << Pa_GetErrorText(err) << std::endl;
    exit(err);
}



int Metronome::paCallback	(const		void*						inputBuffer,
                                        void*                       outputBuffer,
                            unsigned	long						framesPerBuffer,
                            const		PaStreamCallbackTimeInfo*	timeInfo,
                                        PaStreamCallbackFlags       statusFlags,
                                        void*                       userData)

{
        Metronome *metronome = (Metronome*)userData;
        float sampleVal;
        const float pi = 3.14159265358;
        float *out = (float*)outputBuffer;
        float framesInMs = SAMPLE_RATE / 1000.0;			//количество кадров в одной мс. = 44.1
        double tick = framesInMs * 100;                     //длительность одного тика в кадрах
        double delayMs = (1000 * 60) / metronome->bpm;      //интервал в мс
        double interval = (framesInMs * delayMs);           //интервал между тиками в кадрах. =

        for (unsigned int i = 0; i < framesPerBuffer; i++)
        {


           sampleVal = (float)sin(2.0*pi*metronome->frequencyTick*(metronome->counter) / SAMPLE_RATE);

            if (metronome->counter < tick)
            {
                *out++ = sampleVal;
                *out++ = sampleVal;
                metronome->counter++;
            }
            else
                if (metronome->counter < interval)
                {
                    *out++ = 0;
                    *out++ = 0;
                    metronome->counter++;
                }
                else
                    metronome->counter = 0;
        }

        return 0;
    }


    Metronome::~Metronome(void)
    {
    }
