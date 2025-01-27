/*
  ==============================================================================

    IIR_FirstOrderHPF.cpp
    Created: 30 Sep 2024 11:56:09am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "IIR_FirstOrderHPF.h"

// EN: Constructor of the IIRFirstOrderHPF class. Initializes the object.
    // ES: Constructor de la clase IIRFirstOrderHPF. Inicializa el objeto.
IIRFirstOrderHPF::IIRFirstOrderHPF()
{
}

// EN: Destructor of the IIRFirstOrderHPF class. Cleans up resources when the object is destroyed.
    // ES: Destructor de la clase IIRFirstOrderHPF. Limpia los recursos cuando el objeto es destruido.
IIRFirstOrderHPF::~IIRFirstOrderHPF()
{
}

// EN: Prepares the filter with the given sample rate, block size, and number of channels.
//     This method sets up the filter state based on the provided specifications and initializes it with the cutoff frequency.
// ES: Prepara el filtro con la frecuencia de muestreo, el tamaño del bloque y el número de canales proporcionados.
//     Este método configura el estado del filtro según las especificaciones proporcionadas e inicializa el filtro con la frecuencia de corte.
void IIRFirstOrderHPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;   // Sets the sample rate for the filter
    spec.maximumBlockSize = inSamplesPerBlock;  // Sets the block size for the filter
    spec.numChannels = inChannels;    // Sets the number of channels for the filter

    sampleRate = inSampleRate;  // Store the sample rate for later use

    // Prepares the filter with the process specifications
    foHpf.prepare(spec);

    // Initializes the filter with the current cutoff frequency
    updateFilter();
}

// EN: Processes the audio buffer by applying the first-order high-pass filter.
//     The filter modifies the buffer directly in place (no need for a separate output buffer).
// ES: Procesa el búfer de audio aplicando el filtro pasa-altos de primer orden.
//     El filtro modifica directamente el búfer en el lugar (no se necesita un búfer de salida separado).
void IIRFirstOrderHPF::process(juce::AudioBuffer<float>& buffer)
{
    // Converts the audio buffer to an audio block for DSP processing
    juce::dsp::AudioBlock<float> block(buffer);

    // Creates the context for processing (the buffer will be replaced with the processed audio)
    juce::dsp::ProcessContextReplacing<float> context(block);

    // Processes the audio block using the high-pass filter
    foHpf.process(context);
}

// EN: Sets a new cutoff frequency for the filter and updates the filter coefficients.
//     This method recalculates the filter coefficients with the new frequency.
// ES: Establece una nueva frecuencia de corte para el filtro y actualiza los coeficientes del filtro.
//     Este método recalcula los coeficientes del filtro con la nueva frecuencia.
void IIRFirstOrderHPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;   // Update the cutoff frequency
    updateFilter();  // Recalculate the filter coefficients with the new cutoff frequency
}

// EN: Updates the filter coefficients based on the current sample rate and cutoff frequency.
//     This method recalculates the filter state each time the cutoff frequency is changed.
// ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo y la frecuencia de corte actuales.
//     Este método recalcula el estado del filtro cada vez que cambia la frecuencia de corte.
void IIRFirstOrderHPF::updateFilter()
{
    // Generates the filter coefficients for a first-order high-pass filter
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(
        sampleRate,       // Sample rate for calculating the coefficients
        cutoffFrequency); // The current cutoff frequency of the filter

    // Assign the newly calculated coefficients to the filter
    *foHpf.state = *coefficients;
}