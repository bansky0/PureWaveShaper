/*
  ==============================================================================

    AmpModulation.h
    Created: 27 Aug 2024 2:40:42pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AmpModulation
{
public:
	AmpModulation();
	~AmpModulation();

    void setDepth(float inDepthValue);
    void setSpeed(float inSpeedValue);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float pi{ juce::MathConstants<float>::pi };
    float time[2];
    float deltTime[2];
    float sampleRate{44100.0f};

    //Tremolo parameters
    float depthValue{ 0 };//0-100
    float speedValue{ 5.0 };//0-20
    //float amp{0.5 * (depthValue / 100)};
    //float offset{ 1 - amp };

    ////Synthesize modulation signal
    //float f{ speed };
    //float phi{ 0 };
    //float sw{ sinf(2 * pi * f * t * phi) };
    //float mod{ amp * sw + offset };
};
