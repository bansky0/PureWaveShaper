/*
  ==============================================================================

    ChorusEffect.h
    Created: 30 Oct 2024 3:21:25pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ChorusFX
{
public:
    ChorusFX();
    ~ChorusFX();

    // EN: Configures the class with the sample rate.
    // ES: Configura la clase con la frecuencia de muestreo.
    void prepare(double sampleRate);

    // EN: Sets the LFO depth (modulation depth).
    // ES: Ajusta la profundidad del LFO (profundidad de modulación).
    void setDepth(float inDepth);

    // EN: Sets the modulation rate in a range of 0 to 100%.
    // ES: Ajusta la frecuencia de modulación en un rango de 0 a 100%.
    void setRate(float inRatePercentage);

    // EN: Sets the initial delay (pre-delay).
    // ES: Ajusta el retardo inicial (pre-delay).
    void setPredelay(float inPredelay);

    // EN: Processes the audio buffer applying the chorus effect.
    // ES: Procesa el buffer de audio aplicando el efecto de chorus.
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate;                  // EN: Sample rate / ES: Frecuencia de muestreo
    float depth;                       // EN: Modulation depth / ES: Profundidad de modulación
    float ratePercentage;              // EN: Modulation rate percentage / ES: Porcentaje de la velocidad de modulación
    float targetRatePercentage;        // EN: Target modulation rate percentage / ES: Objetivo de porcentaje de la velocidad de modulación
    float predelay;                    // EN: Initial delay (in ms) / ES: Retardo inicial (en ms)
    float t;                           // EN: Time variable for the LFO / ES: Variable de tiempo para el LFO

    static const int circularBufferSize = 48000; // EN: Circular buffer size / ES: Tamaño del buffer circular
    float circularBuffer[circularBufferSize][2]; // EN: Stereo circular buffer / ES: Buffer circular estéreo
    int writterPointer[2] = { 0, 0 };            // EN: Write pointers for each channel / ES: Punteros de escritura para cada canal
};