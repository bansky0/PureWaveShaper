/*
  ==============================================================================

    SimpleDelay.cpp
    Created: 17 Sep 2024 1:08:03pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SimpleDelay.h"

// EN: Prepares the delay by setting the sample rate of the audio.
// ES: Prepara el delay configurando la frecuencia de muestreo del audio.
void SimpleDelay::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

// EN: Sets the delay time in seconds and converts it to samples.
// ES: Configura el tiempo de delay en segundos y lo convierte a muestras.
void SimpleDelay::setDelay(float inDelay)
{
    // EN: Converts the delay time (in seconds) to samples based on the sample rate.
    // ES: Convierte el tiempo de delay (en segundos) a muestras basado en la frecuencia de muestreo.
    delay = static_cast<int>(std::floor(inDelay * sampleRate));
}

// EN: Processes the input buffer and applies the delay effect.
// ES: Procesa el búfer de entrada y aplica el efecto de delay.
void SimpleDelay::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Stores the output from the circular buffer for processing.
    // ES: Almacena la salida del búfer circular para el procesamiento.
    auto outputCircularBuffer = 0.0f;

    // EN: Iterate over each audio channel.
    // ES: Itera sobre cada canal de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Iterate over each audio sample in the current channel.
        // ES: Itera sobre cada muestra de audio en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (delay >= 1) // EN: Ensure delay is valid (at least 1 sample).
                // ES: Asegura que el delay sea válido (al menos 1 muestra).
            {
                // EN: Get the current input sample.
                // ES: Obtiene la muestra de entrada actual.
                auto sample = buffer.getReadPointer(channel)[i];

                // EN: Calculate the position of the reader pointer in the circular buffer.
                // ES: Calcula la posición del puntero de lectura en el búfer circular.
                readerPointer = writterPointer[channel] - delay;
                if (readerPointer < 0) // EN: Wrap around if the pointer goes negative.
                    // ES: Regresa al final si el puntero se vuelve negativo.
                {
                    readerPointer += circularBufferSize;
                }

                // EN: Retrieve the delayed sample from the circular buffer.
                // ES: Recupera la muestra con delay del búfer circular.
                outputCircularBuffer = circularBuffer[readerPointer][channel];

                // EN: Write the current input sample to the circular buffer.
                // ES: Escribe la muestra de entrada actual en el búfer circular.
                circularBuffer[writterPointer[channel]][channel] = sample;

                // EN: Increment the writer pointer and wrap it around if necessary.
                // ES: Incrementa el puntero de escritura y lo regresa al inicio si es necesario.
                writterPointer[channel]++;
                if (writterPointer[channel] >= circularBufferSize)
                {
                    writterPointer[channel] = 0;
                }

                // EN: Combine the input sample and the delayed sample for output.
                // ES: Combina la muestra de entrada y la muestra con delay para la salida.
                auto out = sample + outputCircularBuffer;

                // EN: Write the output sample back to the audio buffer.
                // ES: Escribe la muestra de salida de vuelta en el búfer de audio.
                buffer.getWritePointer(channel)[i] = out;
            }
        }
    }
}

// EN: Constructor for the SimpleDelay class. Initializes default values.
// ES: Constructor de la clase SimpleDelay. Inicializa valores predeterminados.
SimpleDelay::SimpleDelay()
{
}

// EN: Destructor for the SimpleDelay class. Cleans up resources if necessary.
// ES: Destructor de la clase SimpleDelay. Libera recursos si es necesario.
SimpleDelay::~SimpleDelay()
{
}