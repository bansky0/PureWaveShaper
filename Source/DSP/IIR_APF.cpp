/*
  ==============================================================================

    IIR_APF.cpp
    Created: 30 Sep 2024 1:14:09pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "IIR_APF.h"

// EN: Constructor for the IIR_APF class.
// ES: Constructor para la clase IIR_APF.
IIR_APF::IIR_APF()
{
}

// EN: Destructor for the IIR_APF class.
// ES: Destructor para la clase IIR_APF.
IIR_APF::~IIR_APF()
{
}

// EN: Prepares the filter for audio processing. Sets the sample rate, maximum block size, and number of channels.
// ES: Prepara el filtro para el procesamiento de audio. Establece la frecuencia de muestreo, el tamaño máximo de bloque y el número de canales.
void IIR_APF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    // EN: Set up the processing specifications.
    // ES: Configura las especificaciones del procesamiento.
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    // EN: Store the sample rate for use in filter calculations.
    // ES: Almacena la frecuencia de muestreo para usarla en los cálculos del filtro.
    sampleRate = inSampleRate;

    // EN: Prepare the all-pass filter with the processing specifications.
    // ES: Prepara el filtro de fase total con las especificaciones de procesamiento.
    foApf.prepare(spec);

    // EN: Initialize the filter with the initial cutoff frequency.
    // ES: Inicializa el filtro con la frecuencia de corte inicial.
    updateFilter();
}

// EN: Processes the audio buffer through the all-pass filter.
// ES: Procesa el búfer de audio a través del filtro de fase total.
void IIR_APF::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Convert the audio buffer into a JUCE audio block for processing.
    // ES: Convierte el búfer de audio en un bloque de audio de JUCE para procesarlo.
    juce::dsp::AudioBlock<float> block(buffer);

    // EN: Create a processing context for replacing the buffer contents with the filter's output.
    // ES: Crea un contexto de procesamiento para reemplazar el contenido del búfer con la salida del filtro.
    juce::dsp::ProcessContextReplacing<float> context(block);

    // EN: Process the audio block through the all-pass filter.
    // ES: Procesa el bloque de audio a través del filtro de fase total.
    foApf.process(context);
}

// EN: Sets the cutoff frequency of the filter and updates the coefficients accordingly.
// ES: Establece la frecuencia de corte del filtro y actualiza los coeficientes en consecuencia.
void IIR_APF::setCutoffFrequency(float frequency)
{
    // EN: Store the new cutoff frequency.
    // ES: Almacena la nueva frecuencia de corte.
    cutoffFrequency = frequency;

    // EN: Update the filter coefficients to match the new cutoff frequency.
    // ES: Actualiza los coeficientes del filtro para que coincidan con la nueva frecuencia de corte.
    updateFilter();
}

// EN: Updates the coefficients of the all-pass filter based on the current sample rate and cutoff frequency.
// ES: Actualiza los coeficientes del filtro de fase total en función de la frecuencia de muestreo y la frecuencia de corte actuales.
void IIR_APF::updateFilter()
{
    // EN: Generate new coefficients for the all-pass filter.
    // ES: Genera nuevos coeficientes para el filtro de fase total.
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(
        sampleRate,      // EN: Sample rate of the audio. | ES: Frecuencia de muestreo del audio.
        cutoffFrequency  // EN: Current cutoff frequency. | ES: Frecuencia de corte actual.
    );

    // EN: Assign the new coefficients to the filter state.
    // ES: Asigna los nuevos coeficientes al estado del filtro.
    *foApf.state = *coefficients;
}