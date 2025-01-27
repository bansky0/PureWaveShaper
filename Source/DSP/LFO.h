/*
  ==============================================================================

    LFO.h
    Created: 27 Aug 2024 10:39:40am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// ES: Definición de la clase LFO (Oscilador de Baja Frecuencia).
// EN: Definition of the LFO class (Low-Frequency Oscillator).
class LFO
{
public:
    // ES: Constructor de la clase LFO.
    // EN: Constructor for the LFO class.
    LFO();

    // ES: Destructor de la clase LFO.
    // EN: Destructor for the LFO class.
    ~LFO();

    // ES: Establece la frecuencia del LFO.
    // EN: Sets the frequency of the LFO.
    void setLFOValue(float inRateValue);

    // ES: Prepara el LFO configurando la frecuencia de muestreo.
    // EN: Prepares the LFO by setting the sample rate.
    void prepare(double theSampleRate);

    // ES: Procesa un buffer de audio generando valores del LFO.
    // EN: Processes an audio buffer by generating LFO values.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // ES: Fórmula del LFO: y = 0.5sin(2PIft) + 0.5.
    // EN: LFO formula: y = 0.5sin(2PIft) + 0.5.

    float sampleRate{ 44100.0f }; // ES: Frecuencia de muestreo en Hz.
                                  // EN: Sampling rate in Hz.

    float twoPi{ juce::MathConstants<float>::twoPi }; // ES: Constante 2PI para cálculos rápidos.
                                                      // EN: 2PI constant for fast calculations.

    float frecuency{ 0 }; // ES: Frecuencia del LFO en Hz.
                          // EN: Frequency of the LFO in Hz.

    float time[2]; // ES: Array que almacena el tiempo actual por canal.
                   // EN: Array storing the current time per channel.

    float deltaTime[2]; // ES: Incremento de tiempo por canal (controla la frecuencia del LFO).
                        // EN: Time increment per channel (controls the LFO frequency).
};
