/*
  ==============================================================================

    Biquad_TDFII_Notch.h
    Created: 7 Oct 2024 4:02:43pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Class definition for a Biquad Notch Filter in Transposed Direct Form II.
// This class implements a notch filter with configurable frequency and Q factor.
// ES: Definición de clase para un filtro Biquad de muesca en Forma Directa Transpuesta II.
// Esta clase implementa un filtro de muesca con frecuencia y factor Q configurables.
class Biquad_TDFII_Notch
{
public:
    // EN: Constructor. Initializes the Notch Filter object.
    // ES: Constructor. Inicializa el objeto del filtro de muesca.
    Biquad_TDFII_Notch();

    // EN: Destructor. Cleans up the Notch Filter object.
    // ES: Destructor. Libera los recursos del objeto del filtro de muesca.
    ~Biquad_TDFII_Notch();

    // EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
    // ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer through the Notch Filter.
    // ES: Procesa un buffer completo de audio a través del filtro de muesca.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample for a specific channel using the filter.
    // ES: Procesa una única muestra para un canal específico usando el filtro.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency of the notch filter.
    // ES: Configura la frecuencia de corte del filtro de muesca.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) of the notch filter.
    // ES: Configura el factor Q (resonancia) del filtro de muesca.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the frequency and Q factor.
    // ES: Actualiza los coeficientes del filtro basándose en la frecuencia y el factor Q.
    void updateFilter();

private:
    // EN: The sample rate used for processing audio.
    // ES: La frecuencia de muestreo utilizada para procesar audio.
    double sampleRate{ 0.0f };

    // EN: Delay buffers for storing intermediate results in the filter calculations.
    // ES: Buffers de retardo para almacenar resultados intermedios en los cálculos del filtro.
    float r1[2] = { 0.0f }; // EN: First delay line for each channel. / ES: Primera línea de retardo para cada canal.
    float r2[2] = { 0.0f }; // EN: Second delay line for each channel. / ES: Segunda línea de retardo para cada canal.

    // EN: Intermediate variables for filter calculations.
    // ES: Variables intermedias para los cálculos del filtro.
    float w0{ 0.0f };    // EN: Angular frequency. / ES: Frecuencia angular.
    float alpha{ 0.0f }; // EN: Bandwidth factor. / ES: Factor de ancho de banda.

    // EN: Filter coefficients for the biquad filter.
    // ES: Coeficientes del filtro Biquad.
    float b0{ 0.0f }; // EN: Feedforward coefficient 0. / ES: Coeficiente de avance 0.
    float b1{ 0.0f }; // EN: Feedforward coefficient 1. / ES: Coeficiente de avance 1.
    float b2{ 0.0f }; // EN: Feedforward coefficient 2. / ES: Coeficiente de avance 2.
    float a0{ 0.0f }; // EN: Feedback coefficient 0 (used for normalization). / ES: Coeficiente de retroalimentación 0 (usado para normalización).
    float a1{ 0.0f }; // EN: Feedback coefficient 1. / ES: Coeficiente de retroalimentación 1.
    float a2{ 0.0f }; // EN: Feedback coefficient 2. / ES: Coeficiente de retroalimentación 2.

    // EN: Parameters for the notch filter.
    // ES: Parámetros del filtro de muesca.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz. / ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };         // EN: Quality factor (resonance). / ES: Factor de calidad (resonancia).
};
