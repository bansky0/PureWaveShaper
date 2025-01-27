/*
  ==============================================================================

    Biquad_II_APF.h
    Created: 7 Oct 2024 11:58:53am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class definition for a Biquad All-Pass Filter (APF) implemented in Direct Form II.
// ES: Definición de la clase para un filtro All-Pass (APF) Biquad implementado en Forma Directa II.
class Biquad_II_APF
{
public:
    // EN: Constructor - Initializes the All-Pass Filter.
    // ES: Constructor - Inicializa el filtro All-Pass.
    Biquad_II_APF();

    // EN: Destructor - Cleans up resources used by the filter.
    // ES: Destructor - Libera los recursos utilizados por el filtro.
    ~Biquad_II_APF();

    // EN: Prepares the filter by setting the sample rate and initializing the coefficients.
    // ES: Prepara el filtro configurando la frecuencia de muestreo e inicializando los coeficientes.
    void prepare(double inSampleRate);

    // EN: Processes an audio buffer, applying the All-Pass Filter to each channel and sample.
    // ES: Procesa un buffer de audio, aplicando el filtro All-Pass a cada canal y muestra.
    void process(juce::AudioBuffer<float>& inBuffer);

    // EN: Processes a single audio sample for a specific channel using the filter.
    // ES: Procesa una única muestra de audio para un canal específico utilizando el filtro.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency for the All-Pass Filter.
    // ES: Establece la frecuencia de corte para el filtro All-Pass.
    void setFrequency(float inFrequency);

    // EN: Sets the quality factor (Q) for the All-Pass Filter.
    // ES: Establece el factor de calidad (Q) para el filtro All-Pass.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current frequency and Q values.
    // ES: Actualiza los coeficientes del filtro según los valores actuales de frecuencia y Q.
    void updateFilter();

private:
    // EN: Sample rate for the filter's operation.
    // ES: Frecuencia de muestreo para el funcionamiento del filtro.
    double sampleRate{ 0.0f };

    // EN: Delay lines for storing intermediate filter states for each channel.
    // ES: Líneas de retardo para almacenar los estados intermedios del filtro para cada canal.
    float w1[2] = { 0.0f }; // First delay line.
    float w2[2] = { 0.0f }; // Second delay line.

    // EN: Intermediate variables for filter calculations.
    // ES: Variables intermedias para los cálculos del filtro.
    float w0{ 0.0f };    // Normalized angular frequency.
    float alpha{ 0.0f }; // Bandwidth scaling factor.

    // EN: Coefficients for the All-Pass Filter.
    // ES: Coeficientes para el filtro All-Pass.
    float b0{ 0.0f }; // Numerator coefficient b0.
    float b1{ 0.0f }; // Numerator coefficient b1.
    float b2{ 0.0f }; // Numerator coefficient b2.
    float a0{ 0.0f }; // Denominator coefficient a0.
    float a1{ 0.0f }; // Denominator coefficient a1.
    float a2{ 0.0f }; // Denominator coefficient a2.

    // EN: Parameters for configuring the filter.
    // ES: Parámetros para configurar el filtro.
    float frequency{ 1000.0f }; // Cutoff frequency in Hz.
    float Q{ 0.707f };          // Quality factor (Q).
};
