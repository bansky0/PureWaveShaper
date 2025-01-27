/*
  ==============================================================================

    HardClip.cpp
    Created: 2 Sep 2024 8:43:08pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "HardClip.h"

// EN: Sets the threshold for the hard clipping effect. Converts the input value from decibels to linear gain.
// ES: Establece el umbral para el efecto de "hard clipping". Convierte el valor de entrada de decibelios a ganancia lineal.
void HardClip::setHardClipThresh(float inHardClipThreshValue)
{
    // EN: Convert the input decibel value to linear gain and assign it to the threshold.
    // ES: Convierte el valor de decibelios de entrada a ganancia lineal y lo asigna al umbral.
    thresh = juce::Decibels::decibelsToGain(inHardClipThreshValue);
}

// EN: Applies the hard clipping effect to the audio buffer by limiting the amplitude of each sample
//     based on the threshold value.
// ES: Aplica el efecto de "hard clipping" al búfer de audio limitando la amplitud de cada muestra
//     según el valor del umbral.
void HardClip::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Iterate through all the channels in the buffer.
    // ES: Iterar a través de todos los canales del búfer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Iterate through all the samples in the current channel.
        // ES: Iterar a través de todas las muestras en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Get the input sample from the buffer.
            // ES: Obtener la muestra de entrada desde el búfer.
            float inSample = buffer.getSample(channel, i);
            float outSample = 0.0f;

            // EN: Apply hard clipping based on the threshold:
            //     - If the sample is greater than or equal to the threshold, clip it to the threshold value.
            //     - If the sample is less than or equal to the negative threshold, clip it to the negative threshold value.
            //     - Otherwise, keep the sample unchanged.
            // ES: Aplicar el "hard clipping" según el umbral:
            //     - Si la muestra es mayor o igual al umbral, recortarla al valor del umbral.
            //     - Si la muestra es menor o igual al umbral negativo, recortarla al valor del umbral negativo.
            //     - De lo contrario, mantener la muestra sin cambios.
            if (inSample >= thresh)
            {
                outSample = thresh;
            }
            else if (inSample <= -thresh)
            {
                outSample = -thresh;
            }
            else
            {
                outSample = inSample;
            }

            // EN: Write the processed sample back into the buffer.
            // ES: Escribir la muestra procesada de vuelta en el búfer.
            buffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor for the HardClip class. Initializes the object.
// ES: Constructor de la clase HardClip. Inicializa el objeto.
HardClip::HardClip()
{
}

// EN: Destructor for the HardClip class. Cleans up resources if needed.
// ES: Destructor de la clase HardClip. Libera recursos si es necesario.
HardClip::~HardClip()
{
}