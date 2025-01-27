/*
  ==============================================================================

    SimpleDelay2.cpp
    Created: 17 Sep 2024 3:41:36pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SimpleDelay2.h"

// EN: Prepares the delay by setting the sample rate. This is essential for delay time calculations.
// ES: Prepara el delay configurando la frecuencia de muestreo. Esto es esencial para los cálculos del tiempo de delay.
void SimpleDelay2::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

// EN: Configures the delay time based on the tempo in beats per minute (BPM).
// ES: Configura el tiempo de delay basado en el tempo en pulsaciones por minuto (BPM).
void SimpleDelay2::setBPM(float BPM)
{
    float beatsPerMin = BPM;                     // EN: The tempo in beats per minute. // ES: El tempo en pulsaciones por minuto.
    float beatsPerSec = beatsPerMin / 60;        // EN: Converts BPM to beats per second. // ES: Convierte BPM a pulsaciones por segundo.
    float secPerBeat = 1 / beatsPerSec;          // EN: Seconds per beat. // ES: Segundos por pulsación.
    float noteDiv = 1;                           // EN: Note division factor (e.g., quarter notes). // ES: Factor de división de nota (por ejemplo, negras).
    auto timeSec = noteDiv * secPerBeat;         // EN: Total delay time in seconds. // ES: Tiempo total de delay en segundos.
    delay = static_cast<int>(std::floor(timeSec * sampleRate)); // EN: Converts delay time to samples. // ES: Convierte el tiempo de delay a muestras.
}

// EN: Sets the amplitude of the delayed signal, which controls the mix level between dry and wet signals.
// ES: Configura la amplitud de la señal con delay, controlando el nivel de mezcla entre la señal seca y la señal procesada.
void SimpleDelay2::setAmpDelay(float inAmpDelay)
{
    ampDelay = inAmpDelay;
}

// EN: Configures the feedback amount, dividing the input value by 100 to normalize it.
// ES: Configura la cantidad de feedback, dividiendo el valor de entrada por 100 para normalizarlo.
void SimpleDelay2::setFeedback(float inFeedback)
{
    feedback = inFeedback / 100.0f; // EN: Normalize feedback to a range of 0.0 - 1.0. // ES: Normaliza el feedback a un rango de 0.0 - 1.0.
}

// EN: Processes the audio buffer, applying the delay effect with optional feedback and amplitude scaling.
// ES: Procesa el búfer de audio, aplicando el efecto de delay con retroalimentación opcional y escalado de amplitud.
void SimpleDelay2::process(juce::AudioBuffer<float>& buffer)
{
    auto outputCircularBuffer = 0.0f; // EN: Temporary variable for reading from the circular buffer. // ES: Variable temporal para leer del búfer circular.

    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // EN: Loop through all audio channels. // ES: Recorre todos los canales de audio.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) // EN: Loop through all samples in the buffer. // ES: Recorre todas las muestras del búfer.
        {
            if (delay >= 1) // EN: Only process if the delay time is valid (greater than or equal to 1 sample). // ES: Procesa solo si el tiempo de delay es válido (mayor o igual a 1 muestra).
            {
                auto sample = buffer.getReadPointer(channel)[i]; // EN: Read the current sample from the buffer. // ES: Lee la muestra actual del búfer.

                // EN: Calculate the position in the circular buffer to read from.
                // ES: Calcula la posición en el búfer circular para leer.
                readerPointer = writterPointer[channel] - delay;
                if (readerPointer < 0) // EN: Handle wrap-around if the reader pointer goes negative. // ES: Gestiona el desbordamiento si el puntero de lectura es negativo.
                {
                    readerPointer += circularBufferSize;
                }
                outputCircularBuffer = circularBuffer[readerPointer][channel]; // EN: Read the delayed sample. // ES: Lee la muestra con delay.

                // EN: Write the current sample to the circular buffer, adding the feedback signal.
                // ES: Escribe la muestra actual en el búfer circular, añadiendo la señal de feedback.
                circularBuffer[writterPointer[channel]][channel] = sample + (outputCircularBuffer * feedback);

                writterPointer[channel]++; // EN: Advance the writer pointer. // ES: Avanza el puntero de escritura.
                if (writterPointer[channel] >= circularBufferSize) // EN: Handle wrap-around if the writer pointer exceeds the buffer size. // ES: Gestiona el desbordamiento si el puntero de escritura excede el tamaño del búfer.
                {
                    writterPointer[channel] = 0;
                }

                // EN: Calculate the output sample by mixing the current sample with the delayed signal.
                // ES: Calcula la muestra de salida mezclando la muestra actual con la señal retrasada.
                auto out = sample - (outputCircularBuffer * ampDelay); // EN: Subtracts for inverse delay; change to '+' for forward delay. // ES: Resta para un delay inverso; cambiar a '+' para un delay normal.

                buffer.getWritePointer(channel)[i] = out; // EN: Write the processed sample back to the buffer. // ES: Escribe la muestra procesada de nuevo en el búfer.
            }
        }
    }
}

// EN: Constructor for the SimpleDelay2 class.
// ES: Constructor de la clase SimpleDelay2.
SimpleDelay2::SimpleDelay2()
{
}

// EN: Destructor for the SimpleDelay2 class.
// ES: Destructor de la clase SimpleDelay2.
SimpleDelay2::~SimpleDelay2()
{
}