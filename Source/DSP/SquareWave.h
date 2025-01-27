/*
  ==============================================================================

    SquareWave.h
    Created: 28 Aug 2024 2:25:56pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class to generate a square wave signal.
// ES: Clase para generar una señal de onda cuadrada.
class SquareWave
{
public:
    // EN: Sets the frequency of the square wave.
    // ES: Establece la frecuencia de la onda cuadrada.
    void setFrequency(double inFrequency);

    // EN: Prepares the square wave generator by setting the sample rate.
    // ES: Prepara el generador de onda cuadrada configurando la tasa de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes an audio buffer and fills it with the square wave signal.
    // ES: Procesa un buffer de audio y lo llena con la señal de onda cuadrada.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the SquareWave class.
    // ES: Constructor de la clase SquareWave.
    SquareWave();

    // EN: Destructor for the SquareWave class.
    // ES: Destructor de la clase SquareWave.
    ~SquareWave();

private:
    float frequency{ 0.0f };         // EN: Frequency of the square wave. | ES: Frecuencia de la onda cuadrada.
    float sampleRate{ 44100 };       // EN: Sample rate for the audio processing. | ES: Tasa de muestreo para el procesamiento de audio.
    float time[2]{};                 // EN: Keeps track of the current time position for each channel. | ES: Mantiene la posición de tiempo actual para cada canal.
    float deltaTime[2]{};            // EN: Change in time for each sample, based on the frequency. | ES: Cambio en el tiempo por muestra, basado en la frecuencia.
};