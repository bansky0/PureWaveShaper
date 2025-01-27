/*
  ==============================================================================

    SimpleDelay3.cpp
    Created: 19 Sep 2024 1:00:10pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SimpleDelay3.h"

// EN: Prepares the delay effect by setting up the DSP process specifications and initializing the delay line.
// ES: Prepara el efecto de delay configurando las especificaciones del proceso DSP e inicializando la línea de delay.
void SimpleDelay3::prepare(double theSampleRate, int samplesPerBlock, juce::dsp::ProcessSpec& spec, int numChannels)
{
    spec.sampleRate = theSampleRate; // EN: Set the sample rate for the process spec.
                                     // ES: Establece la frecuencia de muestreo para las especificaciones del proceso.
    spec.maximumBlockSize = samplesPerBlock; // EN: Define the maximum block size for processing.
                                             // ES: Define el tamaño máximo del bloque para el procesamiento.
    spec.numChannels = numChannels; // EN: Specify the number of channels.
                                    // ES: Especifica el número de canales.

    myDelay.reset(); // EN: Resets the internal state of the delay line.
                     // ES: Reinicia el estado interno de la línea de delay.
    myDelay.prepare(spec); // EN: Prepares the delay line with the given specifications.
                           // ES: Prepara la línea de delay con las especificaciones dadas.
    myDelay.setDelay(48000); // EN: Set an initial delay value of 48000 samples (1 second at 48kHz).
                             // ES: Establece un valor inicial de delay de 48000 muestras (1 segundo a 48kHz).

    sampleRate = theSampleRate; // EN: Store the sample rate for future calculations.
                                // ES: Almacena la frecuencia de muestreo para cálculos futuros.
}

// EN: Sets the delay time in seconds and updates the delay line configuration.
// ES: Configura el tiempo de delay en segundos y actualiza la configuración de la línea de delay.
void SimpleDelay3::setTimeDelay(float delayTime)
{
    delay = static_cast<int>(std::floor(delayTime * sampleRate)); // EN: Convert delay time (in seconds) to samples.
                                                                  // ES: Convierte el tiempo de delay (en segundos) a muestras.
    myDelay.setDelay(delay); // EN: Update the delay line with the calculated delay in samples.
                             // ES: Actualiza la línea de delay con el valor de delay calculado en muestras.
    DBG(delay); // EN: Print the delay value to the debug output.
                // ES: Imprime el valor del delay en la salida de depuración.
}

// EN: Processes the audio buffer, applying the delay effect to each sample in each channel.
// ES: Procesa el búfer de audio, aplicando el efecto de delay a cada muestra en cada canal.
void SimpleDelay3::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // EN: Loop through each channel in the buffer.
                                                                        // ES: Itera por cada canal en el búfer.
    {
        auto* inSamples = buffer.getReadPointer(channel); // EN: Get a pointer to the input samples for the channel.
                                                          // ES: Obtiene un puntero a las muestras de entrada para el canal.
        auto* outSamples = buffer.getWritePointer(channel); // EN: Get a pointer to the output samples for the channel.
                                                            // ES: Obtiene un puntero a las muestras de salida para el canal.

        for (int i = 0; i < buffer.getNumSamples(); i++) // EN: Loop through each sample in the buffer.
                                                         // ES: Itera por cada muestra en el búfer.
        {
            float delayedSample = myDelay.popSample(channel); // EN: Retrieve the delayed sample from the delay line.
                                                              // ES: Recupera la muestra retrasada desde la línea de delay.

            myDelay.pushSample(channel, inSamples[i]); // EN: Push the current input sample into the delay line.
                                                       // ES: Inserta la muestra de entrada actual en la línea de delay.
            outSamples[i] = inSamples[i] + delayedSample; // EN: Mix the original sample with the delayed sample for the output.
                                                          // ES: Mezcla la muestra original con la muestra retrasada para la salida.
        }
    }
}

// EN: Constructor for the SimpleDelay3 class. Initializes the object.
// ES: Constructor de la clase SimpleDelay3. Inicializa el objeto.
SimpleDelay3::SimpleDelay3()
{
}

// EN: Destructor for the SimpleDelay3 class. Cleans up resources.
// ES: Destructor de la clase SimpleDelay3. Limpia los recursos.
SimpleDelay3::~SimpleDelay3()
{
}