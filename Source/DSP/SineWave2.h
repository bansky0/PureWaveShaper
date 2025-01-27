/*
  ==============================================================================

    SineWave2.h
    Created: 8 Sep 2024 12:44:04pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Declaration of the SineWave2 class, which generates a sine wave signal.
// ES: Declaración de la clase SineWave2, que genera una señal de onda seno.
class SineWave2
{
public:
    // EN: Sets the frequency of the sine wave in Hz.
    // ES: Establece la frecuencia de la onda seno en Hz.
    void setFrequency(double inFrequency);

    // EN: Sets the initial phase of the sine wave.
    // ES: Establece la fase inicial de la onda seno.
    void setPhase(double setPhase);

    // EN: Prepares the sine wave generator with the specified sample rate.
    // ES: Prepara el generador de onda seno con la tasa de muestreo especificada.
    void prepare(double theSampleRate);

    // EN: Processes an audio buffer to generate the sine wave signal.
    // ES: Procesa un buffer de audio para generar la señal de onda seno.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the SineWave2 class. Initializes default values.
    // ES: Constructor de la clase SineWave2. Inicializa valores por defecto.
    SineWave2();

    // EN: Destructor for the SineWave2 class. Cleans up resources (if necessary).
    // ES: Destructor de la clase SineWave2. Limpia recursos (si es necesario).
    ~SineWave2();

private:
    float sampleRate{ 44100.0f };         // EN: The audio sample rate in Hz. | ES: La tasa de muestreo en Hz.
    float twoPi{ juce::MathConstants<float>::twoPi }; // EN: The constant value 2PI. | ES: El valor constante 2PI.
    float frequency{ 0.0f };             // EN: The frequency of the sine wave in Hz. | ES: La frecuencia de la onda seno en Hz.
    float phi{ 0.0f };                   // EN: The initial phase of the sine wave. | ES: La fase inicial de la onda seno.
    float phaseIncrement{};              // EN: The phase increment per sample, based on the frequency. | ES: El incremento de fase por muestra, basado en la frecuencia.
    float phase[2]{};                    // EN: The current phase for each channel (stereo support). | ES: La fase actual para cada canal (soporte estéreo).
};