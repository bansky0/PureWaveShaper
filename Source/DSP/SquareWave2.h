/*
  ==============================================================================

    SquareWave2.h
    Created: 8 Sep 2024 2:40:00pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class to generate a square wave signal.
// ES: Clase para generar una señal de onda cuadrada.
class SquareWave2
{
public:
    // EN: Sets the frequency of the square wave.
    // ES: Establece la frecuencia de la onda cuadrada.
    void setFrequency(double inFrequency);

    // EN: Prepares the generator by setting the sample rate.
    // ES: Prepara el generador configurando la tasa de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes an audio buffer and fills it with a square wave signal.
    // ES: Procesa un buffer de audio y lo llena con una señal de onda cuadrada.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the SquareWave2 class.
    // ES: Constructor de la clase SquareWave2.
    SquareWave2();

    // EN: Destructor for the SquareWave2 class.
    // ES: Destructor de la clase SquareWave2.
    ~SquareWave2();

private:
    // EN: Frequency of the square wave in Hz.
    // ES: Frecuencia de la onda cuadrada en Hz.
    float frequency{ 0.0f };

    // EN: Sample rate of the audio in Hz.
    // ES: Tasa de muestreo del audio en Hz.
    float sampleRate{ 44100 };

    // EN: Phase increment for each sample, based on frequency and sample rate.
    // ES: Incremento de fase para cada muestra, basado en la frecuencia y la tasa de muestreo.
    float phaseIncrement{};

    // EN: Phase value for each channel (up to stereo).
    // ES: Valor de fase para cada canal (hasta estéreo).
    float phase[2]{};
};