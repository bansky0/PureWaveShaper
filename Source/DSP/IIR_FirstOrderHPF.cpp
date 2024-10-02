/*
  ==============================================================================

    IIR_FirstOrderHPF.cpp
    Created: 30 Sep 2024 11:56:09am
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_FirstOrderHPF.h"

IIRFirstOrderHPF::IIRFirstOrderHPF()
{
}

IIRFirstOrderHPF::~IIRFirstOrderHPF()
{
}

void IIRFirstOrderHPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // Prepara el filtro con las especificaciones del proceso
    foHpf.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

void IIRFirstOrderHPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    foHpf.process(context);
}

void IIRFirstOrderHPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIRFirstOrderHPF::updateFilter()
{
    // Crea los coeficientes del filtro FIR
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(
        sampleRate,
        cutoffFrequency);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *foHpf.state = *coefficients;
}