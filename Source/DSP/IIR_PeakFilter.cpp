/*
  ==============================================================================

    IIR_PeakFilter.cpp
    Created: 30 Sep 2024 6:28:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_PeakFilter.h"
IIR_PeakF::IIR_PeakF()
{
}

IIR_PeakF::~IIR_PeakF()
{
}


void IIR_PeakF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inChannels;

    sampleRate = inSampleRate; // Almacena la frecuencia de muestreo

    // Prepara el filtro con las especificaciones del proceso
    notch.prepare(spec);
    updateFilter(); // Inicializa el filtro con la frecuencia de corte inicial
}

void IIR_PeakF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    notch.process(context);
}

void IIR_PeakF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIR_PeakF::setQ(float newQ)
{
    q = newQ;
    updateFilter();  // Recalcula los coeficientes con el nuevo q.
}

void IIR_PeakF::setGain(float newGain)
{
    gain = newGain;
    updateFilter(); // Recalcula los coeficientes con el nueva ganancia.
}

void IIR_PeakF::updateFilter()
{
    // Crea los coeficientes del filtro FIR
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(
        sampleRate,
        cutoffFrequency, q, gain);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *notch.state = *coefficients;
}