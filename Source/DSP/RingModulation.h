/*
  ==============================================================================

    RingModulation.h
    Created: 12 Sep 2024 2:55:02pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class RingModulation
{
public:
    // EN: Sets the frequency for the first oscillator.
    // ES: Establece la frecuencia para el primer oscilador.
    void setFrequency1(float inFreqOsc1);

    // EN: Sets the amplitude for the first oscillator.
    // ES: Establece la amplitud para el primer oscilador.
    void setAmplitud1(float inAmp1);

    // EN: Sets the frequency for the second oscillator.
    // ES: Establece la frecuencia para el segundo oscilador.
    void setFrequency2(float inFreqOsc2);

    // EN: Sets the amplitude for the second oscillator.
    // ES: Establece la amplitud para el segundo oscilador.
    void setAmplitud2(float inAmp2);

    // EN: Prepares the ring modulation effect by initializing necessary parameters.
    // ES: Prepara el efecto de modulación en anillo inicializando los parámetros necesarios.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer and applies the ring modulation effect.
    // ES: Procesa el búfer de audio y aplica el efecto de modulación en anillo.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the RingModulation class.
    // ES: Constructor de la clase RingModulation.
    RingModulation();

    // EN: Destructor for the RingModulation class.
    // ES: Destructor de la clase RingModulation.
    ~RingModulation();

private:
    // EN: Frequency of the first oscillator.
    // ES: Frecuencia del primer oscilador.
    float osc1{};

    // EN: Amplitude of the first oscillator.
    // ES: Amplitud del primer oscilador.
    float amp1{};

    // EN: Frequency of the second oscillator.
    // ES: Frecuencia del segundo oscilador.
    float osc2{};

    // EN: Amplitude of the second oscillator.
    // ES: Amplitud del segundo oscilador.
    float amp2{};

    // EN: Sample rate used for processing.
    // ES: Frecuencia de muestreo utilizada para el procesamiento.
    double sampleRate{};

    // EN: Constant representing 2PI.
    // ES: Constante que representa 2PI.
    float twoPi{ juce::MathConstants<float>::twoPi };

    // EN: Phase increment for the first oscillator.
    // ES: Incremento de fase para el primer oscilador.
    float phaseIncrement1{};

    // EN: Phase increment for the second oscillator.
    // ES: Incremento de fase para el segundo oscilador.
    float phaseIncrement2{};

    // EN: Phase values for the first oscillator (per channel).
    // ES: Valores de fase para el primer oscilador (por canal).
    float phase1[2]{};

    // EN: Phase values for the second oscillator (per channel).
    // ES: Valores de fase para el segundo oscilador (por canal).
    float phase2[2]{};
};