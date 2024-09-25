/*
  ==============================================================================

    PingPongEcho.cpp
    Created: 24 Sep 2024 10:48:08am
    Author:  Jhonatan

  ==============================================================================
*/

#include "PingPongEcho.h"

// Establecer los tiempos de delay en muestras
void PingPongEcho::setBPM(float BPM1, float BPM2)
{
    float beatsPerMin1 = BPM1;
    float beatsPerSec1 = beatsPerMin1 / 60.0f;
    float secPerBeat1 = 1.0f / beatsPerSec1;
    float noteDiv1 = 1.0f; // Esto podría ser ajustable para diferentes subdivisiones
    auto timeSec1 = noteDiv1 * secPerBeat1;

    delay1Samples = static_cast<int>(std::floor(timeSec1 * sampleRate));

    float beatsPerMin2 = BPM2;
    float beatsPerSec2 = beatsPerMin2 / 60.0f;
    float secPerBeat2 = 1.0f / beatsPerSec2;
    float noteDiv2 = 1.0f; // Esto podría ser ajustable para diferentes subdivisiones
    auto timeSec2 = noteDiv2 * secPerBeat2;

    delay2Samples = static_cast<int>(std::floor(timeSec2 * sampleRate));
}

// Establecer las ganancias para cada delay
void PingPongEcho::setGains(float gain1Value, float gain2Value)
{
    gain1 = gain1Value;
    gain2 = gain2Value;
}

// Preparar el procesador de delay
void PingPongEcho::prepare(double theSampleRate, int inTotalChannels)
{
    sampleRate = theSampleRate;
    circularBufferInput1.resize(circularBufferSize, std::vector<float>(inTotalChannels, 0.0f));
    circularBufferInput2.resize(circularBufferSize, std::vector<float>(inTotalChannels, 0.0f));

    // Inicializar los punteros
    writterPointerInput1.resize(inTotalChannels, 0);
    writterPointerInput2.resize(inTotalChannels, 0);
}

void PingPongEcho::process(juce::AudioBuffer<float>& buffer)
{
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        // Obtener la señal de entrada de cada canal
        auto leftInput = buffer.getReadPointer(0)[i];  // Canal izquierdo
        auto rightInput = buffer.getReadPointer(1)[i]; // Canal derecho

        // --- Procesamiento del canal izquierdo ---
        int readerPointerInputLeft = writterPointerInput2[1] - delay1Samples; // Leer del canal derecho
        if (readerPointerInputLeft < 0)
            readerPointerInputLeft += circularBufferSize;

        float delayedSampleFromRight = circularBufferInput2[readerPointerInputLeft][1]; // Señal retrasada del derecho
        float leftOutput = leftInput - gain1 * delayedSampleFromRight; // Canal izquierdo + feedback derecho

        // Guardar la salida procesada del canal izquierdo en el buffer circular del canal derecho (feedback cruzado)
        circularBufferInput1[writterPointerInput1[0]][0] = leftOutput;

        // Avanzar el puntero de escritura del canal izquierdo
        writterPointerInput1[0]++;
        if (writterPointerInput1[0] >= circularBufferSize)
            writterPointerInput1[0] = 0;

        // Escribir la salida procesada en el canal izquierdo
        buffer.getWritePointer(0)[i] = leftOutput;

        // --- Procesamiento del canal derecho ---
        int readerPointerInputRight = writterPointerInput1[0] - delay2Samples; // Leer del canal izquierdo
        if (readerPointerInputRight < 0)
            readerPointerInputRight += circularBufferSize;

        float delayedSampleFromLeft = circularBufferInput1[readerPointerInputRight][0]; // Señal retrasada del izquierdo
        float rightOutput = rightInput - gain2 * delayedSampleFromLeft; // Canal derecho + feedback izquierdo

        // Guardar la salida procesada del canal derecho en el buffer circular del canal izquierdo (feedback cruzado)
        circularBufferInput2[writterPointerInput2[1]][1] = rightOutput;

        // Avanzar el puntero de escritura del canal derecho
        writterPointerInput2[1]++;
        if (writterPointerInput2[1] >= circularBufferSize)
            writterPointerInput2[1] = 0;

        // Escribir la salida procesada en el canal derecho
        buffer.getWritePointer(1)[i] = rightOutput;
    }
}

PingPongEcho::PingPongEcho()
{
}

PingPongEcho::~PingPongEcho()
{
}