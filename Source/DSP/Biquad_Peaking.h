/*
  ==============================================================================

    Biquad_Peaking.h
    Created: 1 Oct 2024 12:25:55pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Class definition for a peaking EQ filter implemented as a biquad filter.
// ES: Definición de una clase para un filtro de ecualización peaking implementado como un filtro biquad.
class Biquad_Peaking
{
public:
    // EN: Constructor for the Biquad_Peaking class.
    // ES: Constructor de la clase Biquad_Peaking.
    Biquad_Peaking();

    // EN: Destructor for the Biquad_Peaking class.
    // ES: Destructor de la clase Biquad_Peaking.
    ~Biquad_Peaking();

    // EN: Prepares the filter with the specified sample rate.
    // ES: Prepara el filtro con la frecuencia de muestreo especificada.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer by applying the peaking filter.
    // ES: Procesa un buffer completo de audio aplicando el filtro peaking.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single audio sample for a specific channel.
    // ES: Procesa una única muestra de audio para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the center frequency of the peaking filter.
    // ES: Establece la frecuencia central del filtro peaking.
    void setFrequency(float inFrequency);

    // EN: Sets the gain (boost/cut) of the peaking filter in dB.
    // ES: Establece la ganancia (boost/cut) del filtro peaking en dB.
    void setGain(float inGain);

    // EN: Sets the Q factor (quality factor) of the peaking filter.
    // ES: Establece el factor Q (factor de calidad) del filtro peaking.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on current parameters.
    // ES: Actualiza los coeficientes del filtro según los parámetros actuales.
    void updateFilter();

private:
    // EN: The sample rate of the audio being processed.
    // ES: La frecuencia de muestreo del audio que se está procesando.
    double sampleRate{ 0.0f };

    // EN: Delay buffers for the filter input (x) and output (y) samples.
    // ES: Buffers de retardo para las muestras de entrada (x) y salida (y) del filtro.
    float x1[2] = { 0.0f }; // EN: Delayed input sample x[n-1].
                            // ES: Muestra de entrada retrasada x[n-1].
    float x2[2] = { 0.0f }; // EN: Delayed input sample x[n-2].
                            // ES: Muestra de entrada retrasada x[n-2].
    float y1[2] = { 0.0f }; // EN: Delayed output sample y[n-1].
                            // ES: Muestra de salida retrasada y[n-1].
    float y2[2] = { 0.0f }; // EN: Delayed output sample y[n-2].
                            // ES: Muestra de salida retrasada y[n-2].

// EN: Internal variables for calculating filter coefficients.
// ES: Variables internas para calcular los coeficientes del filtro.
    float w0{ 0.0f };       // EN: Angular frequency (2 * pi * f / sampleRate).
                            // ES: Frecuencia angular (2 * pi * f / sampleRate).
    float alpha{ 0.0f };    // EN: Bandwidth-related parameter.
                            // ES: Parámetro relacionado con el ancho de banda.

// EN: Coefficients for the filter's difference equation.
// ES: Coeficientes para la ecuación en diferencias del filtro.
    float b0{ 0.0f };       // EN: Feedforward coefficient b0.
                            // ES: Coeficiente de realimentación directa b0.
    float b1{ 0.0f };       // EN: Feedforward coefficient b1.
                            // ES: Coeficiente de realimentación directa b1.
    float b2{ 0.0f };       // EN: Feedforward coefficient b2.
                            // ES: Coeficiente de realimentación directa b2.
    float a0{ 0.0f };       // EN: Feedback coefficient a0.
                            // ES: Coeficiente de realimentación a0.
    float a1{ 0.0f };       // EN: Feedback coefficient a1.
                            // ES: Coeficiente de realimentación a1.
    float a2{ 0.0f };       // EN: Feedback coefficient a2.
                            // ES: Coeficiente de realimentación a2.

// EN: Parameters for configuring the peaking filter.
// ES: Parámetros para configurar el filtro peaking.
    float frequency{ 1000.0f }; // EN: Center frequency in Hz.
                                // ES: Frecuencia central en Hz.
    float Q{ 0.707f };          // EN: Q factor (quality factor).
                                // ES: Factor Q (factor de calidad).
    float Gain{ 0.0f };         // EN: Gain in dB for boost or cut.
                                // ES: Ganancia en dB para aumentar o reducir.
    float A{ 0.0f };            // EN: Linear amplitude derived from Gain.
                                // ES: Amplitud lineal derivada de la ganancia.
};