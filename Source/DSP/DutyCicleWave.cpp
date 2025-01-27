/*
  ==============================================================================

    DutyCicleWave.cpp
    Created: 9 Sep 2024 1:03:43pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "DutyCicleWave.h"

// EN: Sets the frequency of the waveform and calculates the phase increment.
// ES: Establece la frecuencia de la forma de onda y calcula el incremento de fase.
void DutyCicleWave::setFrequency(double inFrequency)
{
    frequency = inFrequency;

    // EN: Calculate the phase increment based on the frequency and sample rate.
    // ES: Calcula el incremento de fase basado en la frecuencia y la frecuencia de muestreo.
    if (sampleRate > 0.0f)
    {
        phaseIncrement = 1.0f / (sampleRate / frequency);
    }
}

// EN: Sets the duty cycle of the waveform, ensuring it is in the range [0.0, 1.0].
// ES: Establece el ciclo de trabajo de la forma de onda, asegurándose de que esté en el rango [0.0, 1.0].
void DutyCicleWave::setDutyCycle(float inDutyCycle)
{
    // EN: Convert percentage to a normalized value between 0.0 and 1.0.
    // ES: Convierte el porcentaje en un valor normalizado entre 0.0 y 1.0.
    dutyCycle = inDutyCycle / 100.f;
}

// EN: Prepares the waveform generator by setting the sample rate.
// ES: Prepara el generador de formas de onda configurando la frecuencia de muestreo.
void DutyCicleWave::prepare(double theSampleRate)
{
    // EN: Cast sample rate to float for consistent internal calculations.
    // ES: Convierte la frecuencia de muestreo a float para cálculos internos consistentes.
    sampleRate = static_cast<float>(theSampleRate);
}

// EN: Processes the audio buffer by generating a square waveform with the specified duty cycle.
// ES: Procesa el buffer de audio generando una onda cuadrada con el ciclo de trabajo especificado.
void DutyCicleWave::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Loop through each audio channel.
    // ES: Itera por cada canal de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Loop through each sample in the channel.
        // ES: Itera por cada muestra del canal.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Calculate the total period and the active portion based on duty cycle.
            // ES: Calcula el periodo total y la porción activa basada en el ciclo de trabajo.
            float fullPeriodTime = 1.0f / frequency;
            float halfPeriodTime = fullPeriodTime * dutyCycle;

            // EN: Determine the current phase time within the waveform's period.
            // ES: Determina el tiempo actual de la fase dentro del periodo de la forma de onda.
            float localTime = fmod(phase[channel] * fullPeriodTime, fullPeriodTime);

            // EN: Output +1.0 if within the active duty cycle, otherwise -1.0.
            // ES: Produce +1.0 si está dentro del ciclo activo, de lo contrario -1.0.
            float outSample = (localTime < halfPeriodTime) ? 1.0f : -1.0f;

            // EN: Write the generated sample to the buffer.
            // ES: Escribe la muestra generada en el buffer.
            buffer.setSample(channel, i, outSample);

            // EN: Update the phase and wrap it to stay within [0, 1).
            // ES: Actualiza la fase y la ajusta para mantenerse dentro del rango [0, 1).
            phase[channel] += phaseIncrement;
            if (phase[channel] >= 1.0f)
                phase[channel] -= 1.0f;
        }
    }
}

// EN: Constructor - Initializes the class, setting default values for its members.
// ES: Constructor - Inicializa la clase, configurando valores predeterminados para sus miembros.
DutyCicleWave::DutyCicleWave()
{
}

// EN: Destructor - Cleans up any resources (none in this case).
// ES: Destructor - Libera recursos (ninguno en este caso).
DutyCicleWave::~DutyCicleWave()
{
}
