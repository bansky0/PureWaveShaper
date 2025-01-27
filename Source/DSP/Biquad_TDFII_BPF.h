/*
  ==============================================================================

    Biquad_TDFII_BPF.h
    Created: 7 Oct 2024 4:01:29pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class for a Band-Pass Filter (BPF) implemented using Transposed Direct Form II.
// ES: Clase para un filtro pasa banda (BPF) implementado utilizando la forma directa transpuesta II.
class Biquad_TDFII_BPF
{
public:
    // EN: Constructor for the Biquad_TDFII_BPF class.
    // ES: Constructor de la clase Biquad_TDFII_BPF.
    Biquad_TDFII_BPF();

    // EN: Destructor for the Biquad_TDFII_BPF class.
    // ES: Destructor de la clase Biquad_TDFII_BPF.
    ~Biquad_TDFII_BPF();

    // EN: Prepares the filter by initializing the sample rate and updating coefficients.
    // ES: Prepara el filtro inicializando la frecuencia de muestreo y actualizando los coeficientes.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer, applying the band-pass filter.
    // ES: Procesa un buffer de audio completo, aplicando el filtro pasa banda.
    void process(juce::AudioBuffer<float>& inBuffer);

    // EN: Processes a single sample for a specific channel.
    // ES: Procesa una muestra individual para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the center frequency of the band-pass filter.
    // ES: Establece la frecuencia central del filtro pasa banda.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) of the band-pass filter.
    // ES: Establece el factor Q (resonancia) del filtro pasa banda.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current settings.
    // ES: Actualiza los coeficientes del filtro según la configuración actual.
    void updateFilter();

private:
    // EN: The sample rate of the audio signal.
    // ES: La frecuencia de muestreo de la señal de audio.
    double sampleRate{ 0.0f };

    // EN: Internal state variables for the filter (delay elements for the feedback path).
    // ES: Variables internas de estado del filtro (elementos de retardo para la retroalimentación).
    float r1[2] = { 0.0f }; // EN: First delay element for each channel.
                            // ES: Primer elemento de retardo para cada canal.
    float r2[2] = { 0.0f }; // EN: Second delay element for each channel.
                            // ES: Segundo elemento de retardo para cada canal.

// EN: Filter parameters.
// ES: Parámetros del filtro.
    float w0{ 0.0f };    // EN: Angular frequency of the center frequency.
                         // ES: Frecuencia angular de la frecuencia central.
    float alpha{ 0.0f }; // EN: Bandwidth parameter based on Q.
                         // ES: Parámetro de ancho de banda basado en Q.

// EN: Coefficients for the filter equation.
// ES: Coeficientes para la ecuación del filtro.
    float b0{ 0.0f }; // EN: Feedforward coefficient b0.
                      // ES: Coeficiente de avance b0.
    float b1{ 0.0f }; // EN: Feedforward coefficient b1.
                      // ES: Coeficiente de avance b1.
    float b2{ 0.0f }; // EN: Feedforward coefficient b2.
                      // ES: Coeficiente de avance b2.
    float a0{ 0.0f }; // EN: Feedback coefficient a0 (normalization factor).
                      // ES: Coeficiente de retroalimentación a0 (factor de normalización).
    float a1{ 0.0f }; // EN: Feedback coefficient a1.
                      // ES: Coeficiente de retroalimentación a1.
    float a2{ 0.0f }; // EN: Feedback coefficient a2.
                      // ES: Coeficiente de retroalimentación a2.

// EN: User-defined filter settings.
// ES: Configuración del filtro definida por el usuario.
    float frequency{ 1000.0f }; // EN: Center frequency of the filter in Hz.
                                // ES: Frecuencia central del filtro en Hz.
    float Q{ 0.707f };          // EN: Quality factor controlling the bandwidth of the filter.
                                // ES: Factor de calidad que controla el ancho de banda del filtro.
};