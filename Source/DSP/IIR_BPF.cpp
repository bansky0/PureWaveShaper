/*
  ==============================================================================

    IIR_BPF.cpp
    Created: 30 Sep 2024 4:05:49pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "IIR_BPF.h"

// EN: Constructor for the IIR_BPF class.
// ES: Constructor para la clase IIR_BPF.
IIR_BPF::IIR_BPF()
{
}

// EN: Destructor for the IIR_BPF class.
// ES: Destructor para la clase IIR_BPF.
IIR_BPF::~IIR_BPF()
{
}

// EN: Prepares the band-pass filter for processing by setting the sample rate, block size, and channels.
//     It also initializes the filter coefficients.
// ES: Prepara el filtro pasabanda para el procesamiento configurando la frecuencia de muestreo, el tamaño del bloque y los canales.
//     También inicializa los coeficientes del filtro.
void IIR_BPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    // EN: Set up the specifications for the audio processing, including sample rate, block size, and number of channels.
    // ES: Configura las especificaciones para el procesamiento de audio, incluyendo la frecuencia de muestreo, el tamaño del bloque y el número de canales.
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // EN: Stores the sample rate for later use. / ES: Almacena la frecuencia de muestreo para su uso posterior.

    // EN: Prepares the filter with the process specifications. 
    // ES: Prepara el filtro con las especificaciones del proceso.
    bpf.prepare(spec);
    updateFilter(); // EN: Initializes the filter with the initial cutoff frequency. / ES: Inicializa el filtro con la frecuencia de corte inicial.
}

// EN: Processes the audio buffer using the band-pass filter, modifying the audio buffer in place.
// ES: Procesa el búfer de audio utilizando el filtro pasabanda, modificando el búfer de audio en el lugar.
void IIR_BPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer); // EN: Converts the audio buffer into an audio block for DSP processing. / ES: Convierte el búfer de audio en un bloque de audio para el procesamiento DSP.

    juce::dsp::ProcessContextReplacing<float> context(block); // EN: Prepares the context for the processing, allowing modification of the buffer. / ES: Prepara el contexto para el procesamiento, permitiendo la modificación del búfer.

    bpf.process(context); // EN: Processes the audio block through the band-pass filter. / ES: Procesa el bloque de audio a través del filtro pasabanda.
}

// EN: Updates the filter coefficients based on the cutoff frequency.
//     This method is called whenever the cutoff frequency is changed.
// ES: Actualiza los coeficientes del filtro según la frecuencia de corte.
//     Este método se llama siempre que se cambie la frecuencia de corte.
void IIR_BPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // EN: Updates the cutoff frequency value. / ES: Actualiza el valor de la frecuencia de corte.
    updateFilter();  // EN: Recalculates the filter coefficients based on the new cutoff frequency. / ES: Recalcula los coeficientes del filtro según la nueva frecuencia de corte.
}

// EN: Calculates the band-pass filter coefficients based on the sample rate and cutoff frequency.
//     This method is used to update the filter state when parameters change.
// ES: Calcula los coeficientes del filtro pasabanda según la frecuencia de muestreo y la frecuencia de corte.
//     Este método se utiliza para actualizar el estado del filtro cuando cambian los parámetros.
void IIR_BPF::updateFilter()
{
    // EN: Creates the band-pass filter coefficients with the given sample rate and cutoff frequency.
    // ES: Crea los coeficientes del filtro pasabanda con la frecuencia de muestreo y la frecuencia de corte dadas.
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(
        sampleRate,    // EN: The sample rate of the audio signal. / ES: La frecuencia de muestreo de la señal de audio.
        cutoffFrequency); // EN: The cutoff frequency for the band-pass filter. / ES: La frecuencia de corte para el filtro pasabanda.

    // EN: Assigns the calculated coefficients to the filter state. / ES: Asigna los coeficientes calculados al estado del filtro.
    *bpf.state = *coefficients;
}