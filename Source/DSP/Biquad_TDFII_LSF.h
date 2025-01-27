/*
  ==============================================================================

    Biquad_TDFII_LSF.h
    Created: 7 Oct 2024 4:02:00pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class implementing a Biquad filter in Transposed Direct Form II for a Low Shelf Filter (LSF).
// ES: Clase que implementa un filtro Biquad en Forma Directa Transpuesta II para un Filtro de Estantería Baja (LSF).
class Biquad_TDFII_LSF
{
public:
    // EN: Constructor. Initializes the Low Shelf Filter instance.
    // ES: Constructor. Inicializa la instancia del filtro de estantería baja.
    Biquad_TDFII_LSF();

    // EN: Destructor. Cleans up any allocated resources.
    // ES: Destructor. Libera cualquier recurso asignado.
    ~Biquad_TDFII_LSF();

    // EN: Prepares the filter with the specified sample rate and updates the coefficients.
    // ES: Prepara el filtro con la frecuencia de muestreo especificada y actualiza los coeficientes.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer through the Low Shelf Filter.
    // ES: Procesa un buffer completo de audio a través del filtro de estantería baja.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample for a specific channel.
    // ES: Procesa una única muestra para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency of the filter.
    // ES: Establece la frecuencia de corte del filtro.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) of the filter.
    // ES: Establece el factor Q (resonancia) del filtro.
    void setQ(float inQ);

    // EN: Sets the gain of the Low Shelf Filter.
    // ES: Establece la ganancia del filtro de estantería baja.
    void setGain(float inGain);

    // EN: Updates the filter coefficients based on the current parameters.
    // ES: Actualiza los coeficientes del filtro basándose en los parámetros actuales.
    void updateFilter();

private:
    // EN: Sample rate of the audio being processed.
    // ES: Frecuencia de muestreo del audio que se procesa.
    double sampleRate{ 0.0f };

    // EN: Delay lines for the filter (two delay registers per channel).
    // ES: Líneas de retardo para el filtro (dos registros de retardo por canal).
    float r1[2] = { 0.0f };
    float r2[2] = { 0.0f };

    // EN: Intermediate variables for filter calculations.
    // ES: Variables intermedias para los cálculos del filtro.
    float w0{ 0.0f };    // EN: Angular frequency. / ES: Frecuencia angular.
    float alpha{ 0.0f }; // EN: Slope or bandwidth parameter. / ES: Parámetro de pendiente o ancho de banda.

    // EN: Filter coefficients for feedforward (b0, b1, b2) and feedback (a0, a1, a2).
    // ES: Coeficientes del filtro para avance (b0, b1, b2) y retroalimentación (a0, a1, a2).
    float b0{ 0.0f };
    float b1{ 0.0f };
    float b2{ 0.0f };
    float a0{ 0.0f };
    float a1{ 0.0f };
    float a2{ 0.0f };

    // EN: Parameters for the filter.
    // ES: Parámetros para el filtro.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz. / ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };          // EN: Quality factor (resonance). / ES: Factor de calidad (resonancia).
    float Gain{ 0.0f };         // EN: Gain in decibels. / ES: Ganancia en decibelios.
    float A{ 0.0f };            // EN: Linear amplitude derived from gain. / ES: Amplitud lineal derivada de la ganancia.
};

