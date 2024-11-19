/*
  ==============================================================================

    SimpleDelay4.h
    Created: 14 Nov 2024 1:48:52pm
    Author:  Jhonatan

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

    void prepare(double theSampleRate);

    // Configura el delay en samples (puede ser fraccional)
    void setDelay(float newDelayInSamples);

    // Agrega una muestra al buffer en el canal correspondiente
    void pushSample(int channel, float sample);

    // Extrae una muestra del buffer aplicando el delay configurado
    float popSample(int channel);

    void process(juce::AudioBuffer<float>& buffer);

private:
    double sampleRate{};
    static constexpr int maxDelaySamples = 48000; // Máximo delay en samples
    std::vector<int> writeIndex;          // Índice de escritura en el buffer
    float delay{};                        // Delay en samples
    int delayInt{};                       // Parte entera del delay
    float delayFrac{};                    // Parte fraccional del delay

    std::vector<std::vector<float>> buffer; // Buffer de delay, un buffer por canal // Inicializa el buffer con ceros
};