/*
  ==============================================================================

    FIR_HPF.cpp
    Created: 27 Sep 2024 8:52:32am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "FIR_LPF.h"

// EN: Constructor of FIR_LPF class. It initializes the filter with default values.
// ES: Constructor de la clase FIR_LPF. Inicializa el filtro con valores predeterminados.
FIR_LPF::FIR_LPF()
{
}

// EN: Destructor of FIR_LPF class. Cleans up any resources when the filter is no longer needed.
// ES: Destructor de la clase FIR_LPF. Limpia los recursos cuando el filtro ya no es necesario.
FIR_LPF::~FIR_LPF()
{
}

// EN: Prepares the filter by setting up the sample rate, block size, and number of channels.
//     This is done before processing the audio data to set up the necessary configurations.
// ES: Prepara el filtro configurando la tasa de muestreo, el tamaño del bloque y el número de canales.
//     Esto se realiza antes de procesar los datos de audio para configurar las configuraciones necesarias.
void FIR_LPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate; // Configura la frecuencia de muestreo del filtro
    spec.maximumBlockSize = inSamplesPerBlock; // Configura el tamaño máximo del bloque
    spec.numChannels = inChannels; // Configura el número de canales (mono, estéreo, etc.)

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo para su uso en otras partes del filtro

    // Prepara el filtro con las especificaciones del proceso
    lowPassFilter.prepare(spec); // Prepara el filtro FIR para el canal izquierdo
    lowPassFilter2.prepare(spec); // Prepara otro filtro FIR para el canal derecho
    updateFilter(); // Llama al método para inicializar los coeficientes del filtro con la frecuencia de corte inicial
}

// EN: Processes the audio buffer by applying the low-pass filter to each channel (left and right separately).
//     It processes the left and right channels independently.
// ES: Procesa el buffer de audio aplicando el filtro de paso bajo a cada canal (izquierdo y derecho por separado).
//     Procesa los canales izquierdo y derecho de manera independiente.
void FIR_LPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer); // Convierte el buffer de audio en un bloque para procesamiento más eficiente

    // EN: If the buffer has more than 1 channel (stereo), process the right channel (channel 0).
    // ES: Si el buffer tiene más de 1 canal (estéreo), procesa el canal derecho (canal 0).
    if (block.getNumChannels() > 1)
    {
        // Process the right channel (channel 1)
        auto channelBlock = block.getSingleChannelBlock(1); // Canal derecho, índice 1

        // Applies the FIR low-pass filter to the right channel
        juce::dsp::ProcessContextReplacing<float> context(channelBlock); // Crea un contexto para el procesamiento
        lowPassFilter.process(context); // Aplica el filtro FIR
    }

    // EN: If the buffer has at least 1 channel, process the left channel (channel 1).
    // ES: Si el buffer tiene al menos 1 canal, procesa el canal izquierdo (canal 1).
    if (block.getNumChannels() > 0)
    {
        // Process the left channel (channel 0)
        auto channelBlock = block.getSingleChannelBlock(0); // Canal izquierdo, índice 0

        // Applies the FIR low-pass filter to the left channel
        juce::dsp::ProcessContextReplacing<float> context(channelBlock); // Crea un contexto para el procesamiento
        lowPassFilter2.process(context); // Aplica el filtro FIR
    }
}

// EN: Updates the cutoff frequency of the low-pass filter and recalculates the filter coefficients.
//     The updateFilter method is called to design a new set of filter coefficients based on the new cutoff frequency.
// ES: Actualiza la frecuencia de corte del filtro de paso bajo y recalcula los coeficientes del filtro.
//     Se llama al método updateFilter para diseñar un nuevo conjunto de coeficientes del filtro según la nueva frecuencia de corte.
void FIR_LPF::setCutoffFrequency(float newCutoff)
{
    cutoffFrequency = newCutoff;  // Actualiza la frecuencia de corte con el nuevo valor
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia de corte
}

// EN: Recalculates the filter coefficients based on the current cutoff frequency and sample rate.
//     It uses the windowing method to design the FIR low-pass filter.
// ES: Recalcula los coeficientes del filtro según la frecuencia de corte actual y la tasa de muestreo.
//     Utiliza el método de ventana para diseñar el filtro FIR de paso bajo.
void FIR_LPF::updateFilter()
{
    // Designs the FIR low-pass filter coefficients using the window method.
    coefficients = juce::dsp::FilterDesign<float>::designFIRLowpassWindowMethod(
        cutoffFrequency,  // Frecuencia de corte del filtro, que puede cambiar dinámicamente
        sampleRate,       // Frecuencia de muestreo para el diseño del filtro
        21,               // Número de coeficientes del filtro (determina el orden del filtro)
        juce::dsp::WindowingFunction<float>::hamming);  // Función ventana Hamming para suavizar la respuesta del filtro

    // Sets the newly calculated coefficients to both FIR filters for left and right channels
    lowPassFilter.coefficients = coefficients;  // Asigna los coeficientes al filtro del canal izquierdo
    lowPassFilter2.coefficients = coefficients; // Asigna los coeficientes al filtro del canal derecho
}
