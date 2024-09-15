/*
  ==============================================================================

    RingModulation.cpp
    Created: 12 Sep 2024 2:55:02pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "RingModulation.h"

void RingModulation::setFrequency1(float inFreqOsc1)
{
    osc1 = inFreqOsc1;
    phaseIncrement1 = twoPi * osc1 / sampleRate;
}
void RingModulation::setAmplitud1(float inAmp1)
{
    amp1 = inAmp1;
}
void RingModulation::setFrequency2(float inFreqOsc2)
{
    osc2 = inFreqOsc2;
    phaseIncrement2 = twoPi * osc2 / sampleRate;
}
void RingModulation::setAmplitud2(float inAmp2)
{
    amp2 = inAmp2;
}

void RingModulation::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;

}
void RingModulation::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Calculamos la salida de la onda senoidal usando la fase actual
            float outSample = (amp1 * sinf(phase1[channel])) * (amp2 * sinf(phase2[channel]));

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

RingModulation::RingModulation()
{
}

RingModulation::~RingModulation()
{
}