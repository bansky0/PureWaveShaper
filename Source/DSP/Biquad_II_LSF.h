/*
  ==============================================================================

    Biquad_II_LSF.h
    Created: 7 Oct 2024 11:59:16am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Biquad_II_LSF
{
public:
    // EN: Constructor - No additional initialization is required as all members are initialized in the class definition.
    // ES: Constructor - No se requiere inicialización adicional ya que todos los miembros se inicializan en la definición de la clase.
    Biquad_II_LSF();

    // EN: Destructor - Cleans up any resources allocated by the class.
    // ES: Destructor - Limpia cualquier recurso asignado por la clase.
    ~Biquad_II_LSF();

    // EN: Prepares the filter with the given sample rate.
    // ES: Prepara el filtro con la frecuencia de muestreo dada.
    void prepare(double inSampleRate);

    // EN: Processes the entire audio buffer, applying the filter to each sample.
    // ES: Procesa el buffer de audio completo, aplicando el filtro a cada muestra.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample of audio for the specified channel.
    // ES: Procesa una sola muestra de audio para el canal especificado.
    float processSample(float inSample, int channel);

    // EN: Sets the frequency of the filter and updates the filter coefficients.
    // ES: Establece la frecuencia del filtro y actualiza los coeficientes del filtro.
    void setFrequency(float inFrequency);

    // EN: Sets the quality factor (Q) of the filter and updates the filter coefficients.
    // ES: Establece el factor de calidad (Q) del filtro y actualiza los coeficientes del filtro.
    void setQ(float inQ);

    // EN: Sets the gain for the filter and updates the filter coefficients.
    // ES: Establece la ganancia del filtro y actualiza los coeficientes del filtro.
    void setGain(float inGain);

    // EN: Updates the filter coefficients based on the current frequency, Q, and gain.
    // ES: Actualiza los coeficientes del filtro según la frecuencia, Q y ganancia actuales.
    void updateFilter();

private:
    // EN: Stores the sample rate of the audio being processed.
    // ES: Almacena la frecuencia de muestreo del audio que se está procesando.
    double sampleRate{ 0.0f };

    // EN: State variables for the filter, used for storing delayed values.
    // ES: Variables de estado para el filtro, utilizadas para almacenar valores retardados.
    float w1[2] = { 0.0f };
    float w2[2] = { 0.0f };

    // EN: The angular frequency of the filter.
    // ES: La frecuencia angular del filtro.
    float w0{ 0.0f };

    // EN: The alpha parameter used to calculate filter coefficients.
    // ES: El parámetro alpha utilizado para calcular los coeficientes del filtro.
    float alpha{ 0.0f };

    // EN: Filter coefficients for the Biquad filter.
    // ES: Coeficientes del filtro Biquad.
    float b0{ 0.0f };
    float b1{ 0.0f };
    float b2{ 0.0f };
    float a0{ 0.0f };
    float a1{ 0.0f };
    float a2{ 0.0f };

    // EN: Frequency, Q, and gain parameters for the filter.
    // ES: Parámetros de frecuencia, Q y ganancia para el filtro.
    float frequency{ 1000.0f };
    float Q{ 0.707f };
    float Gain{ 0.0f };

    // EN: The 'A' value used for gain adjustments in the filter.
    // ES: El valor 'A' utilizado para los ajustes de ganancia en el filtro.
    float A{ 0.0f };
};
