/*
  ==============================================================================

    Biquad_II_HPF.h
    Created: 7 Oct 2024 11:58:20am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class declaration for a High-Pass Filter (HPF) using the Direct Form II structure.
// ES: Declaración de clase para un filtro pasa altos (HPF) utilizando la estructura de Forma Directa II.
class Biquad_II_HPF
{
public:
    // EN: Constructor - Initializes the filter with default values.
    // ES: Constructor - Inicializa el filtro con valores predeterminados.
    Biquad_II_HPF();

    // EN: Destructor - Cleans up any allocated resources.
    // ES: Destructor - Libera cualquier recurso asignado.
    ~Biquad_II_HPF();

    // EN: Prepares the filter by setting the sample rate and updating the coefficients.
    // ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes.
    void prepare(double inSampleRate);

    // EN: Processes an audio buffer, applying the high-pass filter to all samples and channels.
    // ES: Procesa un buffer de audio, aplicando el filtro pasa altos a todas las muestras y canales.
    void process(juce::AudioBuffer<float>& inBuffer);

    // EN: Processes a single sample for a specific channel.
    // ES: Procesa una única muestra para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency of the high-pass filter and updates the coefficients.
    // ES: Establece la frecuencia de corte del filtro pasa altos y actualiza los coeficientes.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) of the high-pass filter and updates the coefficients.
    // ES: Establece el factor Q (resonancia) del filtro pasa altos y actualiza los coeficientes.
    void setQ(float inQ);

    // EN: Recalculates the filter coefficients based on the current frequency, Q factor, and sample rate.
    // ES: Recalcula los coeficientes del filtro según la frecuencia, el factor Q y la frecuencia de muestreo actuales.
    void updateFilter();

private:
    // EN: The sample rate of the audio signal.
    // ES: La frecuencia de muestreo de la señal de audio.
    double sampleRate{ 0.0f };

    // EN: Delay lines for the Direct Form II filter structure.
    // ES: Líneas de retardo para la estructura del filtro en Forma Directa II.
    float w1[2] = { 0.0f }; // EN: One per channel. // ES: Una por canal.
    float w2[2] = { 0.0f };

    // EN: Filter coefficients and intermediate values.
    // ES: Coeficientes del filtro y valores intermedios.
    float w0{ 0.0f };    // EN: Angular frequency. // ES: Frecuencia angular.
    float alpha{ 0.0f }; // EN: Bandwidth scaling factor. // ES: Factor de escalado de ancho de banda.

    float b0{ 0.0f }; // EN: Numerator coefficient 0. // ES: Coeficiente del numerador 0.
    float b1{ 0.0f }; // EN: Numerator coefficient 1. // ES: Coeficiente del numerador 1.
    float b2{ 0.0f }; // EN: Numerator coefficient 2. // ES: Coeficiente del numerador 2.
    float a0{ 0.0f }; // EN: Denominator coefficient 0. // ES: Coeficiente del denominador 0.
    float a1{ 0.0f }; // EN: Denominator coefficient 1. // ES: Coeficiente del denominador 1.
    float a2{ 0.0f }; // EN: Denominator coefficient 2. // ES: Coeficiente del denominador 2.

    // EN: Filter parameters set by the user.
    // ES: Parámetros del filtro configurados por el usuario.
    float frequency{ 1000.0f }; // EN: Default cutoff frequency. // ES: Frecuencia de corte predeterminada.
    float Q{ 0.707f };         // EN: Default Q factor (resonance). // ES: Factor Q predeterminado (resonancia).
};