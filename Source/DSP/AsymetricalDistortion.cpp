/*
  ==============================================================================

    AsymetricalDistortion.cpp
    Created: 4 Sep 2024 1:26:39pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "AsymetricalDistortion.h"

// EN: Sets the DC value, which controls the amount of distortion applied to the signal.
//     A value of 0 means no distortion, negative values reduce the wave, and positive values push it higher.
// ES: Configura el valor de DC, que controla la cantidad de distorsión aplicada a la señal.
//     Un valor de 0 significa sin distorsión, valores negativos reducen la onda y valores positivos la empujan más alto.
void AsymetricalDistortion::setDCValue(float inDCValue)
{
    dc = inDCValue;
}

// EN: Processes the audio buffer to apply the asymmetrical distortion effect, using a custom non-linear function.
//     The input signal is first shifted by the DC value, then distorted with a power-based function.
//     The result is then shifted back by the DC value before being output.
// ES: Procesa el buffer de audio para aplicar el efecto de distorsión asimétrica, utilizando una función no lineal personalizada.
//     La señal de entrada se desplaza primero por el valor DC, luego se distorsiona con una función basada en potencias.
//     El resultado luego se desplaza de vuelta por el valor DC antes de ser enviado como salida.
void AsymetricalDistortion::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)  // EN: Loops through each channel of the buffer. | ES: Recorre cada canal del buffer.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)  // EN: Loops through each sample in the buffer. | ES: Recorre cada muestra en el buffer.
        {
            float inSample = buffer.getSample(channel, i);  // EN: Retrieves the current input sample. | ES: Obtiene la muestra de entrada actual.
            float x = inSample + dc;  // EN: Shifts the sample by the DC value before applying distortion. | ES: Desplaza la muestra por el valor DC antes de aplicar la distorsión.
            float outSample = 0.0f;

            // EN: If the absolute value of the signal is greater than 1, it is clipped to the sign of 1.
            //     This creates the asymmetrical clipping effect.
            // ES: Si el valor absoluto de la señal es mayor que 1, se recorta al signo de 1.
            //     Esto crea el efecto de recorte asimétrico.
            if (std::abs(x) > 1.0f)
            {
                x = std::copysign(1.0f, x);  // EN: Clamps the value to 1 or -1 based on its sign. | ES: Limita el valor a 1 o -1 según su signo.
            }

            // EN: Applies the asymmetrical distortion function, a custom 5th power non-linearity.
            //     This introduces harmonic distortion, and the signal is then shifted back by the DC value.
            // ES: Aplica la función de distorsión asimétrica, una no linealidad personalizada basada en la quinta potencia.
            //     Esto introduce distorsión armónica, y luego la señal se desplaza de vuelta por el valor DC.
            float outSample1 = x - (1.0f / 5.0f) * powf(x, 5.0f);

            outSample = outSample1 - dc;  // EN: Shifts the output sample back by the DC value. | ES: Desplaza la muestra de salida de vuelta por el valor DC.
            buffer.setSample(channel, i, outSample);  // EN: Sets the output sample to the buffer. | ES: Establece la muestra de salida en el buffer.
        }
    }
}

// EN: Default constructor for the AsymetricalDistortion class. | ES: Constructor por defecto de la clase AsymetricalDistortion.
AsymetricalDistortion::AsymetricalDistortion()
{
}

// EN: Destructor for the AsymetricalDistortion class. | ES: Destructor de la clase AsymetricalDistortion.
AsymetricalDistortion::~AsymetricalDistortion()
{
}