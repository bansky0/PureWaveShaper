/*
  ==============================================================================

    Subtraction.cpp
    Created: 11 Sep 2024 2:32:06pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Subtraction.h"

// EN: Sets the frequency for the first oscillator and calculates its phase increment.
// ES: Establece la frecuencia para el primer oscilador y calcula su incremento de fase.
void Subtraction::setFrequency1(float inFreqOsc1)
{
    osc1 = inFreqOsc1;
    // EN: Calculate the phase increment for the first oscillator based on its frequency and the sample rate.
    // ES: Calcula el incremento de fase para el primer oscilador en función de su frecuencia y la tasa de muestreo.
    phaseIncrement1 = osc1 * twoPi / sampleRate;

    // Optional alternative calculation method (commented out):
    // Método alternativo opcional para calcular el incremento de fase (comentado):
    // if (sampleRate > 0.0f)
    // {
    //     phaseIncrement1 = 1.0f / (sampleRate / osc1);
    // }
}

// EN: Sets the amplitude for the first oscillator.
// ES: Establece la amplitud para el primer oscilador.
void Subtraction::setAmplitud1(float inAmp1)
{
    amp1 = inAmp1;
}

// EN: Sets the frequency for the second oscillator and calculates its phase increment.
// ES: Establece la frecuencia para el segundo oscilador y calcula su incremento de fase.
void Subtraction::setFrequency2(float inFreqOsc2)
{
    osc2 = inFreqOsc2;
    // EN: Calculate the phase increment for the second oscillator based on its frequency and the sample rate.
    // ES: Calcula el incremento de fase para el segundo oscilador en función de su frecuencia y la tasa de muestreo.
    phaseIncrement2 = osc2 * twoPi / sampleRate;
}

// EN: Sets the amplitude for the second oscillator.
// ES: Establece la amplitud para el segundo oscilador.
void Subtraction::setAmplitud2(float inAmp1)
{
    amp2 = inAmp1;
}

// EN: Prepares the object for audio processing by initializing the sample rate.
// ES: Prepara el objeto para el procesamiento de audio inicializando la tasa de muestreo.
void Subtraction::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

// EN: Processes the audio buffer by generating the output of the two oscillators and applying subtractive synthesis.
// ES: Procesa el buffer de audio generando la salida de los dos osciladores y aplicando síntesis sustractiva.
void Subtraction::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Loop through each audio channel.
    // ES: Itera a través de cada canal de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Loop through each sample in the buffer.
        // ES: Itera a través de cada muestra en el buffer.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Square wave example (commented out).
            // ES: Ejemplo de onda cuadrada (comentado).
            // float outSqrWave = (phase1[channel] < 0.5f) ? 1.0f : -1.0f;

            // EN: Calculate the sine wave output for the first oscillator using its current phase.
            // ES: Calcula la salida de la onda senoidal para el primer oscilador utilizando su fase actual.
            float sw1 = amp1 * sinf(phase1[channel]);

            // EN: Calculate the sine wave output for the second oscillator using its current phase.
            // ES: Calcula la salida de la onda senoidal para el segundo oscilador utilizando su fase actual.
            float sw2 = amp2 * sinf(phase2[channel]);

            // EN: Subtract the output of the first oscillator from the second oscillator.
            // ES: Resta la salida del primer oscilador de la del segundo oscilador.
            float outSample = sw2 - sw1;

            // EN: Store the calculated sample value in the buffer.
            // ES: Almacena el valor calculado de la muestra en el buffer.
            buffer.setSample(channel, i, outSample);

            // EN: Update the phase of the first oscillator and keep it within the range [0, 2PI].
            // ES: Actualiza la fase del primer oscilador y la mantiene dentro del rango [0, 2PI].
            phase1[channel] += phaseIncrement1;

            if (phase1[channel] >= twoPi)
                phase1[channel] -= twoPi;

            // EN: Update the phase of the second oscillator and keep it within the range [0, 2PI].
            // ES: Actualiza la fase del segundo oscilador y la mantiene dentro del rango [0, 2PI].
            phase2[channel] += phaseIncrement2;

            if (phase2[channel] >= twoPi)
                phase2[channel] -= twoPi;
        }
    }
}

// EN: Constructor initializes the `Subtraction` object.
// ES: El constructor inicializa el objeto `Subtraction`.
Subtraction::Subtraction()
{
}

// EN: Destructor cleans up the `Subtraction` object.
// ES: El destructor limpia el objeto `Subtraction`.
Subtraction::~Subtraction()
{
}