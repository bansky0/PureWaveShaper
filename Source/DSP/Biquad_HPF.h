/*
  ==============================================================================

    Biquad_HPF.h
    Created: 1 Oct 2024 12:18:03pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "Juceheader.h"

// EN: Class definition for a High-Pass Filter (HPF) using the Biquad filter design.
// ES: Definición de una clase para un filtro pasa altos (HPF) utilizando un diseño de filtro Biquad.
class Biquad_HPF
{
public:
    // EN: Constructor - Initializes the filter with default parameters.
    // ES: Constructor - Inicializa el filtro con parámetros predeterminados.
    Biquad_HPF();

    // EN: Destructor - Releases any resources used by the filter.
    // ES: Destructor - Libera cualquier recurso utilizado por el filtro.
    ~Biquad_HPF();

    // EN: Prepares the filter by setting the sample rate and updating the coefficients.
    // ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer by applying the high-pass filter.
    // ES: Procesa un buffer de audio completo aplicando el filtro pasa altos.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample for a specific channel.
    // ES: Procesa una sola muestra para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency of the high-pass filter.
    // ES: Establece la frecuencia de corte del filtro pasa altos.
    void setFrequency(float inFrequency);

    // EN: Sets the quality factor (Q) of the high-pass filter.
    // ES: Establece el factor de calidad (Q) del filtro pasa altos.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current frequency and Q.
    // ES: Actualiza los coeficientes del filtro según la frecuencia y el Q actuales.
    void updateFilter();

private:
    // EN: The current sample rate for processing.
    // ES: La frecuencia de muestreo actual para el procesamiento.
    double sampleRate{ 0.0f };

    // EN: Delay lines for the input and output samples for each channel.
    // ES: Líneas de retardo para las muestras de entrada y salida de cada canal.
    float x1[2] = { 0.0f }; // EN: Previous input sample 1. ES: Muestra de entrada anterior 1.
    float x2[2] = { 0.0f }; // EN: Previous input sample 2. ES: Muestra de entrada anterior 2.
    float y1[2] = { 0.0f }; // EN: Previous output sample 1. ES: Muestra de salida anterior 1.
    float y2[2] = { 0.0f }; // EN: Previous output sample 2. ES: Muestra de salida anterior 2.

    // EN: Filter coefficients and intermediate values.
    // ES: Coeficientes del filtro y valores intermedios.
    float w0{ 0.0f };     // EN: Angular frequency. ES: Frecuencia angular.
    float alpha{ 0.0f };  // EN: Bandwidth scaling factor. ES: Factor de escalado de ancho de banda.

    float b0{ 0.0f };     // EN: Feedforward coefficient 0. ES: Coeficiente de alimentación directa 0.
    float b1{ 0.0f };     // EN: Feedforward coefficient 1. ES: Coeficiente de alimentación directa 1.
    float b2{ 0.0f };     // EN: Feedforward coefficient 2. ES: Coeficiente de alimentación directa 2.
    float a0{ 0.0f };     // EN: Feedback coefficient 0. ES: Coeficiente de retroalimentación 0.
    float a1{ 0.0f };     // EN: Feedback coefficient 1. ES: Coeficiente de retroalimentación 1.
    float a2{ 0.0f };     // EN: Feedback coefficient 2. ES: Coeficiente de retroalimentación 2.

    // EN: Filter parameters.
    // ES: Parámetros del filtro.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz. ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };         // EN: Quality factor. ES: Factor de calidad.
};