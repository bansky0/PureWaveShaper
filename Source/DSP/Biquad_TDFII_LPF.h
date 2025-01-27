/*
  ==============================================================================

    Biquad_TDFII_LPF.h
    Created: 7 Oct 2024 3:18:16pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// EN: Class representing a Biquad Low-Pass Filter (LPF) implemented in Transposed Direct Form II (TDFII).
// ES: Clase que representa un filtro de paso bajo Biquad (LPF) implementado en Forma Directa Transpuesta II (TDFII).
class Biquad_TDFII_LPF
{
public:
    // EN: Constructor. Initializes the filter instance.
    // ES: Constructor. Inicializa la instancia del filtro.
    Biquad_TDFII_LPF();

    // EN: Destructor. Cleans up the filter instance.
    // ES: Destructor. Limpia la instancia del filtro.
    ~Biquad_TDFII_LPF();

    // EN: Prepares the filter by setting the sample rate.
    // ES: Prepara el filtro configurando la frecuencia de muestreo.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer through the filter.
    // ES: Procesa un buffer completo de audio a través del filtro.
    void process(juce::AudioBuffer<float>& inBuffer);

    // EN: Processes a single audio sample for a specific channel.
    // ES: Procesa una única muestra de audio para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency of the low-pass filter.
    // ES: Establece la frecuencia de corte del filtro de paso bajo.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) of the low-pass filter.
    // ES: Establece el factor Q (resonancia) del filtro de paso bajo.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current parameters.
    // ES: Actualiza los coeficientes del filtro basándose en los parámetros actuales.
    void updateFilter();

private:
    // EN: The sample rate used by the filter.
    // ES: La frecuencia de muestreo utilizada por el filtro.
    double sampleRate{ 0.0f };

    // EN: Delay lines used for the filter's internal state (one for each channel).
    // ES: Líneas de retardo utilizadas para el estado interno del filtro (una por canal).
    float r1[2] = { 0.0f }; // EN: First delay line.
    // ES: Primera línea de retardo.
    float r2[2] = { 0.0f }; // EN: Second delay line.
    // ES: Segunda línea de retardo.

// EN: Filter parameters and intermediate calculations.
// ES: Parámetros del filtro y cálculos intermedios.
    float w0{ 0.0f };      // EN: Angular frequency.
                           // ES: Frecuencia angular.
    float alpha{ 0.0f };   // EN: Filter width and slope.
                           // ES: Ancho y pendiente del filtro.

// EN: Coefficients for the filter equations.
// ES: Coeficientes para las ecuaciones del filtro.
    float b0{ 0.0f };      // EN: Feedforward coefficient b0.
                           // ES: Coeficiente de avance b0.
    float b1{ 0.0f };      // EN: Feedforward coefficient b1.
                           // ES: Coeficiente de avance b1.
    float b2{ 0.0f };      // EN: Feedforward coefficient b2.
                           // ES: Coeficiente de avance b2.
    float a0{ 0.0f };      // EN: Feedback coefficient a0.
                           // ES: Coeficiente de retroalimentación a0.
    float a1{ 0.0f };      // EN: Feedback coefficient a1.
                           // ES: Coeficiente de retroalimentación a1.
    float a2{ 0.0f };      // EN: Feedback coefficient a2.
                           // ES: Coeficiente de retroalimentación a2.

// EN: User-defined parameters for the filter.
// ES: Parámetros definidos por el usuario para el filtro.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz.
                                // ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };          // EN: Quality factor (default value corresponds to Butterworth filter).
                                // ES: Factor de calidad (el valor por defecto corresponde a un filtro Butterworth).
};