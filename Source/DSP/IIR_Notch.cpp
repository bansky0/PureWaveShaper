/*
  ==============================================================================

    IIR_Notch.cpp
    Created: 30 Sep 2024 6:27:34pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "IIR_Notch.h"

IIR_Notch::IIR_Notch()
{
}

IIR_Notch::~IIR_Notch()
{
}


void IIR_Notch::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
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

void IIR_Notch::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);

    juce::dsp::ProcessContextReplacing<float>context(block);

    notch.process(context);
}

void IIR_Notch::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Actualiza la frecuencia de corte
    updateFilter();  // Recalcula los coeficientes con la nueva frecuencia
}

void IIR_Notch::updateFilter()
{
    // Crea los coeficientes del filtro FIR
    auto coefficients = juce::dsp::IIR::Coefficients<float>::makeNotch(
        sampleRate,
        cutoffFrequency);  // Ajusta el número de coeficientes según sea necesario

    // Asigna los coeficientes al filtro
    *notch.state = *coefficients;
}