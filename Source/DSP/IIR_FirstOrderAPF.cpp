/*
  ==============================================================================

    IIR_FirstOrderAPF.cpp
    Created: 30 Sep 2024 12:55:31pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_FirstOrderAPF.h"

IIRFirstOrderAPF::IIRFirstOrderAPF()
{
}

IIRFirstOrderAPF::~IIRFirstOrderAPF()
{
}

void IIRFirstOrderAPF::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
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

void IIRFirstOrderAPF::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    foApf.process(context);
}

void IIRFirstOrderAPF::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIRFirstOrderAPF::updateFilter()
{
    // Crea los coeficientes del filtro FIR
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeFirstOrderAllPass(
        sampleRate,
        cutoffFrequency);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *foApf.state = *coefficients;
}