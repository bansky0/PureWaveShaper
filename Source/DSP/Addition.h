/*
  ==============================================================================

    Addition.h
    Created: 10 Sep 2024 1:57:19pm
    Author:  Jhonatan  López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class AdditiveSynth: Implements a simple additive synthesizer with two oscillators.
// ES: Clase AdditiveSynth: Implementa un sintetizador aditivo simple con dos osciladores.

class AdditiveSynth
{
public:

    // EN: Sets the frequency of the first oscillator.
    // ES: Establece la frecuencia del primer oscilador.
    void setFrequency1(float inFreqOsc1);

    // EN: Sets the amplitude of the first oscillator.
    // ES: Establece la amplitud del primer oscilador.
    void setAmplitud1(float inAmp1);

    // EN: Sets the frequency of the second oscillator.
    // ES: Establece la frecuencia del segundo oscilador.
    void setFrequency2(float inFreqOsc2);

    // EN: Sets the amplitude of the second oscillator.
    // ES: Establece la amplitud del segundo oscilador.
    void setAmplitud2(float inAmp1);

    // EN: Prepares the synthesizer with the given sample rate.
    // ES: Prepara el sintetizador con la frecuencia de muestreo dada.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer to generate sound using the oscillators.
    // ES: Procesa el buffer de audio para generar sonido utilizando los osciladores.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the AdditiveSynth class.
    // ES: Constructor de la clase AdditiveSynth.
    AdditiveSynth();

    // EN: Destructor for the AdditiveSynth class.
    // ES: Destructor de la clase AdditiveSynth.
    ~AdditiveSynth();

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

    // EN: Sample rate for the audio processing.
    // ES: Frecuencia de muestreo para el procesamiento de audio.
    double sampleRate{};

    // EN: Constant for 2pi, used in phase calculations.
    // ES: Constante para 2pi, utilizada en cálculos de fase.
    float twoPi{ juce::MathConstants<float>::twoPi };

    // EN: Phase increment for the first oscillator.
    // ES: Incremento de fase para el primer oscilador.
    float phaseIncrement1{};

    // EN: Phase increment for the second oscillator.
    // ES: Incremento de fase para el segundo oscilador.
    float phaseIncrement2{};

    // EN: Phase accumulator for the first oscillator, one per channel (stereo).
    // ES: Acumulador de fase para el primer oscilador, uno por canal (estéreo).
    float phase1[2]{};

    // EN: Phase accumulator for the second oscillator, one per channel (stereo).
    // ES: Acumulador de fase para el segundo oscilador, uno por canal (estéreo).
    float phase2[2]{};
};