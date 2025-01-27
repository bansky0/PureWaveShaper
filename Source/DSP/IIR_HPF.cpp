/*
  ==============================================================================

    IIR_HPF.cpp
    Created: 29 Sep 2024 8:49:51pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "IIR_HPF.h"

// EN: Default constructor for the IIR_HPF class. 
//     Initializes the object without any specific configuration.
// ES: Constructor por defecto para la clase IIR_HPF. 
//     Inicializa el objeto sin ninguna configuración específica.
IIR_HPF::IIR_HPF()
{
}

// EN: Destructor for the IIR_HPF class. 
//     Responsible for cleaning up any resources when the object is destroyed.
// ES: Destructor para la clase IIR_HPF. 
//     Se encarga de liberar cualquier recurso cuando el objeto es destruido.
IIR_HPF::~IIR_HPF()
{
}

// EN: Prepares the high-pass filter with the given sample rate, block size, and number of channels.
//     This method sets up the filter to be ready for processing audio and initializes the filter with the provided specifications.
// ES: Prepara el filtro pasa-altos con la frecuencia de muestreo, el tamaño del bloque y el número de canales proporcionados.
//     Este método configura el filtro para estar listo para procesar audio e inicializa el filtro con las especificaciones proporcionadas.
void IIR_HPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;  // Almacena la frecuencia de muestreo
    spec.maximumBlockSize = inSamplesPerBlock;  // Establece el tamaño máximo del bloque de muestras
    spec.numChannels = inChannels;  // Establece el número de canales de audio

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo para su uso posterior

    // EN: Prepares the filter with the given process specifications.
    //     The filter is now ready to process audio.
    // ES: Prepara el filtro con las especificaciones del proceso dadas.
    //     El filtro ya está listo para procesar audio.
    hpf.prepare(spec);

    // EN: Initializes the filter with the initial cutoff frequency by updating the filter coefficients.
    // ES: Inicializa el filtro con la frecuencia de corte inicial actualizando los coeficientes del filtro.
    updateFilter();
}

// EN: Processes the provided audio buffer with the high-pass filter.
//     This method modifies the buffer in place by applying the filter to the audio data.
// ES: Procesa el búfer de audio proporcionado con el filtro pasa-altos.
//     Este método modifica el búfer directamente aplicando el filtro a los datos de audio.
void IIR_HPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);  // Convierte el búfer de audio en un bloque de audio para el procesamiento

    juce::dsp::ProcessContextReplacing<float> context(block);  // Crea un contexto de proceso para reemplazar el audio en el bloque

    // EN: Applies the high-pass filter to the audio block.
    //     The filter processes the audio data in place.
    // ES: Aplica el filtro pasa-altos al bloque de audio.
    //     El filtro procesa los datos de audio directamente en el lugar.
    hpf.process(context);
}

// EN: Sets the cutoff frequency for the high-pass filter.
//     This method updates the cutoff frequency and recalculates the filter coefficients with the new value.
// ES: Establece la frecuencia de corte para el filtro pasa-altos.
//     Este método actualiza la frecuencia de corte y recalcula los coeficientes del filtro con el nuevo valor.
void IIR_HPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes del filtro con la nueva frecuencia de corte
}

// EN: Updates the filter coefficients based on the current sample rate and cutoff frequency.
//     This method is used to recalculate the filter's behavior whenever the cutoff frequency is changed.
// ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo y la frecuencia de corte actuales.
//     Este método se utiliza para recalcular el comportamiento del filtro cada vez que cambia la frecuencia de corte.
void IIR_HPF::updateFilter()
{
    // EN: Creates the high-pass filter coefficients using the sample rate and cutoff frequency.
    //     The coefficients define the behavior of the filter based on the current parameters.
    // ES: Crea los coeficientes del filtro pasa-altos utilizando la frecuencia de muestreo y la frecuencia de corte.
    //     Los coeficientes definen el comportamiento del filtro según los parámetros actuales.
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(
        sampleRate,  // Frecuencia de muestreo
        cutoffFrequency);  // Frecuencia de corte

    // EN: Assigns the newly calculated coefficients to the filter.
    //     This updates the filter's state with the new filter coefficients.
    // ES: Asigna los coeficientes recién calculados al filtro.
    //     Esto actualiza el estado del filtro con los nuevos coeficientes.
    *hpf.state = *coefficients;
}
