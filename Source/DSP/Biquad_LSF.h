/*
  ==============================================================================

    Biquad_LSF.h
    Created: 1 Oct 2024 12:26:41pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Class for implementing a biquad low-shelving filter (LSF).
// ES: Clase para implementar un filtro biquad de tipo shelving bajo (LSF).
class Biquad_LSF
{
public:
    // EN: Constructor to initialize the filter instance.
    // ES: Constructor para inicializar la instancia del filtro.
    Biquad_LSF();

    // EN: Destructor to clean up resources.
    // ES: Destructor para limpiar los recursos.
    ~Biquad_LSF();

    // EN: Prepares the filter by setting the sample rate and updating coefficients.
    // ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes.
    void prepare(double inSampleRate);

    // EN: Processes an audio buffer by applying the filter to each sample in each channel.
    // ES: Procesa un buffer de audio aplicando el filtro a cada muestra en cada canal.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single audio sample for a specific channel.
    // ES: Procesa una muestra de audio individual para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency for the filter.
    // ES: Establece la frecuencia de corte para el filtro.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) for the filter.
    // ES: Establece el factor Q (resonancia) para el filtro.
    void setQ(float inQ);

    // EN: Sets the gain for the shelving filter.
    // ES: Establece la ganancia para el filtro shelving.
    void setGain(float inGain);

    // EN: Updates the filter coefficients based on the current frequency, Q, and gain.
    // ES: Actualiza los coeficientes del filtro según la frecuencia, Q y ganancia actuales.
    void updateFilter();

private:
    // EN: The sample rate of the audio system.
    // ES: La frecuencia de muestreo del sistema de audio.
    double sampleRate{ 0.0f };

    // EN: Delay line states for previous input and output samples for both channels.
    // ES: Estados de la línea de retardo para muestras de entrada y salida previas en ambos canales.
    float x1[2] = { 0.0f }; // EN: x[n-1]: previous input sample. 
                            // ES: x[n-1]: muestra de entrada previa.
    float x2[2] = { 0.0f }; // EN: x[n-2]: input sample two steps back.
                            // ES: x[n-2]: muestra de entrada dos pasos atrás.
    float y1[2] = { 0.0f }; // EN: y[n-1]: previous output sample.
                            // ES: y[n-1]: muestra de salida previa.
    float y2[2] = { 0.0f }; // EN: y[n-2]: output sample two steps back.
                            // ES: y[n-2]: muestra de salida dos pasos atrás.

// EN: Variables for filter calculation.
// ES: Variables para el cálculo del filtro.
    float w0{ 0.0f };       // EN: Angular frequency.
                            // ES: Frecuencia angular.
    float alpha{ 0.0f };    // EN: Bandwidth or damping factor.
                            // ES: Ancho de banda o factor de amortiguación.

// EN: Coefficients for the biquad filter.
// ES: Coeficientes del filtro biquad.
    float b0{ 0.0f };       // EN: Feedforward coefficient for the current input.
                            // ES: Coeficiente directo para la entrada actual.
    float b1{ 0.0f };       // EN: Feedforward coefficient for the previous input.
                            // ES: Coeficiente directo para la entrada previa.
    float b2{ 0.0f };       // EN: Feedforward coefficient for the input two steps back.
                            // ES: Coeficiente directo para la entrada dos pasos atrás.
    float a0{ 0.0f };       // EN: Normalization factor.
                            // ES: Factor de normalización.
    float a1{ 0.0f };       // EN: Feedback coefficient for the previous output.
                            // ES: Coeficiente de realimentación para la salida previa.
    float a2{ 0.0f };       // EN: Feedback coefficient for the output two steps back.
                            // ES: Coeficiente de realimentación para la salida dos pasos atrás.

// EN: Filter parameters.
// ES: Parámetros del filtro.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz.
                                // ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };          // EN: Quality factor (resonance).
                                // ES: Factor de calidad (resonancia).
    float Gain{ 0.0f };         // EN: Gain in dB for the shelving filter.
                                // ES: Ganancia en dB para el filtro shelving.
    float A{ 0.0f };            // EN: Linear gain value derived from the dB gain.
                                // ES: Valor de ganancia lineal derivado de la ganancia en dB.
};
