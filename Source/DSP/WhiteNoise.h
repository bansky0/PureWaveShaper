/*
  ==============================================================================

    WhiteNoise.h
    Created: 10 Sep 2024 1:12:37pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: The WhiteNoise class generates white noise audio signals.
// ES: La clase WhiteNoise genera señales de ruido blanco.

class WhiteNoise
{
public:
    // EN: Constructor. Initializes the WhiteNoise object.
    // ES: Constructor. Inicializa el objeto WhiteNoise.
    WhiteNoise();

    // EN: Destructor. Cleans up the WhiteNoise object.
    // ES: Destructor. Libera el objeto WhiteNoise.
    ~WhiteNoise();

    // EN: Prepares the WhiteNoise generator by setting the sample rate.
    // ES: Prepara el generador de ruido blanco configurando la tasa de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer by filling it with white noise.
    // ES: Procesa el buffer de audio llenándolo con ruido blanco.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: Stores the current sample rate of the audio processing system.
    // ES: Almacena la tasa de muestreo actual del sistema de procesamiento de audio.
    double sampleRate;

    // EN: Random number generator used to produce white noise samples.
    // ES: Generador de números aleatorios usado para producir muestras de ruido blanco.
    juce::Random randomGenerator;
};