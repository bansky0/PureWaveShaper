/*
  ==============================================================================

    BitReduction.cpp
    Created: 4 Sep 2024 10:39:47am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "BitReduction.h"

// EN: Sets the bit depth value for the bit reduction effect.
// ES: Establece el valor de profundidad de bits para el efecto de reducción de bits.
void BitReduction::setBitNumberValue(float inBitNumberValue)
{
    bitNumber = inBitNumberValue;
}

// EN: Applies the bit reduction effect to the audio buffer.
// ES: Aplica el efecto de reducción de bits al buffer de audio.
void BitReduction::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Calculate the amplitude value based on the bit depth.
    // ES: Calcula el valor de amplitud basado en la profundidad de bits.
    float ampValue = powf(2.0f, bitNumber);

    // EN: Iterate over all channels in the audio buffer.
    // ES: Itera sobre todos los canales en el buffer de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Iterate over all samples in the current channel.
        // ES: Itera sobre todas las muestras en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Get the input sample value from the buffer.
            // ES: Obtiene el valor de la muestra de entrada del buffer.
            float inSample = buffer.getSample(channel, i);

            // EN: Normalize the sample to the range [0, 1].
            // ES: Normaliza la muestra al rango [0, 1].
            float preIn = 0.5f * inSample + 0.5f;

            // EN: Scale the normalized value by the amplitude value.
            // ES: Escala el valor normalizado por el valor de amplitud.
            float scaleIn = ampValue * preIn;

            // EN: Round the scaled value to the nearest integer.
            // ES: Redondea el valor escalado al entero más cercano.
            float roundIn = roundf(scaleIn);

            // EN: Convert the rounded value back to the normalized range.
            // ES: Convierte el valor redondeado de vuelta al rango normalizado.
            float preOut = roundIn / ampValue;

            // EN: Map the normalized output back to the range [-1, 1].
            // ES: Mapea la salida normalizada de vuelta al rango [-1, 1].
            float outSample = 2.0f * preOut - 1;

            // EN: Set the processed sample back into the buffer.
            // ES: Establece la muestra procesada de vuelta en el buffer.
            buffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor for the BitReduction class.
// ES: Constructor de la clase BitReduction.
BitReduction::BitReduction()
{
}

// EN: Destructor for the BitReduction class.
// ES: Destructor de la clase BitReduction.
BitReduction::~BitReduction()
{
}