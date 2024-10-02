/*
  ==============================================================================

    IIR_HPF.cpp
    Created: 29 Sep 2024 8:49:51pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_HPF.h"

IIR_HPF::IIR_HPF()
{
}

IIR_HPF::~IIR_HPF()
{
}

void IIR_HPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo
    
    // Prepara el filtro con las especificaciones del proceso
    hpf.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

void IIR_HPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    hpf.process(context);
}

void IIR_HPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIR_HPF::updateFilter()
{
    // Crea los coeficientes del filtro
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(
        sampleRate,
        cutoffFrequency);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *hpf.state = *coefficients;
}