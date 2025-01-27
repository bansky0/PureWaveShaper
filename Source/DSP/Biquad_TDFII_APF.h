/*
  ==============================================================================

    Biquad_TDFII_APF.h
    Created: 7 Oct 2024 3:59:49pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class implementing a Biquad All-Pass Filter using the Transposed Direct Form II structure.
// ES: Clase que implementa un filtro All-Pass Biquad utilizando la estructura de Forma Directa Transpuesta II.
class Biquad_TDFII_APF
{
public:
    // EN: Constructor for the Biquad_TDFII_APF class.
    // ES: Constructor de la clase Biquad_TDFII_APF.
    Biquad_TDFII_APF();

    // EN: Destructor for the Biquad_TDFII_APF class.
    // ES: Destructor de la clase Biquad_TDFII_APF.
    ~Biquad_TDFII_APF();

    // EN: Initializes the filter with the provided sample rate.
    // ES: Inicializa el filtro con la frecuencia de muestreo proporcionada.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer through the filter.
    // ES: Procesa un buffer completo de audio a través del filtro.
    void process(juce::AudioBuffer<float>& inBuffer);

    // EN: Processes a single audio sample for the specified channel.
    // ES: Procesa una única muestra de audio para el canal especificado.
    float processSample(float inSample, int channel);

    // EN: Sets the center frequency of the filter and updates its coefficients.
    // ES: Establece la frecuencia central del filtro y actualiza sus coeficientes.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) of the filter and updates its coefficients.
    // ES: Establece el factor Q (resonancia) del filtro y actualiza sus coeficientes.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current frequency and Q factor.
    // ES: Actualiza los coeficientes del filtro según la frecuencia y el factor Q actuales.
    void updateFilter();

private:
    // EN: The sample rate of the audio system.
    // ES: La frecuencia de muestreo del sistema de audio.
    double sampleRate{ 0.0f };

    // EN: Internal delay buffers for the filter (state variables).
    // ES: Buffers internos de retardo para el filtro (variables de estado).
    float r1[2] = { 0.0f }; // EN: Stores intermediate results for each channel.
                            // ES: Almacena resultados intermedios para cada canal.
    float r2[2] = { 0.0f }; // EN: Stores previous results for each channel.
                            // ES: Almacena resultados previos para cada canal.

// EN: Parameters for filter calculations.
// ES: Parámetros para los cálculos del filtro.
    float w0{ 0.0f };     // EN: Angular frequency.
                          // ES: Frecuencia angular.
    float alpha{ 0.0f };  // EN: Bandwidth-related parameter.
                          // ES: Parámetro relacionado con el ancho de banda.

// EN: Filter coefficients.
// ES: Coeficientes del filtro.
    float b0{ 0.0f }; // EN: Numerator coefficient (feedforward).
                      // ES: Coeficiente del numerador (realimentación directa).
    float b1{ 0.0f }; // EN: Numerator coefficient (feedforward).
                      // ES: Coeficiente del numerador (realimentación directa).
    float b2{ 0.0f }; // EN: Numerator coefficient (feedforward).
                      // ES: Coeficiente del numerador (realimentación directa).
    float a0{ 0.0f }; // EN: Denominator coefficient (feedback).
                      // ES: Coeficiente del denominador (retroalimentación).
    float a1{ 0.0f }; // EN: Denominator coefficient (feedback).
                      // ES: Coeficiente del denominador (retroalimentación).
    float a2{ 0.0f }; // EN: Denominator coefficient (feedback).
                      // ES: Coeficiente del denominador (retroalimentación).

// EN: Filter parameters set by the user.
// ES: Parámetros del filtro establecidos por el usuario.
    float frequency{ 1000.0f }; // EN: Center frequency in Hz.
                                // ES: Frecuencia central en Hz.
    float Q{ 0.707f };          // EN: Quality factor (controls resonance).
                                // ES: Factor de calidad (controla la resonancia).
};