/*
  ==============================================================================

    DutyCicleWave.h
    Created: 9 Sep 2024 1:03:43pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Defines a class to generate waveforms with a configurable duty cycle.
// ES: Define una clase para generar formas de onda con un ciclo de trabajo configurable.
class DutyCicleWave
{
public:
    // EN: Sets the frequency of the waveform.
    // ES: Establece la frecuencia de la forma de onda.
    void setFrequency(double inFrequency);

    // EN: Sets the duty cycle of the waveform (percentage of the cycle where the signal is "on").
    // ES: Establece el ciclo de trabajo de la forma de onda (porcentaje del ciclo en el que la señal está "activa").
    void setDutyCycle(float inDutyCycle);

    // EN: Prepares the generator by setting the sample rate.
    // ES: Prepara el generador configurando la frecuencia de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes a buffer of audio, generating the waveform.
    // ES: Procesa un buffer de audio, generando la forma de onda.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor - Initializes the generator.
    // ES: Constructor - Inicializa el generador.
    DutyCicleWave();

    // EN: Destructor - Releases resources used by the generator.
    // ES: Destructor - Libera los recursos utilizados por el generador.
    ~DutyCicleWave();

private:
    // EN: The frequency of the waveform in Hz.
    // ES: La frecuencia de la forma de onda en Hz.
    float frequency{ 0.0f };

    // EN: The sample rate of the audio system in Hz (default: 44100 Hz).
    // ES: La frecuencia de muestreo del sistema de audio en Hz (por defecto: 44100 Hz).
    float sampleRate{ 44100 };

    // EN: The amount by which the phase increases per sample, based on frequency and sample rate.
    // ES: La cantidad por la que incrementa la fase por muestra, basada en la frecuencia y la frecuencia de muestreo.
    float phaseIncrement{};

    // EN: The current phase of the waveform for each channel.
    // ES: La fase actual de la forma de onda para cada canal.
    float phase[2]{};

    // EN: The duty cycle of the waveform as a percentage (0–100%).
    // ES: El ciclo de trabajo de la forma de onda como porcentaje (0–100%).
    float dutyCycle{};
};
