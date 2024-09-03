/*
  ==============================================================================

    StereoImager.cpp
    Created: 31 Aug 2024 11:53:59am
    Author:  Jhonatan

  ==============================================================================
*/

#include "StereoImager.h"
void StereoImager::setStereoImagerValue(float inStereoImagerWidthValue)
{
    widthValue = inStereoImagerWidthValue;
}

void StereoImager::process(juce::AudioBuffer<float>& buffer)
{
    if (buffer.getNumChannels() < 2)
        return;
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        //float inSample = buffer.getSample(channel, i);

        float left = buffer.getSample(0, i);
        float right = buffer.getSample(1, i);
        //coding m/s
        float mid = 0.5f * (left + right);
        float side = 0.5f * (left - right);
        
        //Process here!
        float newMid = (2.0f - widthValue) * mid;
        float newSide = widthValue * side;
        
        //decoding m/s
        float newLeft = newMid + newSide;
        float newRight = newMid - newSide;

        /*output sample could be selected depending of the processes needed mid, side or processed new L/R*/
        buffer.setSample(0, i, newLeft);

        buffer.setSample(1, i, newRight);
    }
}

StereoImager::StereoImager()
{
}

StereoImager::~StereoImager()
{
}