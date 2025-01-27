/*
  ==============================================================================

    SimpleDelay4.h
    Created: 14 Nov 2024 1:48:52pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <vector>
#include <JuceHeader.h>

class SimpleDelay4
{
public:
    SimpleDelay4();
    ~SimpleDelay4();

    // EN: Prepares the delay system by setting up the sample rate.
    // ES: Prepara el sistema de delay configurando la frecuencia de muestreo.
    void prepare(double theSampleRate);

    // EN: Sets the delay time in samples, allowing fractional delays.
    // ES: Configura el tiempo de delay en samples, permitiendo delays fraccionales.
    void setDelay(float newDelayInSamples);

    // EN: Adds a sample to the delay buffer at the corresponding channel.
    // ES: Agrega una muestra al buffer de delay en el canal correspondiente.
    void pushSample(int channel, float sample);

    // EN: Extracts a sample from the delay buffer, applying the configured delay.
    // ES: Extrae una muestra del buffer de delay aplicando el tiempo de delay configurado.
    float popSample(int channel);

    // EN: Processes an audio buffer, applying the delay effect to all samples and channels.
    // ES: Procesa un búfer de audio, aplicando el efecto de delay a todas las muestras y canales.
    void process(juce::AudioBuffer<float>& buffer);

private:
    double sampleRate{}; // EN: The sample rate of the audio system.
                         // ES: La frecuencia de muestreo del sistema de audio.

    static constexpr int maxDelaySamples = 48000; // EN: Maximum delay in samples (1 second at 48kHz).
                                                  // ES: Máximo tiempo de delay en samples (1 segundo a 48kHz).

    std::vector<int> writeIndex; // EN: Write index for each channel in the buffer.
                                 // ES: Índice de escritura para cada canal en el buffer.

    float delay{};    // EN: Configured delay in samples (can include fractional part).
                      // ES: Tiempo de delay configurado en samples (puede incluir parte fraccional).
    int delayInt{};   // EN: Integer part of the delay.
                      // ES: Parte entera del tiempo de delay.
    float delayFrac{}; // EN: Fractional part of the delay.
                       // ES: Parte fraccional del tiempo de delay.

    std::vector<std::vector<float>> buffer; // EN: Circular delay buffer for each channel.
                                            // ES: Buffer circular de delay, un buffer por canal.
};