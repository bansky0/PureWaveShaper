/*
  ==============================================================================

    FIR_LPF2.cpp
    Created: 28 Sep 2024 9:39:51pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "FIR_LPF2.h"

FIR_LPF2::FIR_LPF2()
{
}

FIR_LPF2::~FIR_LPF2()
{
}

void FIR_LPF2::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // Prepara el filtro con las especificaciones del proceso
    lowPassFilter.prepare(spec);
    //lowPassFilter2.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

void FIR_LPF2::process(juce::AudioBuffer<float>& buffer)
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

void FIR_LPF2::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void FIR_LPF2::updateFilter()
{
    // Crea los coeficientes del filtro FIR de paso bajo usando el método Kaiser
    auto coefficients = juce::dsp::FilterDesign<float>::designFIRLowpassTransitionMethod(        
        cutoffFrequency,
        sampleRate,
        125, // Ajusta el número de coeficientes según sea necesario
        0.4,4.0); // Parámetro beta de Kaiser

    // Asigna los coeficientes al filtro
    lowPassFilter.coefficients = coefficients;
    lowPassFilter2.coefficients = coefficients;
}