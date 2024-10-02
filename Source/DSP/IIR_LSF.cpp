/*
  ==============================================================================

    IIR_LSF.cpp
    Created: 30 Sep 2024 1:53:16pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_LSF.h"
IIR_LSF::IIR_LSF()
{
}

IIR_LSF::~IIR_LSF()
{
}

void IIR_LSF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
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

void IIR_LSF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    foApf.process(context);
}

void IIR_LSF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIR_LSF::setQ(float newQ)
{
    q = newQ;
    updateFilter();  // Recalcula los coeficientes con el nuevo q.
}

void IIR_LSF::setGain(float newGain)
{
    gain = newGain;
    updateFilter(); // Recalcula los coeficientes con el nueva ganancia.
}

void IIR_LSF::updateFilter()
{
    // Crea los coeficientes del filtro FIR
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeLowShelf(
        sampleRate,
        cutoffFrequency, q, gain);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *foApf.state = *coefficients;
}