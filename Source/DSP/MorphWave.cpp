/*
  ==============================================================================

    MorphWave.cpp
    Created: 30 Aug 2024 11:25:40am
    Author:  Jhonatan

  ==============================================================================
*/

#include "MorphWave.h"
void MorphWave::setShape(float inShapeValue)
{
    shapeValue = inShapeValue;
}
void MorphWave::setFrequency(double inFrequecy) 
{
    frequency = inFrequecy;
}
void MorphWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}
void MorphWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float osc = (2.0f * std::fmod(frequency * time[i] + 0.5f, 1.0f) - 1.0f);
            float newWave = 0.0f;
            float outSample = 0.0f;
            float out = 0.0f;

            if (osc >= 0)
            {
                newWave = std::pow(osc, 1.0f / shapeValue);
            }
            else
            {
                newWave = -std::pow(std::abs(osc), 1.0f / shapeValue);
            }

            outSample = newWave;

            buffer.setSample(channel, i, outSample);

            time[channel] += deltaTime[channel];

            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}
MorphWave::MorphWave()
{
}

MorphWave::~MorphWave()
{
}