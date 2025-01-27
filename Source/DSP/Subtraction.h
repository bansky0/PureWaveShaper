/*
  ==============================================================================

    Subtraction.h
    Created: 11 Sep 2024 2:32:06pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: The `Subtraction` class generates two oscillators and applies a subtractive synthesis process to their output.
// ES: La clase `Subtraction` genera dos osciladores y aplica un proceso de síntesis sustractiva a su salida.
class Subtraction
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

    // EN: Prepares the object for audio processing by initializing the sample rate.
    // ES: Prepara el objeto para el procesamiento de audio inicializando la frecuencia de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer by generating the output of the two oscillators and applying the subtractive synthesis.
    // ES: Procesa el buffer de audio generando la salida de los dos osciladores y aplicando la síntesis sustractiva.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor initializes the `Subtraction` object.
    // ES: El constructor inicializa el objeto `Subtraction`.
    Subtraction();

    // EN: Destructor cleans up the `Subtraction` object.
    // ES: El destructor limpia el objeto `Subtraction`.
    ~Subtraction();

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

    // EN: Sample rate of the audio system.
    // ES: Frecuencia de muestreo del sistema de audio.
    double sampleRate{};

    // EN: Represents the mathematical constant 2PI, used for phase calculations in oscillators.
    // ES: Representa la constante matemática 2PI, utilizada para cálculos de fase en osciladores.
    float twoPi{ juce::MathConstants<float>::twoPi };

    // EN: Phase increment for the first oscillator, determines its frequency.
    // ES: Incremento de fase para el primer oscilador, determina su frecuencia.
    float phaseIncrement1{};

    // EN: Phase increment for the second oscillator, determines its frequency.
    // ES: Incremento de fase para el segundo oscilador, determina su frecuencia.
    float phaseIncrement2{};

    // EN: Phase accumulators for the first oscillator, one for each stereo channel.
    // ES: Acumuladores de fase para el primer oscilador, uno para cada canal estéreo.
    float phase1[2]{};

    // EN: Phase accumulators for the second oscillator, one for each stereo channel.
    // ES: Acumuladores de fase para el segundo oscilador, uno para cada canal estéreo.
    float phase2[2]{};
};