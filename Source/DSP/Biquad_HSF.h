/*
  ==============================================================================

    Biquad_HSF.h
    Created: 1 Oct 2024 12:26:59pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Class definition for a Biquad High-Shelf Filter (HSF).
// ES: Definición de clase para un filtro biquad de estante alto (HSF).
class Biquad_HSF
{
public:
    // EN: Constructor - Initializes the High-Shelf Filter.
    // ES: Constructor - Inicializa el filtro de estante alto.
    Biquad_HSF();

    // EN: Destructor - Cleans up resources used by the filter.
    // ES: Destructor - Libera los recursos utilizados por el filtro.
    ~Biquad_HSF();

    // EN: Prepares the filter by setting the sample rate.
    // ES: Prepara el filtro configurando la frecuencia de muestreo.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer, applying the high-shelf filter to all channels and samples.
    // ES: Procesa un buffer de audio completo, aplicando el filtro de estante alto a todos los canales y muestras.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample for a specific channel using the high-shelf filter coefficients.
    // ES: Procesa una sola muestra para un canal específico utilizando los coeficientes del filtro de estante alto.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency for the high-shelf filter.
    // ES: Establece la frecuencia de corte para el filtro de estante alto.
    void setFrequency(float inFrequency);

    // EN: Sets the quality factor (Q) for the high-shelf filter.
    // ES: Establece el factor de calidad (Q) para el filtro de estante alto.
    void setQ(float inQ);

    // EN: Sets the gain (boost/cut) for the high-shelf filter.
    // ES: Establece la ganancia (realce/atenuación) para el filtro de estante alto.
    void setGain(float inGain);

    // EN: Updates the filter coefficients based on the current parameters.
    // ES: Actualiza los coeficientes del filtro según los parámetros actuales.
    void updateFilter();

private:
    // EN: Sample rate of the audio being processed.
    // ES: Frecuencia de muestreo del audio procesado.
    double sampleRate{ 0.0f };

    // EN: Delay lines for input samples (x1, x2) and output samples (y1, y2) for each channel.
    // ES: Líneas de retardo para muestras de entrada (x1, x2) y muestras de salida (y1, y2) para cada canal.
    float x1[2] = { 0.0f };
    float x2[2] = { 0.0f };
    float y1[2] = { 0.0f };
    float y2[2] = { 0.0f };

    // EN: Variables for angular frequency (w0) and bandwidth scaling factor (alpha).
    // ES: Variables para la frecuencia angular (w0) y el factor de escalado de ancho de banda (alpha).
    float w0{ 0.0f };
    float alpha{ 0.0f };

    // EN: Filter coefficients for the high-shelf filter.
    // ES: Coeficientes del filtro para el filtro de estante alto.
    float b0{ 0.0f };
    float b1{ 0.0f };
    float b2{ 0.0f };
    float a0{ 0.0f };
    float a1{ 0.0f };
    float a2{ 0.0f };

    // EN: Filter parameters - frequency, quality factor (Q), and gain.
    // ES: Parámetros del filtro - frecuencia, factor de calidad (Q) y ganancia.
    float frequency{ 1000.0f }; // EN: Default cutoff frequency (Hz). ES: Frecuencia de corte por defecto (Hz).
    float Q{ 0.707f };          // EN: Default quality factor. ES: Factor de calidad por defecto.
    float Gain{ 0.0f };         // EN: Gain for the high-shelf filter (dB). ES: Ganancia para el filtro de estante alto (dB).

    // EN: Linear amplitude scaling factor calculated from gain.
    // ES: Factor de escalado de amplitud lineal calculado a partir de la ganancia.
    float A{ 0.0f };
};
