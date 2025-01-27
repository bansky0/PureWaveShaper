/*
  ==============================================================================

    IIR_FirstOrderLPF.cpp
    Created: 30 Sep 2024 11:08:21am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "IIR_FirstOrderLPF.h"

// EN: Constructor of the IIRFirstOrderLPF class. Initializes the object.
// ES: Constructor de la clase IIRFirstOrderLPF. Inicializa el objeto.
IIRFirstOrderLPF::IIRFirstOrderLPF()
{
}

// EN: Destructor of the IIRFirstOrderLPF class. Cleans up resources when the object is destroyed.
// ES: Destructor de la clase IIRFirstOrderLPF. Limpia los recursos cuando el objeto es destruido.
IIRFirstOrderLPF::~IIRFirstOrderLPF()
{
}

// EN: Prepares the filter with the given sample rate, block size, and number of channels.
//     This method sets up the filter state and prepares it for processing.
// ES: Prepara el filtro con la frecuencia de muestreo, el tamaño del bloque y el número de canales proporcionados.
//     Este método configura el estado del filtro y lo prepara para el procesamiento.
void IIRFirstOrderLPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;  // Establece la frecuencia de muestreo
    spec.maximumBlockSize = inSamplesPerBlock;  // Establece el tamaño máximo del bloque de muestras
    spec.numChannels = inChannels;  // Establece el número de canales

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // EN: Prepares the filter with the provided specifications for processing.
    //     Initializes the filter with the given process specification (sample rate, block size, channels).
    //     Then, the filter is updated with the initial cutoff frequency.
    // ES: Prepara el filtro con las especificaciones del proceso proporcionadas.
    //     Inicializa el filtro con la frecuencia de corte inicial.
    foLpf.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

// EN: Processes the audio buffer by applying the low-pass filter.
//     This method modifies the buffer in place with the filtered audio.
// ES: Procesa el búfer de audio aplicando el filtro pasa-bajos.
//     Este método modifica el búfer directamente con el audio filtrado.
void IIRFirstOrderLPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);  // Convierte el búfer en un bloque de audio

    juce::dsp::ProcessContextReplacing<float> context(block);  // Contexto para el procesamiento de audio

    foLpf.process(context);  // Aplica el filtro pasa-bajos al bloque de audio
}

// EN: Sets the cutoff frequency of the filter and recalculates the filter coefficients.
//     The filter will allow frequencies below this threshold and attenuate higher ones.
// ES: Establece la frecuencia de corte del filtro y recalcula los coeficientes del filtro.
//     El filtro permitirá las frecuencias por debajo de este umbral y atenuará las frecuencias más altas.
void IIRFirstOrderLPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

// EN: Updates the filter coefficients based on the current sample rate and cutoff frequency.
//     This method recalculates the filter coefficients whenever the cutoff frequency is changed.
//     The filter coefficients are then applied to the filter object.
// ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo y la frecuencia de corte actuales.
//     Este método recalcula los coeficientes del filtro cada vez que cambia la frecuencia de corte.
//     Luego, los coeficientes se asignan al filtro.
void IIRFirstOrderLPF::updateFilter()
{
    // EN: Creates the low-pass filter coefficients using the makeFirstOrderLowPass method.
    //     This method calculates the coefficients based on the sample rate and cutoff frequency.
    //     The filter is first-order, meaning it will attenuate frequencies above the cutoff.
    // ES: Crea los coeficientes del filtro pasa-bajos usando el método makeFirstOrderLowPass.
    //     Este método calcula los coeficientes en base a la frecuencia de muestreo y la frecuencia de corte.
    //     El filtro es de primer orden, lo que significa que atenuará las frecuencias por encima de la frecuencia de corte.
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(
        sampleRate,    // La frecuencia de muestreo utilizada para calcular los coeficientes
        cutoffFrequency);  // La frecuencia de corte utilizada para calcular los coeficientes

    // EN: Applies the computed filter coefficients to the filter state.
    //     This step ensures that the filter uses the updated coefficients when processing audio.
    // ES: Asigna los coeficientes calculados al estado del filtro.
    //     Este paso asegura que el filtro use los coeficientes actualizados cuando procese el audio.
    *foLpf.state = *coefficients;
}