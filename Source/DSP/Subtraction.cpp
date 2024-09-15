/*
  ==============================================================================

    Subtraction.cpp
    Created: 11 Sep 2024 2:32:06pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Subtraction.h"

void Subtraction::setFrequency1(float inFreqOsc1)
{
    osc1 = inFreqOsc1;
    phaseIncrement1 = osc1 * twoPi / sampleRate;
    //if (sampleRate > 0.0f)
    //{
    //    phaseIncrement1 = 1.0f / (sampleRate / osc1);
    //}
}
void Subtraction::setAmplitud1(float inAmp1)
{
    amp1 = inAmp1;
}
void Subtraction::setFrequency2(float inFreqOsc2)
{
    osc2 = inFreqOsc2;
    phaseIncrement2 = osc2 * twoPi / sampleRate;
}
void Subtraction::setAmplitud2(float inAmp1)
{
    amp2 = inAmp1;
}
void Subtraction::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}
void Subtraction::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            //Square wave
            //float outSqrWave = (phase1[channel] < 0.5f) ? 1.0f : -1.0f;
            // Calculamos la salida de la onda senoidal usando la fase actual
            float sw1 = amp1 * sinf(phase1[channel]); //amp1 * ((phase1[channel] < 0.5f) ? 1.0f : -1.0f); //
            float sw2 = amp2 * sinf(phase2[channel]);
            float outSample = sw2 - sw1;

            // Guardamos el valor en el buffer
            buffer.setSample(channel, i, outSample);

            // Actualizamos la fase y la mantenemos dentro del rango [0, 2pi]
            phase1[channel] += phaseIncrement1;

            if (phase1[channel] >= twoPi)
                phase1[channel] -= twoPi;

            phase2[channel] += phaseIncrement2;

            if (phase2[channel] >= twoPi)
                phase2[channel] -= twoPi;
        }
    }
}
Subtraction::Subtraction()
{
}

Subtraction::~Subtraction()
{
}