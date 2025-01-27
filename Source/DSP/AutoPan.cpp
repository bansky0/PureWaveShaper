/*
  ==============================================================================

    AutoPan.cpp
    Created: 30 Aug 2024 12:13:48pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "AutoPan.h"

// EN: Sets the depth value for the auto-pan effect, controlling how much the volume modulation affects the channels.
// ES: Configura el valor de profundidad para el efecto de auto-pan, controlando cuánto afecta la modulación de volumen a los canales.
void AutoPan::setDepth(float inDepthValue)
{
    depthValue = inDepthValue;  // EN: Assigns the depth value (0-100). | ES: Asigna el valor de profundidad (0-100).
}

// EN: Sets the speed value for the auto-pan effect, which determines the rate of modulation.
// ES: Configura el valor de velocidad para el efecto de auto-pan, que determina la tasa de modulación.
void AutoPan::setSpeed(float inSpeedValue)
{
    speedValue = inSpeedValue;  // EN: Assigns the speed value (0-20 Hz). | ES: Asigna el valor de velocidad (0-20 Hz).
}

// EN: Prepares the auto-pan effect by setting the sample rate and initializing time-related parameters.
// ES: Prepara el efecto de auto-pan configurando la tasa de muestreo e inicializando los parámetros relacionados con el tiempo.
void AutoPan::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);  // EN: Stores the sample rate as a float. | ES: Almacena la tasa de muestreo como un float.

    for (int i = 0; i < 2; i++)  // EN: Initializes time and delta time for both channels. | ES: Inicializa el tiempo y el delta de tiempo para ambos canales.
    {
        time[i] = 0.0f;
        deltTime[i] = 1.0f / sampleRate;  // EN: Delta time is the reciprocal of the sample rate. | ES: Delta de tiempo es el recíproco de la tasa de muestreo.
    }
}

// EN: Processes the audio buffer, applying the auto-pan effect by modulating the amplitude of each channel based on a sine wave.
// ES: Procesa el buffer de audio, aplicando el efecto de auto-pan modulando la amplitud de cada canal basado en una onda sinusoidal.
void AutoPan::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)  // EN: Loops through each channel in the buffer. | ES: Recorre cada canal en el buffer.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)  // EN: Loops through each sample in the buffer. | ES: Recorre cada muestra en el buffer.
        {
            float sample = buffer.getSample(channel, i);  // EN: Gets the current sample from the buffer. | ES: Obtiene la muestra actual del buffer.

            // EN: Calculates modulation parameters for the sine wave.
            // ES: Calcula los parámetros de modulación para la onda sinusoidal.
            float amplitude = 0.5f * (depthValue / 100.0f);  // EN: Depth controls the modulation intensity. | ES: Depth controla la intensidad de la modulación.
            float offset = 1.0f - amplitude;  // EN: Offset ensures a minimum modulation level. | ES: Offset asegura un nivel mínimo de modulación.
            float phi = 0.0f;  // EN: Phase offset for the sine wave. | ES: Desplazamiento de fase para la onda sinusoidal.
            float f = speedValue;  // EN: Frequency of the modulation in Hz. | ES: Frecuencia de la modulación en Hz.

            // EN: Calculates the sine wave for modulation, using the current time and frequency.
            // ES: Calcula la onda sinusoidal para la modulación, usando el tiempo actual y la frecuencia.
            float sw = sinf(2.0f * pi * f * time[channel] + phi);

            // EN: Computes the modulation factor for this sample.
            // ES: Calcula el factor de modulación para esta muestra.
            float mod = (amplitude * sw) + offset;

            // EN: Modulates the left channel by reducing volume as the sine wave decreases.
            // ES: Modula el canal izquierdo reduciendo el volumen a medida que la onda sinusoidal disminuye.
            if (channel == 0)
            {
                sample *= powf(1 - mod, 0.75f);
            }
            // EN: Modulates the right channel by increasing volume as the sine wave increases.
            // ES: Modula el canal derecho aumentando el volumen a medida que la onda sinusoidal aumenta.
            else
            {
                sample *= powf(mod, 0.75f);
            }

            buffer.setSample(channel, i, sample);  // EN: Writes the modulated sample back to the buffer. | ES: Escribe la muestra modulada de vuelta en el buffer.

            time[channel] += deltTime[channel];  // EN: Advances the time for the current channel. | ES: Avanza el tiempo para el canal actual.

            // EN: Resets time to prevent overflow when it reaches 1 second.
            // ES: Reinicia el tiempo para prevenir desbordamientos cuando alcanza 1 segundo.
            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

// EN: Constructor for the AutoPan class. Initializes default values.
// ES: Constructor de la clase AutoPan. Inicializa valores predeterminados.
AutoPan::AutoPan()
{
}

// EN: Destructor for the AutoPan class. Cleans up resources if necessary.
// ES: Destructor de la clase AutoPan. Libera recursos si es necesario.
AutoPan::~AutoPan()
{
}