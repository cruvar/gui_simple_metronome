#include <portaudio.h>
#include <vector>

#ifndef _METRONOME_H_
#define _METRONOME_H_

class Metronome
{
public:
    Metronome();

    struct Beat
    {
        int frequencyTick;
    };
    std::vector<Beat> bar;

    void setBar(std::vector<Beat> bar);
    void setFreq(int);
    void setBpm(int);
    int getFreq();
    int getBpm();
    bool open(PaDeviceIndex);
    void pa_init();
    bool start();
    bool close();
    bool stop();
    void HandleError(PaError &err);

    ~Metronome(void);

private:
        static int paCallback(const void*  inputBuffer,
        void*                           outputBuffer,
        unsigned long                   framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags           statusFlags,
        void*                           userData);
    int frequencyTick = 1000;
    int bpm = 120;
    unsigned int counter = 0;

    PaStream *stream;
};

#endif
