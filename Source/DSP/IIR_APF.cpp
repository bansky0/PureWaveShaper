/*
  ==============================================================================

    IIR_APF.cpp
    Created: 30 Sep 2024 1:14:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_APF.h"
IIR_APF::IIR_APF()
{
}

IIR_APF::~IIR_APF()
{
}

void IIR_APF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // Prepara el filtro con las especificaciones del proceso
    foApf.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

void IIR_APF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    foApf.process(context);
}

void IIR_APF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIR_APF::updateFilter()
{
    // Crea los coeficientes del filtro FIR
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeAllPass(
        sampleRate,
        cutoffFrequency);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *foApf.state = *coefficients;
}