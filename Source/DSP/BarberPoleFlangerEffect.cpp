/*
  ==============================================================================

    BarberPoleFeedback.cpp
    Created: 5 Nov 2024 8:29:25am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "BarberpoleFlangerEffect.h"

// EN: Prepares the Barberpole Flanger effect by initializing the sample rate and variables.
// ES: Prepara el efecto de Barberpole Flanger inicializando la frecuencia de muestreo y las variables.
void BarberpoleFlangerFX::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    t = 0.0f; // EN: Initializes the time variable for phase calculation.
    // ES: Inicializa la variable de tiempo para el cálculo de la fase.
    ratePercentage = 0.0f; // EN: Initializes the current rate percentage.
    // ES: Inicializa el porcentaje actual de velocidad.
    targetRatePercentage = 0.0f; // EN: Sets the target rate percentage to 0.
    // ES: Establece el porcentaje objetivo de velocidad en 0.
    predelay = 0.0f; // EN: Initializes the pre-delay in samples.
    // ES: Inicializa el pre-delay en muestras.
}

// EN: Sets the depth of the flanger effect, controlling the modulation intensity.
// ES: Configura la profundidad del efecto flanger, controlando la intensidad de la modulación.
void BarberpoleFlangerFX::setDepth(float inDepth)
{
    depth = inDepth;
}

// EN: Sets the target rate for the flanger, limiting it to a percentage between 0% and 100%.
// ES: Configura la velocidad objetivo para el flanger, limitándola a un porcentaje entre 0% y 100%.
void BarberpoleFlangerFX::setRate(float inRatePercentage)
{
    targetRatePercentage = juce::jlimit(0.0f, 100.0f, inRatePercentage) / 100.0f;
}

// EN: Sets the pre-delay time in milliseconds and converts it to samples.
// ES: Configura el tiempo de pre-delay en milisegundos y lo convierte a muestras.
void BarberpoleFlangerFX::setPredelay(float inPredelayMs)
{
    predelay = inPredelayMs * sampleRate / 1000.0f; // EN: Converts milliseconds to samples.
    // ES: Convierte milisegundos a muestras.
}

// EN: Generates a normalized sawtooth waveform based on the given phase.
// ES: Genera una onda diente de sierra normalizada basada en la fase dada.
float BarberpoleFlangerFX::generateSawtooth(float phase)
{
    return 2.0f * (phase - floorf(phase + 0.5f));
}

// EN: Processes the audio buffer to apply the Barberpole Flanger effect.
// ES: Procesa el buffer de audio para aplicar el efecto Barberpole Flanger.
void BarberpoleFlangerFX::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t; // EN: Stores the current phase time for each channel's independent processing.
    // ES: Almacena el tiempo de fase actual para el procesamiento independiente de cada canal.
    const float minRateHz = 0.1f; // EN: Minimum modulation rate in Hz.
    // ES: Tasa mínima de modulación en Hz.
    const float maxRateHz = 10.0f; // EN: Maximum modulation rate in Hz.
    // ES: Tasa máxima de modulación en Hz.

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t; // EN: Resets time for the current channel.
        // ES: Reinicia el tiempo para el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i]; // EN: Reads the current audio sample.
            // ES: Lee la muestra de audio actual.
            ratePercentage = targetRatePercentage; // EN: Updates the rate percentage for modulation.
            // ES: Actualiza el porcentaje de velocidad para la modulación.
            float rateHz = minRateHz + ratePercentage * (maxRateHz - minRateHz); // EN: Maps the percentage to Hz.
            // ES: Mapea el porcentaje a Hz.
            float phase = rateHz * t; // EN: Computes the phase based on rate and time.
            // ES: Calcula la fase basada en la velocidad y el tiempo.
            float lfoValue = depth * generateSawtooth(phase) + predelay; // EN: Modulation value with depth and predelay.
            // ES: Valor de modulación con profundidad y pre-delay.
            float fracDelay = static_cast<float>(writterPointer[channel]) - lfoValue; // EN: Fractional delay computation.
            // ES: Cálculo del retraso fraccionado.
            if (fracDelay < 0) fracDelay += circularBufferSize;

            int intDelay = static_cast<int>(fracDelay); // EN: Integer part of the delay.
            // ES: Parte entera del retraso.
            float frac = fracDelay - intDelay; // EN: Fractional part of the delay.
            // ES: Parte fraccionaria del retraso.
            int nextSampleIndex = intDelay + 1; // EN: Index of the next sample in the buffer.
            // ES: Índice de la siguiente muestra en el buffer.
            if (nextSampleIndex >= circularBufferSize) nextSampleIndex = 0;

            float delayedSample = (1.0f - frac) * circularBuffer[intDelay][channel]
                + frac * circularBuffer[nextSampleIndex][channel]; // EN: Linear interpolation of delay samples.
            // ES: Interpolación lineal de las muestras retrasadas.
            circularBuffer[writterPointer[channel]][channel] = sample; // EN: Writes the current sample to the circular buffer.
            // ES: Escribe la muestra actual en el buffer circular.
            writterPointer[channel]++; // EN: Updates the writer pointer for the next sample.
            // ES: Actualiza el puntero de escritura para la siguiente muestra.
            if (writterPointer[channel] >= circularBufferSize) writterPointer[channel] = 0;

            buffer.getWritePointer(channel)[i] = delayedSample; // EN: Writes the processed sample back to the buffer.
            // ES: Escribe la muestra procesada de vuelta al buffer.
            t += 1.0f / sampleRate; // EN: Advances the time variable for the next sample.
            // ES: Avanza la variable de tiempo para la siguiente muestra.
        }
    }
}

// EN: Constructor for the Barberpole Flanger effect.
// ES: Constructor para el efecto Barberpole Flanger.
BarberpoleFlangerFX::BarberpoleFlangerFX() {}

// EN: Destructor for the Barberpole Flanger effect.
// ES: Destructor para el efecto Barberpole Flanger.
BarberpoleFlangerFX::~BarberpoleFlangerFX() {}