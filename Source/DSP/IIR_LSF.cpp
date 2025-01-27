/*
  ==============================================================================

    IIR_LSF.cpp
    Created: 30 Sep 2024 1:53:16pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "IIR_LSF.h"

// EN: Constructor of the IIR_LSF class. It initializes the filter object, but does not perform any specific setup.
//     Configuration happens in the `prepare` method.
// ES: Constructor de la clase IIR_LSF. Inicializa el objeto del filtro, pero no realiza ninguna configuración específica.
//     La configuración se realiza en el método `prepare`.
IIR_LSF::IIR_LSF()
{
}

// EN: Destructor of the IIR_LSF class. It cleans up resources when the object is destroyed.
//     No explicit resource management is required since DSP objects are managed by JUCE.
// ES: Destructor de la clase IIR_LSF. Libera los recursos cuando el objeto es destruido.
//     No se requiere una gestión explícita de recursos ya que los objetos DSP son gestionados por JUCE.
IIR_LSF::~IIR_LSF()
{
}

// EN: Prepares the low-shelf filter with the given sample rate, block size, and number of channels.
//     It sets up the DSP objects and stores the sample rate for later use in filter coefficient calculations.
// ES: Prepara el filtro de estante bajo con la frecuencia de muestreo, el tamaño del bloque y el número de canales proporcionados.
//     Configura los objetos DSP y almacena la frecuencia de muestreo para su uso posterior en el cálculo de los coeficientes del filtro.
void IIR_LSF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;  // Almacena la frecuencia de muestreo
    spec.maximumBlockSize = inSamplesPerBlock;  // Establece el tamaño máximo del bloque
    spec.numChannels = inChannels;  // Establece el número de canales

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // EN: Prepares the filter with the process specifications provided.
// ES: Prepara el filtro con las especificaciones del proceso proporcionadas.
    foApf.prepare(spec);

    updateFilter(); // EN: Initializes the filter with the initial cutoff frequency.
    // ES: Inicializa el filtro con la frecuencia de corte inicial.
}

// EN: Processes the audio buffer using the low-shelf filter. The buffer is modified in place by applying the filter.
// ES: Procesa el búfer de audio utilizando el filtro de estante bajo. El búfer se modifica en el lugar aplicando el filtro.
void IIR_LSF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);  // EN: Converts the buffer into an audio block for DSP processing.
    // ES: Convierte el búfer en un bloque de audio para el procesamiento DSP.

    juce::dsp::ProcessContextReplacing<float> context(block);  // EN: Creates a processing context to replace the audio data.
    // ES: Crea un contexto de procesamiento para reemplazar los datos de audio.

    foApf.process(context);  // EN: Applies the filter to the audio block using the context.
    // ES: Aplica el filtro al bloque de audio usando el contexto.
}

// EN: Sets the cutoff frequency for the low-shelf filter. This frequency determines where the filter starts affecting the signal.
//     The filter coefficients are recalculated after updating the cutoff frequency.
// ES: Establece la frecuencia de corte para el filtro de estante bajo. Esta frecuencia determina dónde comienza a afectar la señal el filtro.
//     Los coeficientes del filtro se recalculan después de actualizar la frecuencia de corte.
void IIR_LSF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // EN: Updates the cutoff frequency.
    // ES: Actualiza la frecuencia de corte.
    updateFilter();  // EN: Recalculates the filter coefficients with the new cutoff frequency.
    // ES: Recalcula los coeficientes del filtro con la nueva frecuencia de corte.
}

// EN: Sets the Q factor for the filter, which affects the bandwidth of the filter’s influence. A higher Q results in a narrower filter band.
//     After updating the Q, the filter coefficients are recalculated.
// ES: Establece el factor Q para el filtro, que afecta el ancho de banda de la influencia del filtro. Un valor Q más alto resulta en un rango de filtro más estrecho.
//     Después de actualizar el Q, los coeficientes del filtro se recalculan.
void IIR_LSF::setQ(float newQ)
{
    q = newQ;  // EN: Updates the Q value for the filter.
    // ES: Actualiza el valor Q para el filtro.
    updateFilter();  // EN: Recalculates the filter coefficients with the new Q.
    // ES: Recalcula los coeficientes del filtro con el nuevo Q.
}

// EN: Sets the gain for the low-shelf filter, determining how much the low frequencies are amplified or attenuated.
//     The filter coefficients are recalculated after setting the new gain.
// ES: Establece la ganancia para el filtro de estante bajo, determinando cuánto se amplifican o atenúan las frecuencias bajas.
//     Los coeficientes del filtro se recalculan después de establecer la nueva ganancia.
void IIR_LSF::setGain(float newGain)
{
    gain = newGain;  // EN: Updates the gain value for the filter.
    // ES: Actualiza el valor de ganancia para el filtro.
    updateFilter();  // EN: Recalculates the filter coefficients with the new gain.
    // ES: Recalcula los coeficientes del filtro con la nueva ganancia.
}

// EN: Updates the filter coefficients based on the current cutoff frequency, Q, and gain values.
//     This method recalculates the filter behavior by generating the appropriate coefficients.
// ES: Actualiza los coeficientes del filtro en función de la frecuencia de corte, el Q y la ganancia actuales.
//     Este método recalcula el comportamiento del filtro generando los coeficientes adecuados.
void IIR_LSF::updateFilter()
{
    // EN: Creates the filter coefficients for a low-shelf filter with the specified parameters.
    //     These coefficients define the filter’s frequency response.
    // ES: Crea los coeficientes del filtro para un filtro de estante bajo con los parámetros especificados.
    //     Estos coeficientes definen la respuesta en frecuencia del filtro.
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(
        sampleRate,      // EN: Sample rate used to calculate the coefficients.
        // ES: Frecuencia de muestreo utilizada para calcular los coeficientes.
        cutoffFrequency, // EN: Cutoff frequency where the filter starts to affect the signal.
        // ES: Frecuencia de corte donde el filtro comienza a afectar la señal.
        q,               // EN: Q factor that affects the filter bandwidth.
        // ES: Factor Q que afecta el ancho de banda del filtro.
        gain);           // EN: Gain to amplify or attenuate the low frequencies.
    // ES: Ganancia para amplificar o atenuar las frecuencias bajas.

// EN: Assigns the newly calculated coefficients to the filter.
//     This ensures the filter works with the updated parameters.
// ES: Asigna los coeficientes recién calculados al filtro.
//     Esto asegura que el filtro funcione con los parámetros actualizados.
    *foApf.state = *coefficients;
}