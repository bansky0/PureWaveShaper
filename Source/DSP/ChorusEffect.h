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

    // Ajusta la profundidad del LFO (profundidad de modulaci�n)
    void setDepth(float inDepth);

    // Ajusta la frecuencia de modulaci�n en un rango de 0 a 100%
    void setRate(float inRatePercentage);

    // Ajusta el retardo inicial (pre-delay)
    void setPredelay(float inPredelay);

    // Procesa el buffer de audio aplicando el efecto de chorus
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate;                  // Frecuencia de muestreo
    float depth;                       // Profundidad de modulaci�n
    float ratePercentage;              // Porcentaje de la velocidad de modulaci�n
    float targetRatePercentage;        // Objetivo de porcentaje de la velocidad de modulaci�n
    float predelay;                    // Retardo inicial (en ms)
    float t;                           // Variable de tiempo para el LFO

    static const int circularBufferSize = 48000; // Tama�o del buffer circular
    float circularBuffer[circularBufferSize][2]; // Buffer circular est�reo
    int writterPointer[2] = { 0, 0 };            // Punteros de escritura para cada canal
};