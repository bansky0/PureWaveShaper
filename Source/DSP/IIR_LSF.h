/*
  ==============================================================================

    IIR_LSF.h
    Created: 30 Sep 2024 1:53:16pm
    Author:  Jhonatan López

    notes: values for Q 0.1f, 2.0f, 0.707f. Values for gain 0.1f, 3.0f, 1.0f +6db aprox.
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Declaration of the IIR_LSF class, which represents an IIR Low Shelf Filter.
//     This filter adjusts the gain of low frequencies while leaving the high frequencies unaffected or with less effect.
// ES: Declaración de la clase IIR_LSF, que representa un filtro de estante bajo IIR.
//     Este filtro ajusta la ganancia de las frecuencias bajas mientras deja las frecuencias altas inalteradas o con menos efecto.
class IIR_LSF
{
public:
    // EN: Constructor of the IIR_LSF class. Initializes the filter object.
    //     Does not perform any actual filter setup. Configuration happens in `prepare`.
    // ES: Constructor de la clase IIR_LSF. Inicializa el objeto del filtro.
    //     No realiza ninguna configuración real del filtro. La configuración se realiza en `prepare`.
    IIR_LSF();

    // EN: Destructor of the IIR_LSF class. Cleans up the resources when the object is destroyed.
    //     No explicit resource management is needed as the DSP objects are managed by JUCE.
    // ES: Destructor de la clase IIR_LSF. Libera los recursos cuando el objeto es destruido.
    //     No se necesita una gestión explícita de recursos ya que los objetos DSP son gestionados por JUCE.
    ~IIR_LSF();

    // EN: Prepares the low-shelf filter with the sample rate, block size, and number of channels.
    //     This function is called once before processing the audio and sets up the necessary DSP objects.
    //     It also stores the sample rate for later use in filter coefficient calculation.
    // ES: Prepara el filtro de estante bajo con la frecuencia de muestreo, el tamaño del bloque y el número de canales.
    //     Esta función se llama una vez antes de procesar el audio y configura los objetos DSP necesarios.
    //     También almacena la frecuencia de muestreo para su uso posterior en el cálculo de los coeficientes del filtro.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer using the low-shelf filter.
    //     This modifies the audio buffer in place by applying the filter to it.
    // ES: Procesa el búfer de audio utilizando el filtro de estante bajo.
    //     Esto modifica el búfer de audio aplicando el filtro sobre él.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency for the low-shelf filter.
    //     The cutoff frequency determines the point at which the filter starts affecting the audio signal.
    //     After setting the new cutoff, the filter coefficients are updated.
    // ES: Establece la frecuencia de corte para el filtro de estante bajo.
    //     La frecuencia de corte determina el punto en el que el filtro comienza a afectar la señal de audio.
    //     Después de establecer la nueva frecuencia de corte, los coeficientes del filtro se actualizan.
    void setCutoffFrequency(float newCutoff);

    // EN: Sets the Q factor (quality factor) for the filter, affecting the bandwidth of the filter.
    //     A higher Q value results in a narrower filter band, and a lower Q results in a wider filter band.
    //     After setting the new Q, the filter coefficients are recalculated.
    // ES: Establece el factor Q (factor de calidad) para el filtro, afectando el ancho de banda del filtro.
    //     Un valor Q más alto da como resultado un rango de filtro más estrecho, y un Q más bajo da como resultado un rango de filtro más amplio.
    //     Después de establecer el nuevo Q, los coeficientes del filtro se recalculan.
    void setQ(float newQ);

    // EN: Sets the gain of the low-shelf filter.
    //     The gain affects how much the low frequencies will be amplified or attenuated.
    //     After setting the new gain, the filter coefficients are updated.
    // ES: Establece la ganancia del filtro de estante bajo.
    //     La ganancia afecta cuánto se amplificarán o atenuarán las frecuencias bajas.
    //     Después de establecer la nueva ganancia, los coeficientes del filtro se actualizan.
    void setGain(float newGain);

private:
    // EN: Updates the filter coefficients based on the current settings of cutoff frequency, Q, and gain.
    //     This method recalculates the filter's behavior by generating the appropriate coefficients.
    // ES: Actualiza los coeficientes del filtro en función de los ajustes actuales de la frecuencia de corte, Q y ganancia.
    //     Este método recalcula el comportamiento del filtro generando los coeficientes adecuados.
    void updateFilter();

    // EN: A DSP processor object that handles the actual filtering process.
    //     It is a duplicator that uses an IIR filter and its coefficients to apply the filter to the audio buffer.
    // ES: Un objeto de procesador DSP que maneja el proceso de filtrado real.
    //     Es un duplicador que utiliza un filtro IIR y sus coeficientes para aplicar el filtro al búfer de audio.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foApf;

    // EN: Stores the sample rate used for filter calculations.
    // ES: Almacena la frecuencia de muestreo utilizada para los cálculos del filtro.
    double sampleRate{};

    // EN: Stores the cutoff frequency for the filter. This is the frequency at which the filter starts affecting the audio.
    // ES: Almacena la frecuencia de corte para el filtro. Esta es la frecuencia a partir de la cual el filtro comienza a afectar el audio.
    float cutoffFrequency{};

    // EN: Stores the quality factor (Q) for the filter. It affects the bandwidth of the filter's influence.
    // ES: Almacena el factor de calidad (Q) para el filtro. Afecta el ancho de banda de la influencia del filtro.
    float q{};

    // EN: Stores the gain for the filter. This is how much the filter will amplify or attenuate low frequencies.
    // ES: Almacena la ganancia para el filtro. Esta es la cantidad que el filtro amplificará o atenuará las frecuencias bajas.
    float gain{};
};