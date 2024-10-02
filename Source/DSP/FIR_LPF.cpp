/*
  ==============================================================================

    FIR_HPF.cpp
    Created: 27 Sep 2024 8:52:32am
    Author:  Jhonatan

  ==============================================================================
*/

#include "FIR_LPF.h"

FIR_LPF::FIR_LPF()
{
}

FIR_LPF::~FIR_LPF()
{
}

void FIR_LPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // Prepara el filtro con las especificaciones del proceso
    lowPassFilter.prepare(spec);
    lowPassFilter2.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

void FIR_LPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    // Verifica que el buffer tenga al menos 2 canales (estéreo)
    if (block.getNumChannels() > 1)
    {
        // Procesa solo el canal izquierdo (canal 0)
        auto channelBlock = block.getSingleChannelBlock(1); // Canal derecho es el índice 0

        // Aplica el filtro FIR solo al canal derecho
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        lowPassFilter.process(context);
    }
    if (block.getNumChannels() > 0)
    {
        // Procesa solo el canal derecho (canal 1)
        auto channelBlock = block.getSingleChannelBlock(0); // Canal derecho es el índice 1

        // Aplica el filtro FIR solo al canal derecho
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        lowPassFilter2.process(context);
    }
}

void FIR_LPF::setCutoffFrequency(float newCutoff)
{
    cutoffFrequency = newCutoff;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void FIR_LPF::updateFilter()
{
    // Crea los coeficientes del filtro FIR de paso bajo
    coefficients = juce::dsp::FilterDesign<float>::designFIRLowpassWindowMethod(
        cutoffFrequency,  // Frecuencia de corte variable
        sampleRate,       // Frecuencia de muestreo
        21,               // Número de coeficientes (orden del filtro) mayor presiosion valores altos pero mayor costo computacional.
        juce::dsp::WindowingFunction<float>::hamming);  // Función ventana

    // Asigna los coeficientes al filtro
    lowPassFilter.coefficients = coefficients;
    lowPassFilter2.coefficients = coefficients;
}