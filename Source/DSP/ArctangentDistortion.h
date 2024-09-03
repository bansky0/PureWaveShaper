/*
  ==============================================================================

    ArctangentDistortion.h
    Created: 2 Sep 2024 10:08:57pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ArctangentDistortion
{
public:

    void setArctangentDistortionDrive(float inArctangentDistortionDriveValue);

    void process(juce::AudioBuffer<float>& buffer);

	ArctangentDistortion();
	~ArctangentDistortion();

private:
    float pi{ juce::MathConstants<float>::pi };
    float alpha{};//1-10
};