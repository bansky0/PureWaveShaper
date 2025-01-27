/*
  ==============================================================================

    SawtoothWave2.h
    Created: 9 Sep 2024 1:04:43pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SawtoothWave2
{
public:
    // EN: Sets the frequency of the sawtooth wave.
    // ES: Establece la frecuencia de la onda diente de sierra.
    void setFrequency(double inFrequency);

    // EN: Prepares the generator by setting the sample rate and initializing variables.
    // ES: Prepara el generador configurando la frecuencia de muestreo e inicializando las variables.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer by generating a sawtooth wave.
    // ES: Procesa el búfer de audio generando una onda diente de sierra.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the SawtoothWave2 class.
    // ES: Constructor de la clase SawtoothWave2.
    SawtoothWave2();

    // EN: Destructor for the SawtoothWave2 class.
    // ES: Destructor de la clase SawtoothWave2.
    ~SawtoothWave2();

private:
    // EN: Frequency of the sawtooth wave (in Hz).
    // ES: Frecuencia de la onda diente de sierra (en Hz).
    float frequency{ 100.0f };

    // EN: Sample rate of the audio (in Hz).
    // ES: Frecuencia de muestreo del audio (en Hz).
    float sampleRate{ 44100 };

    // EN: Amount to increment the phase on each sample (calculated based on frequency and sample rate).
    // ES: Cantidad para incrementar la fase en cada muestra (calculada en base a la frecuencia y la frecuencia de muestreo).
    float phaseIncrement{};

    // EN: Array to store the phase value for each channel.
    // ES: Arreglo para almacenar el valor de fase para cada canal.
    float phase[2]{};
};