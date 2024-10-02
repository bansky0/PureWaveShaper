/*
  ==============================================================================

    IIR_FirstOrderLPF.cpp
    Created: 30 Sep 2024 11:08:21am
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_FirstOrderLPF.h"

IIRFirstOrderLPF::IIRFirstOrderLPF()
{
}

IIRFirstOrderLPF::~IIRFirstOrderLPF()
{
}

void IIRFirstOrderLPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // Prepara el filtro con las especificaciones del proceso
    foLpf.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

void IIRFirstOrderLPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    foLpf.process(context);
}

void IIRFirstOrderLPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIRFirstOrderLPF::updateFilter()
{
    // Crea los coeficientes del filtro FIR de paso bajo usando el método Kaiser
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(
        sampleRate,
        cutoffFrequency);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *foLpf.state = *coefficients;
}