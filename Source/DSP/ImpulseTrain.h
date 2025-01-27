/*
  ==============================================================================

    ImpulseTrain.h
    Created: 10 Sep 2024 11:13:07am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// Clase ImpulseTrain
// EN: Generates an impulse train signal with adjustable frequency.
// ES: Genera una señal de tren de impulsos con una frecuencia ajustable.
class ImpulseTrain
{
public:
    // Método para establecer la frecuencia del tren de impulsos
    // EN: Sets the frequency of the impulse train.
    // ES: Establece la frecuencia del tren de impulsos.
    void setFrequency(double inFrequency);

    // Método para preparar el tren de impulsos con una frecuencia de muestreo específica
    // EN: Prepares the impulse train with a specified sample rate.
    // ES: Prepara el tren de impulsos con una frecuencia de muestreo específica.
    void prepare(double theSampleRate);

    // Método para procesar un búfer de audio
    // EN: Processes an audio buffer and generates the impulse train signal.
    // ES: Procesa un búfer de audio y genera la señal del tren de impulsos.
    void process(juce::AudioBuffer<float>& buffer);

    // Constructor
    // EN: Initializes the ImpulseTrain object.
    // ES: Inicializa el objeto ImpulseTrain.
    ImpulseTrain();

    // Destructor
    // EN: Cleans up resources used by the ImpulseTrain object.
    // ES: Libera los recursos utilizados por el objeto ImpulseTrain.
    ~ImpulseTrain();

private:
    // Fase para cada canal
    // EN: Phase for each audio channel.
    // ES: Fase para cada canal de audio.
    float phase[2]{ 0.0f, 0.0f };

    // Incremento de fase para controlar el ciclo de la onda
    // EN: Phase increment to control the wave cycle.
    // ES: Incremento de fase para controlar el ciclo de la onda.
    float phaseIncrement = 0.0f;

    // Frecuencia de muestreo
    // EN: The sample rate of the audio system.
    // ES: La frecuencia de muestreo del sistema de audio.
    float sampleRate = 44100.0f;

    // Frecuencia del tren de impulsos
    // EN: The frequency of the impulse train.
    // ES: La frecuencia del tren de impulsos.
    float frequency = 440.0f;
};
