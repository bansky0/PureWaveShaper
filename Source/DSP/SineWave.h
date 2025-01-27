/*
  ==============================================================================

    SineWave.h
    Created: 28 Aug 2024 11:32:36am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class that generates a sine wave signal.
// ES: Clase que genera una señal de onda seno.
class SineWave
{
public:
    // EN: Sets the frequency of the sine wave in Hz.
    // ES: Establece la frecuencia de la onda seno en Hz.
    void setFrequency(double inFrequency);

    // EN: Sets the initial phase of the sine wave.
    // ES: Establece la fase inicial de la onda seno.
    void setPhase(double setPhase);

    // EN: Prepares the sine wave generator with a specified sample rate.
    // ES: Prepara el generador de onda seno con una tasa de muestreo especificada.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer, generating the sine wave signal.
    // ES: Procesa el buffer de audio, generando la señal de onda seno.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the SineWave class.
    // ES: Constructor de la clase SineWave.
    SineWave();

    // EN: Destructor for the SineWave class.
    // ES: Destructor de la clase SineWave.
    ~SineWave();

private:
    float sampleRate{ 44100.0f };         // EN: Sample rate in Hz. | ES: Tasa de muestreo en Hz.
    float twoPi{ juce::MathConstants<float>::twoPi }; // EN: Constant for 2PI. | ES: Constante para 2PI.
    float time[2]{};                     // EN: Array to store the current time for each channel. | ES: Arreglo para almacenar el tiempo actual de cada canal.
    float deltaTime[2]{};                 // EN: Array to store the phase increment per sample for each channel. | ES: Arreglo para almacenar el incremento de fase por muestra de cada canal.
    float frequency{ 0.0f };              // EN: Frequency of the sine wave in Hz. | ES: Frecuencia de la onda seno en Hz.
    float phi{ 0.0f };                    // EN: Phase offset of the sine wave. | ES: Desfase de la onda seno.
};