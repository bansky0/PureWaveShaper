/*
  ==============================================================================

    MorphLFO.cpp
    Created: 28 Aug 2024 9:52:53am
    Author:  Jhonatan

  ==============================================================================
*/

#include "MorphLFO.h"

void MorphLfo::setShape(float inShapeValue)
{
    shapeValue = inShapeValue;
}
void MorphLfo::setDepth(float inDepthValue)
{
    depthValue = inDepthValue;
}
void MorphLfo::setFrequency(double inFrequecy)
{
    frequency = inFrequecy;
}
void MorphLfo::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}

void MorphLfo::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float amplitud = 0.5f * (depthValue / 100.0f);
            float offset = 1.0f - amplitud;

            float lfo= (2.0f * std::fmod(frequency * time[i] + 0.5f, 1.0f) - 1.0f);
            float newLfo = 0.0f;
            float outSample = 0.0f;
            float out = 0.0f;

            if (lfo >= 0)
            {
                newLfo = std::pow(lfo, 1.0f /shapeValue);
            }
            else
            {
                newLfo = -std::pow(std::abs(lfo), 1.0f / shapeValue);
            }
            float mod = (amplitud * newLfo) + offset;

            outSample = mod * inSample;

            buffer.setSample(channel, i, outSample);

            time[channel] += deltaTime[channel];

            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

MorphLfo::MorphLfo()
{
}

MorphLfo::~MorphLfo()
{
}