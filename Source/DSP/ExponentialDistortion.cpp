/*
  ==============================================================================

    ExponentialDistortion.cpp
    Created: 3 Sep 2024 12:32:28pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "ExponentialDistortion.h"

// EN: Set the value for the exponential distortion gain
// ES: Establecer el valor de la ganancia para la distorsión exponencial
void ExponentialDistortion::setExponentialDistortionValue(float inExponentialDistortionValue)
{
    gain = inExponentialDistortionValue;
}

// EN: Process the audio buffer with exponential distortion
// ES: Procesar el buffer de audio con distorsión exponencial
void ExponentialDistortion::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Iterate through each channel in the buffer
    // ES: Iterar sobre cada canal en el buffer
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Process each sample in the channel
        // ES: Procesar cada muestra en el canal
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Get the current sample from the buffer
            // ES: Obtener la muestra actual del buffer
            float inSample = buffer.getSample(channel, i);
            float processedSample = 0.0f;
            float outSample = 0.0f;

            // EN: Apply the exponential distortion formula for positive samples
            // ES: Aplicar la fórmula de distorsión exponencial para muestras positivas
            if (inSample >= 0.0f)
            {
                processedSample = (1 - expf(-fabs(gain * inSample)));
            }
            // EN: Apply the exponential distortion formula for negative samples
            // ES: Aplicar la fórmula de distorsión exponencial para muestras negativas
            else if (inSample < 0.0f)
            {
                processedSample = -(1 - expf(-fabs(gain * inSample)));
            }

            // EN: Set the processed sample as the output sample
            // ES: Establecer la muestra procesada como la muestra de salida
            outSample = processedSample;

            // EN: Set the processed output sample back into the buffer
            // ES: Colocar la muestra de salida procesada de vuelta en el buffer
            buffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor
// ES: Constructor
ExponentialDistortion::ExponentialDistortion()
{
}

// EN: Destructor
// ES: Destructor
ExponentialDistortion::~ExponentialDistortion()
{
}
