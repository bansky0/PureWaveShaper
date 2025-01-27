/*
  ==============================================================================

    Biquad_TDFII_Peaking.h
    Created: 7 Oct 2024 4:02:59pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Class implementing a biquad peaking EQ filter using Transposed Direct Form II.
// ES: Clase que implementa un filtro biquad de ecualización de pico utilizando la Forma Directa Transpuesta II.
class Biquad_TDFII_Peaking
{
public:
    // EN: Constructor for the peaking EQ filter.
    // ES: Constructor para el filtro de ecualización de pico.
    Biquad_TDFII_Peaking();

    // EN: Destructor for the peaking EQ filter.
    // ES: Destructor para el filtro de ecualización de pico.
    ~Biquad_TDFII_Peaking();

    // EN: Prepares the filter by setting the sample rate and initializing parameters.
    // ES: Prepara el filtro configurando la frecuencia de muestreo e inicializando parámetros.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer through the filter.
    // ES: Procesa un buffer de audio completo a través del filtro.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample through the filter for a specific channel.
    // ES: Procesa una muestra única a través del filtro para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the center frequency of the filter.
    // ES: Configura la frecuencia central del filtro.
    void setFrequency(float inFrequency);

    // EN: Sets the gain (boost or cut) of the filter.
    // ES: Configura la ganancia (aumento o reducción) del filtro.
    void setGain(float inGain);

    // EN: Sets the Q factor (quality factor) of the filter.
    // ES: Configura el factor Q (factor de calidad) del filtro.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current parameters.
    // ES: Actualiza los coeficientes del filtro basándose en los parámetros actuales.
    void updateFilter();

private:
    // EN: Sample rate of the audio being processed.
    // ES: Frecuencia de muestreo del audio que se está procesando.
    double sampleRate{ 0.0f };

    // EN: Delay buffers for the filter (one for each channel).
    // ES: Buffers de retardo del filtro (uno para cada canal).
    float r1[2] = { 0.0f };
    float r2[2] = { 0.0f };

    // EN: Angular frequency (w0) and alpha values used in coefficient calculations.
    // ES: Frecuencia angular (w0) y valores alpha utilizados en el cálculo de los coeficientes.
    float w0{ 0.0f };
    float alpha{ 0.0f };

    // EN: Filter coefficients (b0, b1, b2, a0, a1, a2).
    // ES: Coeficientes del filtro (b0, b1, b2, a0, a1, a2).
    float b0{ 0.0f };
    float b1{ 0.0f };
    float b2{ 0.0f };
    float a0{ 0.0f };
    float a1{ 0.0f };
    float a2{ 0.0f };

    // EN: Current filter parameters: frequency, Q factor, gain, and amplitude scaling factor A.
    // ES: Parámetros actuales del filtro: frecuencia, factor Q, ganancia y factor de escala de amplitud A.
    float frequency{ 1000.0f }; // Default frequency set to 1 kHz.
    float Q{ 0.707f };          // Default Q factor set for a Butterworth response.
    float Gain{ 0.0f };         // Default gain set to 0 dB (no boost or cut).
    float A{ 0.0f };            // Amplitude scaling factor.
};
