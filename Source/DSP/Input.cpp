/*
  ==============================================================================

    Input.cpp
    Created: 19 Aug 2024 3:53:03pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::setInputValue(float inInputValue)
{
    inputValue = juce::Decibels::decibelsToGain(inInputValue);
}

void Input::process(juce::AudioBuffer<float>&buffer)
{

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float processesedSample = inSample*inputValue;            
            buffer.setSample(channel, i, processesedSample);
        }
    }
}