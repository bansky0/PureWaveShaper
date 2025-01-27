/*
  ==============================================================================

    FlangerEffect.cpp
    Created: 30 Oct 2024 3:56:42pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "FlangerEffect.h"

// EN: Prepares the flanger effect by initializing necessary variables such as sample rate, time, rate, and predelay.
//     This function should be called before processing audio to set up the effect parameters.
// ES: Prepara el efecto flanger inicializando las variables necesarias como la frecuencia de muestreo, el tiempo, la tasa y el predelay.
//     Esta función debe ser llamada antes de procesar el audio para configurar los parámetros del efecto.
void FlangerFX::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // EN: Convert sample rate from double to float. // ES: Convierte la frecuencia de muestreo de doble a flotante.
    t = 0.0f;  // EN: Initialize time to 0. // ES: Inicializa el tiempo en 0.
    ratePercentage = 0.0f;  // EN: Initialize rate percentage to 0. // ES: Inicializa el porcentaje de la tasa en 0.
    targetRatePercentage = 0.0f;  // EN: Initialize target rate percentage to 0. // ES: Inicializa el porcentaje de la tasa objetivo en 0.
    predelay = 0.0f; // EN: Initialize predelay to 0. // ES: Inicializa el predelay en 0.
}

// EN: Sets the depth of the flanger effect. This defines how intense the modulation is.
//     The depth is converted from milliseconds to samples based on the sample rate.
// ES: Establece la profundidad del efecto flanger. Esto define cuán intensa es la modulación.
//     La profundidad se convierte de milisegundos a muestras según la frecuencia de muestreo.
void FlangerFX::setDepth(float inDepth)
{
    depth = inDepth * sampleRate / 1000.0f; // EN: Convert depth from milliseconds to samples. // ES: Convierte la profundidad de milisegundos a muestras.
}

// EN: Sets the modulation rate as a percentage, limiting the value between 0 and 100.
//     This percentage is then used to calculate the actual modulation rate in Hz.
// ES: Establece la tasa de modulación como un porcentaje, limitando el valor entre 0 y 100.
//     Este porcentaje se usa luego para calcular la tasa de modulación real en Hz.
void FlangerFX::setRate(float inRatePercentage)
{
    targetRatePercentage = juce::jlimit(0.0f, 100.0f, inRatePercentage) / 100.0f; // EN: Limit the rate percentage to a valid range between 0 and 100. // ES: Limita el porcentaje de la tasa a un rango válido entre 0 y 100.
}

// EN: Sets the predelay time in milliseconds. This defines the delay before the effect starts to modulate.
//     It is converted from milliseconds to samples based on the sample rate.
// ES: Establece el tiempo de predelay en milisegundos. Esto define el retardo antes de que el efecto comience a modularse.
//     Se convierte de milisegundos a muestras según la frecuencia de muestreo.
void FlangerFX::setPredelay(float inPredelayMs)
{
    predelay = inPredelayMs * sampleRate / 1000.0f; // EN: Convert predelay from milliseconds to samples. // ES: Convierte el predelay de milisegundos a muestras.
}

// EN: Processes the audio buffer and applies the flanger effect on each channel.
//     The effect uses a circular buffer to store delayed samples and modulates the delay based on an LFO (Low-Frequency Oscillator).
//     The delay time is adjusted based on depth, rate, and predelay, and applied to the audio signal.
//     The output is written back into the buffer, replacing the original signal.
// ES: Procesa el búfer de audio y aplica el efecto flanger en cada canal.
//     El efecto usa un búfer circular para almacenar las muestras retardadas y modula el retardo basado en un LFO (oscilador de baja frecuencia).
//     El tiempo de retardo se ajusta en función de la profundidad, la tasa y el predelay, y se aplica a la señal de audio.
//     El resultado se escribe de vuelta en el búfer, reemplazando la señal original.
void FlangerFX::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t; // EN: Save the current time to avoid changes during processing. // ES: Guarda el tiempo actual para evitar cambios durante el procesamiento.
    const float minRateHz = 0.1f; // EN: Minimum modulation rate in Hz. // ES: Tasa mínima de modulación en Hz.
    const float maxRateHz = 5.0f; // EN: Maximum modulation rate in Hz. // ES: Tasa máxima de modulación en Hz.

    // EN: Loop through all channels in the audio buffer. // ES: Recorre todos los canales en el búfer de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t; // EN: Restore the saved time for each channel. // ES: Restaura el tiempo guardado para cada canal.
        // EN: Loop through all samples in the current channel. // ES: Recorre todas las muestras en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i]; // EN: Read the current sample from the buffer. // ES: Lee la muestra actual del búfer.
            ratePercentage = targetRatePercentage; // EN: Set the current rate percentage to the target rate percentage. // ES: Establece el porcentaje de la tasa actual al porcentaje de la tasa objetivo.
            float rateHz = minRateHz + ratePercentage * (maxRateHz - minRateHz); // EN: Calculate the modulation rate in Hz. // ES: Calcula la tasa de modulación en Hz.
            float lfoValue = (depth / 2.0f) * sin(2.0 * juce::MathConstants<float>::pi * rateHz * t) + depth; // EN: Generate the LFO value based on the rate and depth. // ES: Genera el valor LFO basado en la tasa y profundidad.
            float fracDelay = static_cast<float>(writterPointer[channel]) - lfoValue - predelay; // EN: Calculate the fractional delay using the LFO value and predelay. // ES: Calcula el retardo fraccionario usando el valor LFO y el predelay.
            if (fracDelay < 0) fracDelay += circularBufferSize; // EN: Wrap around if the delay goes below 0. // ES: Vuelve al principio si el retardo es menor que 0.

            int intDelay = static_cast<int>(fracDelay); // EN: Get the integer part of the delay. // ES: Obtiene la parte entera del retardo.
            float frac = fracDelay - intDelay; // EN: Get the fractional part of the delay. // ES: Obtiene la parte fraccionaria del retardo.
            int nextSampleIndex = intDelay + 1; // EN: Get the next sample index in the buffer. // ES: Obtiene el índice de la siguiente muestra en el búfer.
            if (nextSampleIndex >= circularBufferSize) nextSampleIndex = 0; // EN: Wrap around to the beginning of the buffer if necessary. // ES: Vuelve al principio del búfer si es necesario.

            // EN: Get the delayed sample by interpolating between the two surrounding samples. // ES: Obtiene la muestra retardada interpolando entre las dos muestras adyacentes.
            float delayedSample = (1.0f - frac) * circularBuffer[intDelay][channel] + frac * circularBuffer[nextSampleIndex][channel];
            circularBuffer[writterPointer[channel]][channel] = sample; // EN: Store the current sample in the circular buffer. // ES: Almacena la muestra actual en el búfer circular.
            writterPointer[channel]++; // EN: Move the write pointer forward. // ES: Avanza el puntero de escritura.
            if (writterPointer[channel] >= circularBufferSize) writterPointer[channel] = 0; // EN: Wrap the write pointer around to the beginning if necessary. // ES: Vuelve al principio del búfer si es necesario.

            buffer.getWritePointer(channel)[i] = delayedSample; // EN: Write the delayed sample back into the buffer. // ES: Escribe la muestra retardada de vuelta en el búfer.
            t += 1.0f / sampleRate; // EN: Increment time based on sample rate. // ES: Incrementa el tiempo según la frecuencia de muestreo.
        }
    }
}

// EN: Default constructor for the FlangerFX class. // ES: Constructor por defecto para la clase FlangerFX.
FlangerFX::FlangerFX() {}

// EN: Destructor for the FlangerFX class. // ES: Destructor para la clase FlangerFX.
FlangerFX::~FlangerFX() {}
