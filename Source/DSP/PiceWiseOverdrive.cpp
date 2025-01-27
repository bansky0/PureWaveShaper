/*
  ==============================================================================

    PiceWiseOverdrive.cpp
    Created: 3 Sep 2024 1:43:52pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "PiceWiseOverdrive.h"

void PiceWiseOverdrive::process(juce::AudioBuffer<float>& buffer)
{
    // Recorre los canales del buffer de audio
    // ES: Itera sobre cada canal del buffer de audio para aplicar la distorsión.
    // EN: Iterates over each channel of the audio buffer to apply the distortion.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // Recorre las muestras de cada canal
        // ES: Itera sobre cada muestra dentro de un canal específico.
        // EN: Iterates over each sample in a specific channel.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Obtiene la muestra de entrada para el canal y la posición actual
            // ES: Obtiene el valor de la muestra en el canal y la posición de muestra actual.
            // EN: Gets the sample value for the current channel and sample position.
            float inSample = buffer.getSample(channel, i);
            float absValue = std::abs(inSample);  // Valor absoluto de la muestra de entrada
            float processedSample = 0.0f;         // Variable para la muestra procesada
            float outSample = 0.0f;              // Variable para la muestra de salida

            // Aplica la distorsión por tramos
            // ES: El comportamiento de la distorsión se ajusta según el valor absoluto de la muestra de entrada.
            // EN: The distortion behavior is adjusted based on the absolute value of the input sample.

            // Si el valor absoluto es menor o igual a 1/3, aplica una amplificación lineal.
            // ES: Amplifica la muestra de entrada por un factor de 2 si su valor absoluto es pequeño.
            // EN: Amplifies the input sample by a factor of 2 if its absolute value is small.
            if (absValue <= 1.0f / 3.0f)
            {
                processedSample = 2.0f * inSample;
            }
            // Si el valor absoluto es mayor que 2/3, recorta la señal a un valor máximo o mínimo (distorsión fuerte).
            // ES: Aplica un recorte de señal fuerte si el valor absoluto es mayor que 2/3.
            // EN: Applies hard clipping if the absolute value is greater than 2/3.
            else if (absValue > 2.0f / 3.0f)
            {
                processedSample = inSample >= 0.0f ? 1.0f : -1.0f;
            }
            // Para valores intermedios, aplica una curva cuadrática que suaviza la distorsión.
            // ES: Aplica una distorsión más suave para valores intermedios, utilizando una curva cuadrática.
            // EN: Applies a smoother distortion for intermediate values using a quadratic curve.
            else
            {
                float signValue = inSample >= 0.0f ? 1.0f : -1.0f; // Determina el signo de la muestra de entrada
                processedSample = signValue * (3.0f - std::pow(2.0f - 3.0f * absValue, 2)) / 3.0f;
                // Fórmula para la distorsión suave: ajuste no lineal de la muestra de entrada.
                // EN: Formula for smooth distortion: non-linear adjustment of the input sample.
            }

            // Asigna el valor de la muestra procesada al buffer
            // ES: Asigna el valor de la muestra procesada a la posición actual en el buffer.
            // EN: Assigns the processed sample value to the current position in the buffer.
            outSample = processedSample;
            buffer.setSample(channel, i, outSample);
        }
    }
}

// Constructor de la clase
// ES: Inicializa una nueva instancia de la clase PiceWiseOverdrive.
// EN: Initializes a new instance of the PiceWiseOverdrive class.
PiceWiseOverdrive::PiceWiseOverdrive()
{
}

// Destructor de la clase
// ES: Libera recursos cuando la instancia de PiceWiseOverdrive se destruye.
// EN: Releases resources when the PiceWiseOverdrive instance is destroyed.
PiceWiseOverdrive::~PiceWiseOverdrive()
{
}