/*
  ==============================================================================

    PitchUp.cpp
    Created: 5 Nov 2024 4:21:53pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "PitchUp.h"

// EN: Initializes the parameters and clears the delay buffer.
// ES: Inicializa los parámetros y limpia el búfer de retardo.
void PitchUp::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // EN: Set the sample rate. 
                                                    // ES: Configura la frecuencia de muestreo.

    delay = static_cast<float>(bufferSize); // EN: Initialize the delay to the buffer size.
                                            // ES: Inicializa el retardo con el tamaño del búfer.

    writePosition = 0; // EN: Reset the write pointer to the beginning of the buffer.
                       // ES: Restablece el puntero de escritura al inicio del búfer.

// EN: Clear the circular delay buffer by setting all values to 0.
// ES: Limpia el búfer circular de retardo estableciendo todos los valores a 0.
    std::fill(std::begin(delayBuffer), std::end(delayBuffer), 0.0f);
}

// EN: Processes the audio buffer and applies the pitch-up effect.
// ES: Procesa el búfer de audio y aplica el efecto pitch-up.
void PitchUp::process(juce::AudioBuffer<float>& buffer)
{
    int numSamples = buffer.getNumSamples();   // EN: Get the number of samples in the buffer.
                                               // ES: Obtiene el número de muestras en el búfer.

    int numChannels = buffer.getNumChannels(); // EN: Get the number of channels in the buffer.
                                               // ES: Obtiene el número de canales en el búfer.

// EN: Iterate through all the samples in the buffer.
// ES: Itera a través de todas las muestras en el búfer.
    for (int i = 0; i < numSamples; ++i)
    {
        // EN: Process each channel separately.
        // ES: Procesa cada canal por separado.
        for (int channel = 0; channel < numChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel); // EN: Pointer to the current channel's data.
                                                                  // ES: Puntero a los datos del canal actual.

// EN: Calculate the delay for the current sample.
// ES: Calcula el retardo para la muestra actual.
            int intDelay = static_cast<int>(floorf(delay)); // EN: Integer part of the delay.
                                                            // ES: Parte entera del retardo.

            float frac = delay - intDelay; // EN: Fractional part of the delay.
                                           // ES: Parte fraccionaria del retardo.

            int readPosition = writePosition - intDelay; // EN: Calculate the read position in the delay buffer.
                                                         // ES: Calcula la posición de lectura en el búfer de retardo.

// EN: Wrap around the read position if it goes out of bounds.
// ES: Ajusta la posición de lectura si se sale de los límites.
            if (readPosition < 0)
                readPosition += bufferSize;

            int nextSampleIndex = (readPosition + 1) % bufferSize; // EN: Next sample index in the circular buffer.
                                                                   // ES: Índice de la siguiente muestra en el búfer circular.

// EN: Perform linear interpolation between the delayed samples.
// ES: Realiza interpolación lineal entre las muestras retardadas.
            float delayedSample = (1.0f - frac) * delayBuffer[readPosition] + frac * delayBuffer[nextSampleIndex];

            // EN: Store the current sample in the delay buffer.
            // ES: Almacena la muestra actual en el búfer de retardo.
            delayBuffer[writePosition] = channelData[i];

            // EN: Write the pitch-up sample to the current channel.
            // ES: Escribe la muestra con pitch-up en el canal actual.
            channelData[i] = delayedSample;
        }

        // EN: Increment the write pointer and wrap it around if necessary.
        // ES: Incrementa el puntero de escritura y lo ajusta si es necesario.
        if (++writePosition >= bufferSize)
            writePosition = 0;

        // EN: Decrease the delay to achieve a pitch-up effect.
        // ES: Disminuye el retardo para lograr el efecto pitch-up.
        delay -= 1.0f;

        // EN: Wrap the delay around if it goes out of bounds.
        // ES: Ajusta el retardo si se sale de los límites.
        if (delay < 0)
            delay += bufferSize;
    }
}
