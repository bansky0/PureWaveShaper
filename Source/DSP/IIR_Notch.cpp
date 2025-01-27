/*
  ==============================================================================

    IIR_Notch.cpp
    Created: 30 Sep 2024 6:27:34pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "IIR_Notch.h"

// EN: Constructor for the IIR_Notch class. Currently does not perform any additional initialization.
// ES: Constructor de la clase IIR_Notch. Actualmente no realiza ninguna inicialización adicional.
IIR_Notch::IIR_Notch()
{
}

// EN: Destructor for the IIR_Notch class. Automatically cleans up resources managed by JUCE.
// ES: Destructor de la clase IIR_Notch. Limpia automáticamente los recursos administrados por JUCE.
IIR_Notch::~IIR_Notch()
{
}

// EN: Prepares the filter for processing by specifying the sample rate, block size, and number of channels.
//     This method must be called before using the filter.
// ES: Prepara el filtro para el procesamiento especificando la frecuencia de muestreo, el tamaño del bloque y el número de canales.
//     Este método debe llamarse antes de usar el filtro.
void IIR_Notch::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;       // EN: Sets the sample rate for processing.
                                          // ES: Establece la frecuencia de muestreo para el procesamiento.
    spec.maximumBlockSize = inSamplesPerBlock; // EN: Sets the maximum block size for processing.
                                               // ES: Establece el tamaño máximo de bloque para el procesamiento.
    spec.numChannels = inChannels;       // EN: Specifies the number of audio channels.
                                         // ES: Especifica el número de canales de audio.

    sampleRate = inSampleRate; // EN: Stores the sample rate for use in filter calculations.
                               // ES: Almacena la frecuencia de muestreo para su uso en los cálculos del filtro.

// EN: Prepares the notch filter with the specified processing parameters.
// ES: Prepara el filtro notch con los parámetros de procesamiento especificados.
    notch.prepare(spec);

    // EN: Initializes the filter coefficients with the initial cutoff frequency.
    // ES: Inicializa los coeficientes del filtro con la frecuencia de corte inicial.
    updateFilter();
}

// EN: Processes the audio buffer by applying the notch filter.
//     Modifies the buffer in place with the filtered audio.
// ES: Procesa el búfer de audio aplicando el filtro notch.
//     Modifica el búfer directamente con el audio filtrado.
void IIR_Notch::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer); // EN: Wraps the audio buffer into an AudioBlock for DSP processing.
    // ES: Envuelve el búfer de audio en un AudioBlock para el procesamiento DSP.

    juce::dsp::ProcessContextReplacing<float> context(block); // EN: Creates a processing context for in-place processing.
    // ES: Crea un contexto de procesamiento para el procesamiento en el lugar.

    notch.process(context); // EN: Applies the notch filter to the audio block.
    // ES: Aplica el filtro notch al bloque de audio.
}

// EN: Sets the cutoff frequency of the notch filter.
//     Updates the filter coefficients to reflect the new cutoff frequency.
// ES: Establece la frecuencia de corte del filtro notch.
//     Actualiza los coeficientes del filtro para reflejar la nueva frecuencia de corte.
void IIR_Notch::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency; // EN: Updates the cutoff frequency parameter.
    // ES: Actualiza el parámetro de frecuencia de corte.
    updateFilter(); // EN: Recalculates the filter coefficients with the updated frequency.
    // ES: Recalcula los coeficientes del filtro con la frecuencia actualizada.
}

// EN: Updates the coefficients of the notch filter based on the current sample rate and cutoff frequency.
// ES: Actualiza los coeficientes del filtro notch según la frecuencia de muestreo y la frecuencia de corte actuales.
void IIR_Notch::updateFilter()
{
    // EN: Generates the notch filter coefficients using the specified sample rate and cutoff frequency.
    // ES: Genera los coeficientes del filtro notch utilizando la frecuencia de muestreo y la frecuencia de corte especificadas.
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeNotch(
        sampleRate,          // EN: The current sample rate of the audio system.
                             // ES: La frecuencia de muestreo actual del sistema de audio.
        cutoffFrequency);    // EN: The current cutoff frequency of the notch filter.
                             // ES: La frecuencia de corte actual del filtro notch.

// EN: Assigns the new coefficients to the notch filter state.
// ES: Asigna los nuevos coeficientes al estado del filtro notch.
    *notch.state = *coefficients;
}