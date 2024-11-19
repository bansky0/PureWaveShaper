/*
  ==============================================================================

    ModulatedDelay.h
    Created: 13 Nov 2024 3:29:42pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

class ModulatedDelay
{
public:
	ModulatedDelay();
	~ModulatedDelay();

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
