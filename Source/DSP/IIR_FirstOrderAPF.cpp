/*
  ==============================================================================

    IIR_FirstOrderAPF.cpp
    Created: 30 Sep 2024 12:55:31pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "IIR_FirstOrderAPF.h"

// EN: Constructor for the IIRFirstOrderAPF class, initializes the object.
// ES: Constructor para la clase IIRFirstOrderAPF, inicializa el objeto.
IIRFirstOrderAPF::IIRFirstOrderAPF()
{
}

// EN: Destructor for the IIRFirstOrderAPF class, cleans up resources when the object is destroyed.
// ES: Destructor para la clase IIRFirstOrderAPF, limpia los recursos cuando el objeto es destruido.
IIRFirstOrderAPF::~IIRFirstOrderAPF()
{
}

// EN: Prepares the filter with the given sample rate, block size, and number of channels.
//     This method sets up the filter state based on the provided specifications.
// ES: Prepara el filtro con la frecuencia de muestreo, el tamaño del bloque y el número de canales proporcionados.
//     Este método configura el estado del filtro según las especificaciones proporcionadas.
void IIRFirstOrderAPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;           // Set the sample rate for processing
    spec.maximumBlockSize = inSamplesPerBlock; // Set the block size for processing
    spec.numChannels = inChannels;            // Set the number of channels for processing

    sampleRate = inSampleRate; // Stores the sample rate for later use

    // EN: Prepares the filter for processing using the provided specifications.
    // ES: Prepara el filtro para el procesamiento utilizando las especificaciones proporcionadas.
    foApf.prepare(spec);

    updateFilter(); // Initializes the filter with the current cutoff frequency
}

// EN: Processes the audio buffer by applying the first-order all-pass filter.
//     The filter is applied in place, modifying the buffer directly.
// ES: Procesa el búfer de audio aplicando el filtro pasapaso de primer orden.
//     El filtro se aplica en el lugar, modificando directamente el búfer.
void IIRFirstOrderAPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer); // Wraps the audio buffer in an AudioBlock

    juce::dsp::ProcessContextReplacing<float> context(block); // Creates a context for processing the audio block

    // EN: Processes the audio block with the filter. The audio is replaced in place.
    // ES: Procesa el bloque de audio con el filtro. El audio se reemplaza en el lugar.
    foApf.process(context);
}

// EN: Sets the cutoff frequency of the filter and updates the filter coefficients accordingly.
//     This method is called when the cutoff frequency needs to be changed.
// ES: Establece la frecuencia de corte del filtro y actualiza los coeficientes del filtro en consecuencia.
//     Este método se llama cuando se necesita cambiar la frecuencia de corte.
void IIRFirstOrderAPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Updates the cutoff frequency
    updateFilter();  // Recalculates the filter coefficients with the new cutoff frequency
}

// EN: Updates the filter coefficients based on the current sample rate and cutoff frequency.
//     This method recalculates the filter state whenever the cutoff frequency is changed.
// ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo y la frecuencia de corte actuales.
//     Este método recalcula el estado del filtro cada vez que cambia la frecuencia de corte.
void IIRFirstOrderAPF::updateFilter()
{
    // EN: Creates the coefficients for the first-order all-pass filter.
    //     The filter is created with the specified sample rate and cutoff frequency.
    // ES: Crea los coeficientes para el filtro pasapaso de primer orden.
    //     El filtro se crea con la frecuencia de muestreo y la frecuencia de corte especificadas.
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeFirstOrderAllPass(
        sampleRate,     // Sample rate for the filter
        cutoffFrequency // Cutoff frequency for the filter
    );

    // EN: Assigns the created coefficients to the filter state.
    //     This ensures that the filter operates with the updated coefficients.
    // ES: Asigna los coeficientes creados al estado del filtro.
    //     Esto asegura que el filtro opere con los coeficientes actualizados.
    *foApf.state = *coefficients;
}