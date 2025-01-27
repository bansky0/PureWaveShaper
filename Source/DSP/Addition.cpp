/*
  ==============================================================================

    Addition.cpp
    Created: 10 Sep 2024 1:57:19pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Addition.h"

// EN: Sets the frequency of the first oscillator and calculates its phase increment.
// ES: Establece la frecuencia del primer oscilador y calcula su incremento de fase.
void AdditiveSynth::setFrequency1(float inFreqOsc1)
{
    osc1 = inFreqOsc1;
    phaseIncrement1 = twoPi * osc1 / sampleRate;
}

// EN: Sets the amplitude of the first oscillator.
// ES: Establece la amplitud del primer oscilador.
void AdditiveSynth::setAmplitud1(float inAmp1)
{
    amp1 = inAmp1;
}

// EN: Sets the frequency of the second oscillator and calculates its phase increment.
// ES: Establece la frecuencia del segundo oscilador y calcula su incremento de fase.
void AdditiveSynth::setFrequency2(float inFreqOsc2)
{
    osc2 = inFreqOsc2;
    phaseIncrement2 = twoPi * osc2 / sampleRate;
}

// EN: Sets the amplitude of the second oscillator.
// ES: Establece la amplitud del segundo oscilador.
void AdditiveSynth::setAmplitud2(float inAmp2)
{
    amp2 = inAmp2;
}

// EN: Prepares the synthesizer by initializing the sample rate.
// ES: Prepara el sintetizador inicializando la frecuencia de muestreo.
void AdditiveSynth::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

// EN: Processes the audio buffer, generating sound using the two oscillators.
// ES: Procesa el buffer de audio, generando sonido con los dos osciladores.
void AdditiveSynth::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Calculate the output sample by summing the sine waves of both oscillators.
            // ES: Calculamos la muestra de salida sumando las ondas seno de ambos osciladores.
            float outSample = amp1 * sinf(phase1[channel]) + amp2 * sinf(phase2[channel]);

            // EN: Store the calculated sample in the audio buffer.
            // ES: Guardamos la muestra calculada en el buffer de audio.
            buffer.setSample(channel, i, outSample);

            // EN: Increment the phase of the first oscillator, wrapping it within [0, 2π].
            // ES: Incrementamos la fase del primer oscilador y la mantenemos en el rango [0, 2π].
            phase1[channel] += phaseIncrement1;

            if (phase1[channel] >= twoPi)
                phase1[channel] -= twoPi;

            // EN: Increment the phase of the second oscillator, wrapping it within [0, 2π].
            // ES: Incrementamos la fase del segundo oscilador y la mantenemos en el rango [0, 2π].
            phase2[channel] += phaseIncrement2;

            if (phase2[channel] >= twoPi)
                phase2[channel] -= twoPi;
        }
    }
}

// EN: Constructor for the AdditiveSynth class.
// ES: Constructor de la clase AdditiveSynth.
AdditiveSynth::AdditiveSynth()
{
}

// EN: Destructor for the AdditiveSynth class.
// ES: Destructor de la clase AdditiveSynth.
AdditiveSynth::~AdditiveSynth()
{
}