/*
  ==============================================================================

    IIR_PeakFilter.cpp
    Created: 30 Sep 2024 6:28:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_PeakFilter.h"

// Constructor
// EN: Initializes the IIR_PeakF object. No special setup is required here.
// ES: Inicializa el objeto IIR_PeakF. No se requiere una configuración especial aquí.
IIR_PeakF::IIR_PeakF()
{
}

// Destructor
// EN: Cleans up resources when the object is destroyed. Nothing special is done here.
// ES: Libera los recursos cuando el objeto es destruido. No se realiza nada especial aquí.
IIR_PeakF::~IIR_PeakF()
{
}

// Prepares the filter for audio processing
// EN: Configures the filter with the given sample rate, block size, and number of channels. 
//     This method prepares the filter for audio processing and initializes the coefficients.
// ES: Configura el filtro con la frecuencia de muestreo, el tamaño de bloque y el número de canales proporcionados.
//     Este método prepara el filtro para el procesamiento de audio e inicializa los coeficientes.
void IIR_PeakF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // EN: Stores the sample rate. | ES: Almacena la frecuencia de muestreo.

    // EN: Prepares the filter processor with the specified process settings.
    // ES: Prepara el procesador del filtro con las configuraciones especificadas.
    notch.prepare(spec);

    updateFilter(); // EN: Initializes the filter coefficients. | ES: Inicializa los coeficientes del filtro.
}

// Processes an audio buffer
// EN: Applies the filter to the provided audio buffer. The processing is done in place.
// ES: Aplica el filtro al búfer de audio proporcionado. El procesamiento se realiza en el lugar.
void IIR_PeakF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer); // EN: Converts the buffer to a DSP audio block. | ES: Convierte el búfer en un bloque de audio DSP.

    juce::dsp::ProcessContextReplacing<float> context(block); // EN: Creates a processing context. | ES: Crea un contexto de procesamiento.

    notch.process(context); // EN: Processes the audio block with the peak filter. | ES: Procesa el bloque de audio con el filtro pico.
}

// Sets the cutoff frequency
// EN: Updates the cutoff frequency and recalculates the filter coefficients.
// ES: Actualiza la frecuencia de corte y recalcula los coeficientes del filtro.
void IIR_PeakF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // EN: Updates the internal cutoff frequency variable. | ES: Actualiza la variable interna de frecuencia de corte.
    updateFilter();  // EN: Recomputes the filter coefficients. | ES: Recalcula los coeficientes del filtro.
}

// Sets the Q factor
// EN: Updates the Q factor and recalculates the filter coefficients.
// ES: Actualiza el factor Q y recalcula los coeficientes del filtro.
void IIR_PeakF::setQ(float newQ)
{
    q = newQ; // EN: Updates the internal Q factor variable. | ES: Actualiza la variable interna del factor Q.
    updateFilter(); // EN: Recomputes the filter coefficients. | ES: Recalcula los coeficientes del filtro.
}

// Sets the gain
// EN: Updates the gain and recalculates the filter coefficients.
// ES: Actualiza la ganancia y recalcula los coeficientes del filtro.
void IIR_PeakF::setGain(float newGain)
{
    gain = newGain; // EN: Updates the internal gain variable. | ES: Actualiza la variable interna de ganancia.
    updateFilter(); // EN: Recomputes the filter coefficients. | ES: Recalcula los coeficientes del filtro.
}

// Updates the filter coefficients
// EN: Computes the filter coefficients based on the current parameters (sample rate, cutoff frequency, Q, and gain).
// ES: Calcula los coeficientes del filtro en función de los parámetros actuales (frecuencia de muestreo, frecuencia de corte, Q y ganancia).
void IIR_PeakF::updateFilter()
{
    // EN: Creates the coefficients for the peak filter using JUCE's factory method.
    // ES: Crea los coeficientes para el filtro pico usando el método de fábrica de JUCE.
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(
        sampleRate,
        cutoffFrequency, q, gain); // EN: Uses the sample rate, cutoff frequency, Q, and gain to calculate coefficients. 
    // ES: Usa la frecuencia de muestreo, la frecuencia de corte, Q y la ganancia para calcular los coeficientes.

// EN: Assigns the computed coefficients to the filter state.
// ES: Asigna los coeficientes calculados al estado del filtro.
    *notch.state = *coefficients;
}