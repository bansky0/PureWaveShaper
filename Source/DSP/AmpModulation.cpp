/*
  ==============================================================================

    AmpModulation.cpp
    Created: 27 Aug 2024 2:40:42pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "AmpModulation.h"

void AmpModulation::setDepth(float inDepthValue)
{
    // EN: Sets the modulation depth, which controls how much the amplitude will vary.
    // ES: Establece la profundidad de modulación, que controla cuánto variará la amplitud.
    depthValue = inDepthValue;
}

void AmpModulation::setSpeed(float inSpeedValue)
{
    // EN: Sets the speed (frequency) of the modulation, controlling how fast the amplitude changes over time.
    // ES: Establece la velocidad (frecuencia) de la modulación, controlando qué tan rápido cambia la amplitud con el tiempo.
    speedValue = inSpeedValue;
}

void AmpModulation::prepare(double theSampleRate)
{
    // EN: Prepares the modulation by setting the sample rate and initializing timing variables.
    // ES: Prepara la modulación configurando la frecuencia de muestreo e inicializando las variables de tiempo.
    sampleRate = static_cast<float>(theSampleRate);

    // EN: Initializes the time and delta time for both channels (assumed to be stereo, so two channels).
    // ES: Inicializa el tiempo y el delta de tiempo para ambos canales (se asume estéreo, por lo que hay dos canales).
    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltTime[i] = 1.0f / sampleRate; // EN: Sets the time step based on the sample rate. | ES: Ajusta el paso de tiempo basado en la frecuencia de muestreo.
    }
}

void AmpModulation::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Loops through each audio channel.
    // ES: Recorre cada canal de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Loops through each audio sample in the current channel.
        // ES: Recorre cada muestra de audio en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Reads the input sample from the audio buffer.
            // ES: Lee la muestra de entrada del buffer de audio.
            float inSample = buffer.getSample(channel, i);

            // EN: Calculates the amplitude modulation depth and offset.
            //     The modulation depth is scaled down to be between 0 and 0.5.
            // ES: Calcula la profundidad de modulación de amplitud y el offset.
            //     La profundidad de modulación se escala para estar entre 0 y 0.5.
            float amplitud = 0.5f * (depthValue / 100.0f);
            float offset = 1.0f - amplitud;

            // EN: Initializes the phase (phi) and the modulation frequency (f).
            // ES: Inicializa la fase (phi) y la frecuencia de modulación (f).
            float phi = 0.0f;
            float f = speedValue;

            // EN: Applies the sine wave modulation (sw), using the time value for the current channel.
            // ES: Aplica la modulación con una onda sinusoidal (sw), usando el valor de tiempo del canal actual.
            float sw = sinf(2.0f * pi * f * time[channel] + phi);

            // EN: Computes the modulation value (mod) by applying the sine wave to the amplitude and adding the offset.
            // ES: Calcula el valor de modulación (mod) aplicando la onda sinusoidal a la amplitud y sumando el offset.
            float mod = (amplitud * sw) + offset;

            // EN: Modulates the input sample by multiplying it with the modulation value.
            // ES: Modula la muestra de entrada multiplicándola con el valor de modulación.
            float outSample = inSample * mod;

            // EN: Writes the modulated sample back to the buffer.
            // ES: Escribe la muestra modulada de nuevo al buffer.
            buffer.setSample(channel, i, outSample);

            // EN: Advances the time for the current channel.
            // ES: Avanza el tiempo para el canal actual.
            time[channel] += deltTime[channel];

            // EN: If the time exceeds 1.0 (a full cycle), it resets to 0.
            // ES: Si el tiempo excede 1.0 (un ciclo completo), se reinicia a 0.
            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

// Constructor of the class
// EN: Initializes the amplitude modulation object.
// ES: Inicializa el objeto de modulación de amplitud.
AmpModulation::AmpModulation()
{
}

// Destructor of the class
// EN: Destroys the amplitude modulation object.
// ES: Destruye el objeto de modulación de amplitud.
AmpModulation::~AmpModulation()
{
}