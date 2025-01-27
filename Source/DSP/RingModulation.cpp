/*
  ==============================================================================

    RingModulation.cpp
    Created: 12 Sep 2024 2:55:02pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "RingModulation.h"

// EN: Sets the frequency for the first oscillator and calculates its phase increment.
// ES: Establece la frecuencia para el primer oscilador y calcula su incremento de fase.
void RingModulation::setFrequency1(float inFreqOsc1)
{
    osc1 = inFreqOsc1;
    phaseIncrement1 = twoPi * osc1 / sampleRate;
}

// EN: Sets the amplitude for the first oscillator.
// ES: Establece la amplitud para el primer oscilador.
void RingModulation::setAmplitud1(float inAmp1)
{
    amp1 = inAmp1;
}

// EN: Sets the frequency for the second oscillator and calculates its phase increment.
// ES: Establece la frecuencia para el segundo oscilador y calcula su incremento de fase.
void RingModulation::setFrequency2(float inFreqOsc2)
{
    osc2 = inFreqOsc2;
    phaseIncrement2 = twoPi * osc2 / sampleRate;
}

// EN: Sets the amplitude for the second oscillator.
// ES: Establece la amplitud para el segundo oscilador.
void RingModulation::setAmplitud2(float inAmp2)
{
    amp2 = inAmp2;
}

// EN: Prepares the ring modulation effect by setting the sample rate.
// ES: Prepara el efecto de modulación en anillo estableciendo la frecuencia de muestreo.
void RingModulation::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

// EN: Processes the audio buffer and applies the ring modulation effect.
// ES: Procesa el búfer de audio y aplica el efecto de modulación en anillo.
void RingModulation::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // Loop through each audio channel.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) // Loop through each audio sample.
        {
            // EN: Calculate the output of the sine wave using the current phase values.
            // ES: Calculamos la salida de la onda senoidal usando los valores actuales de la fase.
            float outSample = (amp1 * sinf(phase1[channel])) * (amp2 * sinf(phase2[channel]));

            // EN: Store the calculated sample in the buffer.
            // ES: Guardamos la muestra calculada en el búfer.
            buffer.setSample(channel, i, outSample);

            // EN: Update the phase of the first oscillator and keep it within the range [0, 2PI].
            // ES: Actualizamos la fase del primer oscilador y la mantenemos dentro del rango [0, 2PI].
            phase1[channel] += phaseIncrement1;
            if (phase1[channel] >= twoPi)
                phase1[channel] -= twoPi;

            // EN: Update the phase of the second oscillator and keep it within the range [0, 2PI].
            // ES: Actualizamos la fase del segundo oscilador y la mantenemos dentro del rango [0, 2PI].
            phase2[channel] += phaseIncrement2;
            if (phase2[channel] >= twoPi)
                phase2[channel] -= twoPi;
        }
    }
}

// EN: Constructor for the RingModulation class.
// ES: Constructor de la clase RingModulation.
RingModulation::RingModulation()
{
}

// EN: Destructor for the RingModulation class.
// ES: Destructor de la clase RingModulation.
RingModulation::~RingModulation()
{
}
