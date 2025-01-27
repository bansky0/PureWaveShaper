/*
  ==============================================================================

    Biquad_BPF2.h
    Created: 1 Oct 2024 12:25:06pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Biquad_BPF2 class - Implements a second version of a Biquad band-pass filter.
// ES: Clase Biquad_BPF2 - Implementa una segunda versión de un filtro de paso banda Biquad.
class Biquad_BPF2
{
public:
    // EN: Constructor - Initializes the Biquad_BPF2 class with default values.
    // ES: Constructor - Inicializa la clase Biquad_BPF2 con valores predeterminados.
    Biquad_BPF2();

    // EN: Destructor - Cleans up any resources used by the Biquad_BPF2 class.
    // ES: Destructor - Limpia cualquier recurso usado por la clase Biquad_BPF2.
    ~Biquad_BPF2();

    // EN: Prepares the filter for processing by setting the sample rate and updating the coefficients.
    // ES: Prepara el filtro para el procesamiento estableciendo la frecuencia de muestreo y actualizando los coeficientes.
    void prepare(double inSampleRate);

    // EN: Processes an audio buffer by applying the band-pass filter to each sample.
    // ES: Procesa un buffer de audio aplicando el filtro de paso banda a cada muestra.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single audio sample for a given channel using the band-pass filter.
    // ES: Procesa una sola muestra de audio para un canal específico utilizando el filtro de paso banda.
    float processSample(float inSample, int channel);

    // EN: Sets the center frequency of the filter and updates the coefficients.
    // ES: Establece la frecuencia central del filtro y actualiza los coeficientes.
    void setFrequency(float inFrequency);

    // EN: Sets the quality factor (Q) of the filter and updates the coefficients.
    // ES: Establece el factor de calidad (Q) del filtro y actualiza los coeficientes.
    void setQ(float inQ);

    // EN: Updates the coefficients of the band-pass filter based on the frequency and Q values.
    // ES: Actualiza los coeficientes del filtro de paso banda según los valores de frecuencia y Q.
    void updateFilter();

private:
    // EN: The sample rate of the audio signal.
    // ES: La frecuencia de muestreo de la señal de audio.
    double sampleRate{ 0.0f };

    // EN: Delay line for input samples (two samples of delay per channel).
    // ES: Línea de retardo para las muestras de entrada (dos muestras de retardo por canal).
    float x1[2] = { 0.0f }; // EN: First delayed input sample. ES: Primera muestra de entrada retrasada.
    float x2[2] = { 0.0f }; // EN: Second delayed input sample. ES: Segunda muestra de entrada retrasada.

    // EN: Delay line for output samples (two samples of delay per channel).
    // ES: Línea de retardo para las muestras de salida (dos muestras de retardo por canal).
    float y1[2] = { 0.0f }; // EN: First delayed output sample. ES: Primera muestra de salida retrasada.
    float y2[2] = { 0.0f }; // EN: Second delayed output sample. ES: Segunda muestra de salida retrasada.

    // EN: Angular frequency (normalized) and bandwidth scaling factor.
    // ES: Frecuencia angular (normalizada) y factor de escalado de ancho de banda.
    float w0{ 0.0f };   // EN: Normalized angular frequency. ES: Frecuencia angular normalizada.
    float alpha{ 0.0f }; // EN: Bandwidth scaling factor. ES: Factor de escalado de ancho de banda.

    // EN: Filter coefficients for the band-pass filter.
    // ES: Coeficientes del filtro para el filtro de paso banda.
    float b0{ 0.0f }; // EN: Feedforward coefficient for the current stage. ES: Coeficiente directo para la etapa actual.
    float b1{ 0.0f }; // EN: Feedforward coefficient for the previous stage. ES: Coeficiente directo para la etapa anterior.
    float b2{ 0.0f }; // EN: Feedforward coefficient for two stages back. ES: Coeficiente directo para dos etapas atrás.
    float a0{ 0.0f }; // EN: Feedback coefficient for the current stage. ES: Coeficiente de retroalimentación para la etapa actual.
    float a1{ 0.0f }; // EN: Feedback coefficient for the previous stage. ES: Coeficiente de retroalimentación para la etapa anterior.
    float a2{ 0.0f }; // EN: Feedback coefficient for two stages back. ES: Coeficiente de retroalimentación para dos etapas atrás.

    // EN: Parameters for the filter - frequency and quality factor (Q).
    // ES: Parámetros del filtro - frecuencia y factor de calidad (Q).
    float frequency{ 1000.0f }; // EN: Default center frequency (1 kHz). ES: Frecuencia central predeterminada (1 kHz).
    float Q{ 0.707f };         // EN: Default Q factor (approx. 0.707 for Butterworth response). ES: Factor Q predeterminado (aprox. 0.707 para respuesta Butterworth).
};