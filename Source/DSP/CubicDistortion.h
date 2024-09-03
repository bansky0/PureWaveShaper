/*
  ==============================================================================

    CubicDistortion.h
    Created: 2 Sep 2024 9:17:07pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CubicDistortion
{
public:

    void setCubicDistortionDrive(float inCubicDistortionDriveValue);

    void process(juce::AudioBuffer<float>& buffer);

	CubicDistortion();
	~CubicDistortion();

private:
    float drive = 0.0f; //0-1
};