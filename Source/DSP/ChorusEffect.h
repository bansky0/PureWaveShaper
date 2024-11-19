/*
  ==============================================================================

    ChorusEffect.h
    Created: 30 Oct 2024 3:21:25pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#pragma once
#include <JuceHeader.h>

class ChorusFX
{
public:
    ChorusFX();
    ~ChorusFX();

    // Configura la clase con la frecuencia de muestreo
    void prepare(double sampleRate);

    // Ajusta la profundidad del LFO (profundidad de modulación)
    void setDepth(float inDepth);

    // Ajusta la frecuencia de modulación en un rango de 0 a 100%
    void setRate(float inRatePercentage);

    // Ajusta el retardo inicial (pre-delay)
    void setPredelay(float inPredelay);

    // Procesa el buffer de audio aplicando el efecto de chorus
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate;                  // Frecuencia de muestreo
    float depth;                       // Profundidad de modulación
    float ratePercentage;              // Porcentaje de la velocidad de modulación
    float targetRatePercentage;        // Objetivo de porcentaje de la velocidad de modulación
    float predelay;                    // Retardo inicial (en ms)
    float t;                           // Variable de tiempo para el LFO

    static const int circularBufferSize = 48000; // Tamaño del buffer circular
    float circularBuffer[circularBufferSize][2]; // Buffer circular estéreo
    int writterPointer[2] = { 0, 0 };            // Punteros de escritura para cada canal
};