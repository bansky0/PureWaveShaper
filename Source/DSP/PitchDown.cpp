/*
  ==============================================================================

    PitchDown.cpp
    Created: 5 Nov 2024 1:03:19pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "PitchDown.h"

// EN: Prepares the pitch-down effect by initializing parameters and clearing the delay buffer.
// ES: Prepara el efecto de pitch-down inicializando parámetros y limpiando el búfer de retardo.
void PitchDown::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // EN: Store the sample rate. | ES: Almacena la frecuencia de muestreo.
    delay = 0.0f;                                   // EN: Initialize the fractional delay. | ES: Inicializa el retardo fraccionario.
    writePosition = 0;                              // EN: Reset the write position pointer. | ES: Reinicia el puntero de escritura.

    // EN: Clear the delay buffer by setting all elements to zero.
    // ES: Limpia el búfer de retardo estableciendo todos los elementos a cero.
    std::fill(std::begin(delayBuffer), std::end(delayBuffer), 0.0f);
}

// EN: Processes the audio buffer to apply the pitch-down effect by altering playback speed using fractional delays.
// ES: Procesa el búfer de audio para aplicar el efecto pitch-down alterando la velocidad de reproducción usando retardos fraccionarios.
void PitchDown::process(juce::AudioBuffer<float>& buffer)
{
    int numSamples = buffer.getNumSamples();    // EN: Total number of samples in the buffer. | ES: Número total de muestras en el búfer.
    int numChannels = buffer.getNumChannels();  // EN: Number of audio channels. | ES: Número de canales de audio.

    for (int i = 0; i < numSamples; ++i)
    {
        // EN: Calculate the delay for this sample.
        // ES: Calcula el retardo para esta muestra.
        int intDelay = static_cast<int>(floor(delay));   // EN: Integer part of the delay. | ES: Parte entera del retardo.
        float frac = delay - intDelay;                  // EN: Fractional part of the delay. | ES: Parte fraccionaria del retardo.
        int readPosition = writePosition - intDelay;    // EN: Read position in the circular buffer. | ES: Posición de lectura en el búfer circular.

        // EN: Adjust the read position to handle circular buffer wraparound.
        // ES: Ajusta la posición de lectura para manejar el desbordamiento circular del búfer.
        if (readPosition < 0)
            readPosition += bufferSize;

        // EN: Calculate the next sample index for interpolation, wrapping if necessary.
        // ES: Calcula el índice de la siguiente muestra para interpolación, ajustando si es necesario.
        int nextSampleIndex = (readPosition + 1) % bufferSize;

        for (int channel = 0; channel < numChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel); // EN: Pointer to the current channel's data. | ES: Puntero a los datos del canal actual.

            // EN: Perform linear interpolation to get the pitch-shifted sample.
            // ES: Realiza una interpolación lineal para obtener la muestra con cambio de tono.
            float delayedSample = (1.0f - frac) * delayBuffer[readPosition]
                + frac * delayBuffer[nextSampleIndex];

            // EN: Store the current sample in the delay buffer for future use.
            // ES: Almacena la muestra actual en el búfer de retardo para uso futuro.
            delayBuffer[writePosition] = channelData[i];

            // EN: Write the pitch-shifted sample back to the current channel.
            // ES: Escribe la muestra con cambio de tono de vuelta al canal actual.
            channelData[i] = delayedSample;
        }

        // EN: Increment the delay to slow down playback, lowering the pitch.
        // ES: Incrementa el retardo para ralentizar la reproducción, bajando el tono.
        delay += 0.5f;

        // EN: Keep the delay size within the circular buffer's bounds.
        // ES: Mantiene el tamaño del retardo dentro de los límites del búfer circular.
        if (delay > bufferSize - 1)
            delay -= bufferSize;

        // EN: Update the write position in the circular buffer, wrapping if necessary.
        // ES: Actualiza la posición de escritura en el búfer circular, ajustando si es necesario.
        writePosition = (writePosition + 1) % bufferSize;
    }
}