/*
  ==============================================================================

    SlewRateDistortion.h
    Created: 8 Oct 2024 3:00:37pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class that implements slew rate distortion, a type of audio distortion based on limiting the rate of change (slew rate) of a signal.
// ES: Clase que implementa una distorsión por tasa de cambio limitada (slew rate distortion), un tipo de distorsión que limita la velocidad de cambio de la señal.
class SlewRateDistortion
{
public:
    // EN: Constructor for the SlewRateDistortion class.
    // ES: Constructor de la clase SlewRateDistortion.
    SlewRateDistortion();

    // EN: Destructor for the SlewRateDistortion class.
    // ES: Destructor de la clase SlewRateDistortion.
    ~SlewRateDistortion();

    // EN: Prepares the processor with the given sample rate.
    // ES: Prepara el procesador con la tasa de muestreo proporcionada.
    void prepare(double inSampleRate);

    // EN: Processes an audio buffer, applying slew rate distortion to all samples.
    // ES: Procesa un buffer de audio, aplicando la distorsión por tasa de cambio a todas las muestras.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Processes a single audio sample for a specific channel.
    // ES: Procesa una sola muestra de audio para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the maximum frequency limit for the slew rate distortion.
    // ES: Establece el límite de frecuencia máxima para la distorsión por tasa de cambio.
    void setMaxFreq(float inSlewDistortionValue);

    // EN: Updates the slew rate based on the current settings.
    // ES: Actualiza la tasa de cambio (slew rate) según la configuración actual.
    void updateSlewRate();

private:
    double sampleRate{ 44100 }; // EN: Sampling rate in Hz. | ES: Tasa de muestreo en Hz.
    float maxFreq{};            // EN: Maximum frequency for distortion. | ES: Frecuencia máxima para la distorsión.

    float y1[2] = { 0.0f };     // EN: Previous output samples for each channel. | ES: Muestras de salida previas para cada canal.
    float delta[2] = { 0.0f };  // EN: Slew rate applied to each channel. | ES: Tasa de cambio aplicada a cada canal.

    float Ts = 0.0;             // EN: Sampling period (1/sampleRate). | ES: Período de muestreo (1/tasa de muestreo).
    float peak = 1.0;           // EN: Peak value of the output signal. | ES: Valor pico de la señal de salida.
    float slewRate = 0.2;       // EN: Maximum rate of change allowed. | ES: Tasa de cambio máxima permitida.
    float slope = 0.0;          // EN: Current slope or rate of change. | ES: Pendiente o tasa de cambio actual.
    float preSample{};          // EN: Stores the previous sample for calculations. | ES: Almacena la muestra previa para los cálculos.

    // EN: Previously processed samples for feedback (currently commented out).
    // ES: Muestras procesadas previamente para retroalimentación (actualmente comentadas).
    // std::vector<float> prevOut = 0.0;  
};