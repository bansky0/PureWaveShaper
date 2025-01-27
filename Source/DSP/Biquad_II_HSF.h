/*
  ==============================================================================

    Biquad_II_HSF.h
    Created: 7 Oct 2024 11:59:38am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Class definition for a second-order Biquad filter in Direct Form II for high-shelf filtering.
// ES: Definición de clase para un filtro Biquad de segundo orden en forma directa II para filtrado en estantería alta.
class Biquad_II_HSF
{
public:
    // EN: Constructor - Initializes the class and its members.
    // ES: Constructor - Inicializa la clase y sus miembros.
    Biquad_II_HSF();

    // EN: Destructor - Cleans up the class, no specific tasks required since there are no dynamic allocations.
    // ES: Destructor - Limpia la clase, no se requieren tareas específicas ya que no hay asignaciones dinámicas.
    ~Biquad_II_HSF();

    // EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
    // ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer, applying the high-shelf filter to all samples and channels.
    // ES: Procesa un buffer de audio completo, aplicando el filtro de estantería alta a todas las muestras y canales.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample for a specific channel using the high-shelf filter.
    // ES: Procesa una muestra específica para un canal utilizando el filtro de estantería alta.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency for the high-shelf filter and updates the coefficients.
    // ES: Configura la frecuencia de corte para el filtro de estantería alta y actualiza los coeficientes.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) for the high-shelf filter and updates the coefficients.
    // ES: Configura el factor Q (resonancia) para el filtro de estantería alta y actualiza los coeficientes.
    void setQ(float inQ);

    // EN: Sets the gain for the high-shelf filter and updates the coefficients.
    // ES: Configura la ganancia para el filtro de estantería alta y actualiza los coeficientes.
    void setGain(float inGain);

    // EN: Updates the filter coefficients based on the current frequency, Q factor, gain, and sample rate.
    // ES: Actualiza los coeficientes del filtro según la frecuencia, el factor Q, la ganancia y la frecuencia de muestreo actuales.
    void updateFilter();

private:
    // EN: The sample rate of the audio signal being processed.
    // ES: La frecuencia de muestreo de la señal de audio que se procesa.
    double sampleRate{ 0.0f };

    // EN: State variables for the delay lines in the Direct Form II structure, one for each channel.
    // ES: Variables de estado para las líneas de retardo en la estructura de forma directa II, una para cada canal.
    float w1[2] = { 0.0f };
    float w2[2] = { 0.0f };

    // EN: Intermediate variables for filter calculations.
    // ES: Variables intermedias para los cálculos del filtro.
    float w0{ 0.0f };     // EN: Angular frequency. // ES: Frecuencia angular.
    float alpha{ 0.0f };  // EN: Smoothing factor based on Q. // ES: Factor de suavizado basado en Q.

    // EN: Coefficients for the biquad filter equation.
    // ES: Coeficientes para la ecuación del filtro biquad.
    float b0{ 0.0f }; // EN: Numerator coefficient 0. // ES: Coeficiente del numerador 0.
    float b1{ 0.0f }; // EN: Numerator coefficient 1. // ES: Coeficiente del numerador 1.
    float b2{ 0.0f }; // EN: Numerator coefficient 2. // ES: Coeficiente del numerador 2.
    float a0{ 0.0f }; // EN: Denominator coefficient 0 (normalized). // ES: Coeficiente del denominador 0 (normalizado).
    float a1{ 0.0f }; // EN: Denominator coefficient 1 (normalized). // ES: Coeficiente del denominador 1 (normalizado).
    float a2{ 0.0f }; // EN: Denominator coefficient 2 (normalized). // ES: Coeficiente del denominador 2 (normalizado).

    // EN: User-configurable filter parameters.
    // ES: Parámetros configurables por el usuario del filtro.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz. // ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };          // EN: Quality factor (resonance). // ES: Factor de calidad (resonancia).
    float Gain{ 0.0f };         // EN: Gain in dB for the high-shelf filter. // ES: Ganancia en dB para el filtro de estantería alta.

    // EN: Gain adjustment factor for filter calculations.
    // ES: Factor de ajuste de ganancia para los cálculos del filtro.
    float A{ 0.0f };
};
