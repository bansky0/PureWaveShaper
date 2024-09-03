/*
  ==============================================================================

    MidSide.cpp
    Created: 31 Aug 2024 9:53:26am
    Author:  Jhonatan

  ==============================================================================
*/

#include "MidSide.h"

//void setMidSideValue(bool inMidSideValue)
//{
//    
//}
void MidSide::process(juce::AudioBuffer<float>& buffer)
{
    if (buffer.getNumChannels() < 2)
        return;
    //for (int channel = 0; channel < buffer.getNumChannels(); channel++) //also works with a bucle.
    //{
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            //float inSample = buffer.getSample(channel, i);

            float left = buffer.getSample(0, i);
            float right = buffer.getSample(1, i);
            //coding m/s
            float mid = 0.5f * (left + right);
            float side = 0.5f * (left - right);
            /*
            Process here!
            */
            //decoding m/s
            float newLeft = mid + side;
            float newRight = mid - side;
            
            /*output sample could be selected depending of the processes needed mid, side or processed new L/R*/
            buffer.setSample(0, i, side);

            buffer.setSample(1, i, side);
        }
    //}
}

MidSide::MidSide()
{
}

MidSide::~MidSide()
{
}