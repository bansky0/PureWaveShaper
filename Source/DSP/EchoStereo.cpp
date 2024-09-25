/*
  ==============================================================================

    EchoStereo.cpp
    Created: 23 Sep 2024 9:46:31am
    Author:  Jhonatan

  ==============================================================================
*/

#include "EchoStereo.h"

// Establecer los tiempos de delay en muestras
void EchoStereo::setBPM(float BPM1, float BPM2)
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
void EchoStereo::setGains(float gain1Value, float gain2Value)
{
    gain1 = gain1Value;
    gain2 = gain2Value;
}

// Preparar el procesador de delay
void EchoStereo::prepare(double theSampleRate, int inTotalChannels)
{
    sampleRate = theSampleRate;
    circularBufferInput1.resize(circularBufferSize, std::vector<float>(inTotalChannels, 0.0f));
    circularBufferInput2.resize(circularBufferSize, std::vector<float>(inTotalChannels, 0.0f));

    // Inicializar los punteros
        writterPointerInput1.resize(inTotalChannels, 0);
        writterPointerInput2.resize(inTotalChannels, 0);
}

//void EchoStereo::setPan(float inPanValue)
//{
//    panValue = (inPanValue + 100.0f) / 200.0f;
//    panLeft = cosf(panValue * juce::MathConstants<float>::halfPi);  // Pan izquierda
//    panRight = sinf(panValue * juce::MathConstants<float>::halfPi); // Pan derecha
//}

// Procesar el buffer de audio
void EchoStereo::process(juce::AudioBuffer<float>& buffer)
{
    auto outputCircularBuffer = 0.0f;

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (delay1Samples >= 1 || delay2Samples>=1)
            {
                auto sampleInput = buffer.getReadPointer(channel)[i];
                // Procesamiento del canal izquierdo (canal 0, usando output1)
                if (channel == 0) // Canal izquierdo
                {
                    int readerPointerInput1 = writterPointerInput1[channel] - delay1Samples;
                    if (readerPointerInput1 < 0)
                        readerPointerInput1 += circularBufferSize;

                    float delayedSampleInput1 = circularBufferInput1[readerPointerInput1][channel];
                    float output1 = sampleInput + gain1 * delayedSampleInput1;

                    // Guardar en el buffer circular del canal izquierdo
                    circularBufferInput1[writterPointerInput1[channel]][channel] = sampleInput;
                    
                    // Avanzar el puntero de escritura del canal izquierdo
                    writterPointerInput1[channel]++;
                    if (writterPointerInput1[channel] >= circularBufferSize)
                        writterPointerInput1[channel] = 0;

                    // Escribir la salida procesada en el canal izquierdo
                    buffer.getWritePointer(channel)[i] = output1;
                }
                
                // Procesamiento del canal derecho (canal 1, usando output2)
                else if (channel == 1) // Canal derecho
                {
                    int readerPointerInput2 = writterPointerInput2[channel] - delay2Samples;
                    if (readerPointerInput2 < 0)
                        readerPointerInput2 += circularBufferSize;

                    float delayedSampleInput2 = circularBufferInput2[readerPointerInput2][channel];
                    float output2 =sampleInput + gain2 * delayedSampleInput2;
                    
                    // Guardar en el buffer circular del canal derecho
                    circularBufferInput2[writterPointerInput2[channel]][channel] = sampleInput;

                    // Avanzar el puntero de escritura del canal derecho
                    writterPointerInput2[channel]++;
                    if (writterPointerInput2[channel] >= circularBufferSize)
                        writterPointerInput2[channel] = 0;

                    // Escribir la salida procesada en el canal derecho
                    buffer.getWritePointer(channel)[i] = output2;
                }
            }
        }
    }
}

EchoStereo::EchoStereo()
{
}

EchoStereo::~EchoStereo()
{
}