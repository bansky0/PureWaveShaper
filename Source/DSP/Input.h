/*
  ==============================================================================

    Input.h
    Created: 19 Aug 2024 3:53:03pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Input
{
public:
	Input();
	~Input();
    void setInputValue(float inInputValue); //PARA QUE FUNCIONE CON EL UPDATEPARAMETERS
    void process(juce::AudioBuffer<float>&buffer);

private:
    float inputValue{ 0.0f };
};

