/*
  ==============================================================================

    SawtoothWave.h
    Created: 29 Aug 2024 4:38:15pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SawtoothWave
{
public:
    // EN: Sets the frequency of the sawtooth wave.
    // ES: Establece la frecuencia de la onda diente de sierra.
    void setFrequency(double inFrequency);

    // EN: Prepares the wave generator by setting the sample rate.
    // ES: Prepara el generador de ondas configurando la frecuencia de muestreo.
    void prepare(double theSampleRate);

    // EN: Generates the sawtooth wave and processes the audio buffer.
    // ES: Genera la onda diente de sierra y procesa el búfer de audio.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the SawtoothWave class.
    // ES: Constructor de la clase SawtoothWave.
    SawtoothWave();

    // EN: Destructor for the SawtoothWave class.
    // ES: Destructor de la clase SawtoothWave.
    ~SawtoothWave();

private:
    // EN: The frequency of the sawtooth wave.
    // ES: La frecuencia de la onda diente de sierra.
    float frequency{ 100.0f };

    // EN: The sample rate for the audio processing.
    // ES: La frecuencia de muestreo para el procesamiento de audio.
    float sampleRate{ 44100 };

    // EN: Keeps track of the phase (time) for each channel.
    // ES: Lleva un registro de la fase (tiempo) para cada canal.
    float time[2]{};

    // EN: The increment in phase per sample for each channel.
    // ES: El incremento en la fase por muestra para cada canal.
    float deltaTime[2]{};
};
