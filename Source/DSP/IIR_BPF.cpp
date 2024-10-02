/*
  ==============================================================================

    IIR_BPF.cpp
    Created: 30 Sep 2024 4:05:49pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_BPF.h"

IIR_BPF::IIR_BPF()
{
}

IIR_BPF::~IIR_BPF()
{
}


void IIR_BPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // Prepara el filtro con las especificaciones del proceso
    bpf.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

void IIR_BPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    bpf.process(context);
}

void IIR_BPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIR_BPF::updateFilter()
{
    // Crea los coeficientes del filtro FIR
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(
        sampleRate,
        cutoffFrequency);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *bpf.state = *coefficients;
}