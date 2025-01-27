/*
  ==============================================================================

    Biquad_Notch.h
    Created: 1 Oct 2024 12:27:30pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Class for implementing a biquad notch filter.
// ES: Clase para implementar un filtro notch biquad.
class Biquad_Notch
{
public:
    // EN: Constructor for the notch filter.
    // ES: Constructor para el filtro notch.
    Biquad_Notch();

    // EN: Destructor for cleaning up resources.
    // ES: Destructor para limpiar los recursos.
    ~Biquad_Notch();

    // EN: Prepares the filter with the given sample rate.
    // ES: Prepara el filtro con la frecuencia de muestreo dada.
    void prepare(double inSampleRate);

    // EN: Processes an audio buffer by applying the notch filter.
    // ES: Procesa un buffer de audio aplicando el filtro notch.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample for a specific channel.
    // ES: Procesa una muestra individual para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency of the notch filter.
    // ES: Establece la frecuencia de corte del filtro notch.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (quality factor) of the filter.
    // ES: Establece el factor Q (factor de calidad) del filtro.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on current frequency and Q settings.
    // ES: Actualiza los coeficientes del filtro según la configuración actual de frecuencia y Q.
    void updateFilter();

private:
    // EN: Sample rate of the audio signal.
    // ES: Frecuencia de muestreo de la señal de audio.
    double sampleRate{ 0.0f };

    // EN: Delay buffers for storing past input and output samples (per channel).
    // ES: Buffers de retardo para almacenar muestras pasadas de entrada y salida (por canal).
    float x1[2] = { 0.0f }; // EN: x[n-1].
                            // ES: x[n-1].
    float x2[2] = { 0.0f }; // EN: x[n-2].
                            // ES: x[n-2].
    float y1[2] = { 0.0f }; // EN: y[n-1].
                            // ES: y[n-1].
    float y2[2] = { 0.0f }; // EN: y[n-2].
                            // ES: y[n-2].

// EN: Intermediate filter parameters.
// ES: Parámetros intermedios del filtro.
    float w0{ 0.0f };       // EN: Angular frequency.
                            // ES: Frecuencia angular.
    float alpha{ 0.0f };    // EN: Bandwidth parameter.
                            // ES: Parámetro de ancho de banda.

// EN: Filter coefficients.
// ES: Coeficientes del filtro.
    float b0{ 0.0f }; // EN: Numerator coefficient b0.
                      // ES: Coeficiente del numerador b0.
    float b1{ 0.0f }; // EN: Numerator coefficient b1.
                      // ES: Coeficiente del numerador b1.
    float b2{ 0.0f }; // EN: Numerator coefficient b2.
                      // ES: Coeficiente del numerador b2.
    float a0{ 0.0f }; // EN: Denominator coefficient a0.
                      // ES: Coeficiente del denominador a0.
    float a1{ 0.0f }; // EN: Denominator coefficient a1.
                      // ES: Coeficiente del denominador a1.
    float a2{ 0.0f }; // EN: Denominator coefficient a2.
                      // ES: Coeficiente del denominador a2.

// EN: Filter settings.
// ES: Configuración del filtro.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz.
                                // ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };          // EN: Q factor (default to 1/sqrt(2)).
                                // ES: Factor Q (por defecto 1/sqrt(2).
};
