/*
  ==============================================================================

    EchoStereo.cpp
    Created: 23 Sep 2024 9:46:31am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "EchoStereo.h"

// EN: Set delay times in samples based on BPM
// ES: Establecer los tiempos de delay en muestras basados en BPM
void EchoStereo::setBPM(float BPM1, float BPM2)
{
    float beatsPerMin1 = BPM1; // EN: Beats per minute for input 1
    // ES: Pulsos por minuto para la entrada 1
    float beatsPerSec1 = beatsPerMin1 / 60.0f; // EN: Beats per second
    // ES: Pulsos por segundo
    float secPerBeat1 = 1.0f / beatsPerSec1;   // EN: Seconds per beat
    // ES: Segundos por pulso
    float noteDiv1 = 1.0f;                     // EN: Note division (adjustable)
    // ES: División de nota (ajustable)
    auto timeSec1 = noteDiv1 * secPerBeat1;    // EN: Calculate time in seconds
    // ES: Calcular tiempo en segundos

    delay1Samples = static_cast<int>(std::floor(timeSec1 * sampleRate)); // EN: Convert time to samples
    // ES: Convertir tiempo a muestras

    float beatsPerMin2 = BPM2; // EN: Beats per minute for input 2
    // ES: Pulsos por minuto para la entrada 2
    float beatsPerSec2 = beatsPerMin2 / 60.0f;
    float secPerBeat2 = 1.0f / beatsPerSec2;
    float noteDiv2 = 1.0f;
    auto timeSec2 = noteDiv2 * secPerBeat2;

    delay2Samples = static_cast<int>(std::floor(timeSec2 * sampleRate));
}

// EN: Set gains for each delay channel
// ES: Establecer las ganancias para cada canal de delay
void EchoStereo::setGains(float gain1Value, float gain2Value)
{
    gain1 = gain1Value; // EN: Gain for the first channel
    // ES: Ganancia para el primer canal
    gain2 = gain2Value; // EN: Gain for the second channel
    // ES: Ganancia para el segundo canal
}

// EN: Prepare the delay processor
// ES: Preparar el procesador de delay
void EchoStereo::prepare(double theSampleRate, int inTotalChannels)
{
    sampleRate = theSampleRate; // EN: Set the sample rate
    // ES: Configurar la tasa de muestreo
    circularBufferInput1.resize(circularBufferSize, std::vector<float>(inTotalChannels, 0.0f)); // EN: Initialize circular buffer for input 1
    // ES: Inicializar buffer circular para la entrada 1
    circularBufferInput2.resize(circularBufferSize, std::vector<float>(inTotalChannels, 0.0f)); // EN: Initialize circular buffer for input 2
    // ES: Inicializar buffer circular para la entrada 2

// EN: Initialize write pointers
// ES: Inicializar punteros de escritura
    writterPointerInput1.resize(inTotalChannels, 0);
    writterPointerInput2.resize(inTotalChannels, 0);
}

// EN: Process the audio buffer
// ES: Procesar el buffer de audio
void EchoStereo::process(juce::AudioBuffer<float>& buffer)
{
    auto outputCircularBuffer = 0.0f; // EN: Placeholder for output buffer
    // ES: Variable temporal para el buffer de salida

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (delay1Samples >= 1 || delay2Samples >= 1)
            {
                auto sampleInput = buffer.getReadPointer(channel)[i]; // EN: Read input sample
                // ES: Leer muestra de entrada

// EN: Process left channel (channel 0, using output1)
// ES: Procesar canal izquierdo (canal 0, usando output1)
                if (channel == 0)
                {
                    int readerPointerInput1 = writterPointerInput1[channel] - delay1Samples; // EN: Calculate read pointer for delay
                    // ES: Calcular puntero de lectura para el delay
                    if (readerPointerInput1 < 0)
                        readerPointerInput1 += circularBufferSize;

                    float delayedSampleInput1 = circularBufferInput1[readerPointerInput1][channel]; // EN: Get delayed sample
                    // ES: Obtener muestra retardada
                    float output1 = sampleInput + gain1 * delayedSampleInput1; // EN: Apply gain to delayed sample
                    // ES: Aplicar ganancia a la muestra retardada

// EN: Store in the circular buffer for the left channel
// ES: Guardar en el buffer circular del canal izquierdo
                    circularBufferInput1[writterPointerInput1[channel]][channel] = sampleInput;

                    // EN: Advance the write pointer for the left channel
                    // ES: Avanzar el puntero de escritura del canal izquierdo
                    writterPointerInput1[channel]++;
                    if (writterPointerInput1[channel] >= circularBufferSize)
                        writterPointerInput1[channel] = 0;

                    // EN: Write processed output to the left channel
                    // ES: Escribir la salida procesada en el canal izquierdo
                    buffer.getWritePointer(channel)[i] = output1;
                }

                // EN: Process right channel (channel 1, using output2)
                // ES: Procesar canal derecho (canal 1, usando output2)
                else if (channel == 1)
                {
                    int readerPointerInput2 = writterPointerInput2[channel] - delay2Samples;
                    if (readerPointerInput2 < 0)
                        readerPointerInput2 += circularBufferSize;

                    float delayedSampleInput2 = circularBufferInput2[readerPointerInput2][channel];
                    float output2 = sampleInput + gain2 * delayedSampleInput2;

                    // EN: Store in the circular buffer for the right channel
                    // ES: Guardar en el buffer circular del canal derecho
                    circularBufferInput2[writterPointerInput2[channel]][channel] = sampleInput;

                    // EN: Advance the write pointer for the right channel
                    // ES: Avanzar el puntero de escritura del canal derecho
                    writterPointerInput2[channel]++;
                    if (writterPointerInput2[channel] >= circularBufferSize)
                        writterPointerInput2[channel] = 0;

                    // EN: Write processed output to the right channel
                    // ES: Escribir la salida procesada en el canal derecho
                    buffer.getWritePointer(channel)[i] = output2;
                }
            }
        }
    }
}

// EN: Constructor
// ES: Constructor
EchoStereo::EchoStereo()
{
}

// EN: Destructor
// ES: Destructor
EchoStereo::~EchoStereo()
{
}
