/*
  ==============================================================================

    Convolution.cpp
    Created: 26 Sep 2024 10:28:16am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Convolution.h"

// EN: Prepares the convolution processor with the given sample rate, block size, and number of channels.
// ES: Prepara el procesador de convolución con la frecuencia de muestreo, tamaño de bloque y número de canales especificados.
void Convolution::prepare(double inSampleRate, int inSamplesPerblock, int inNumChannels)
{
    // EN: Define the processing specifications (sample rate, block size, number of channels).
    // ES: Define las especificaciones de procesamiento (frecuencia de muestreo, tamaño del bloque, número de canales).
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerblock;
    spec.numChannels = inNumChannels;

    // EN: Resets the convolution processor to its initial state.
    // ES: Restaura el procesador de convolución a su estado inicial.
    convolution.reset();

    // EN: Prepares the convolution processor with the defined specifications.
    // ES: Prepara el procesador de convolución con las especificaciones definidas.
    convolution.prepare(spec);

    // EN: Loads an impulse response from a binary resource to configure the convolution effect.
    // ES: Carga una respuesta al impulso desde un recurso binario para configurar el efecto de convolución.
    convolution.loadImpulseResponse(BinaryData::Taylor_314ce__DPA_4011_wav,    // EN: Impulse response file. | ES: Archivo de respuesta al impulso.
        BinaryData::Taylor_314ce__DPA_4011_wavSize, // EN: Size of the impulse response file. | ES: Tamaño del archivo de respuesta al impulso.
        juce::dsp::Convolution::Stereo::yes,       // EN: Enable stereo processing. | ES: Habilitar procesamiento estéreo.
        juce::dsp::Convolution::Trim::yes,         // EN: Trim silent portions of the IR. | ES: Recortar partes silenciosas de la IR.
        0,                                         // EN: Pre-delay in samples. | ES: Pre-retardo en muestras.
        juce::dsp::Convolution::Normalise::yes);   // EN: Normalize the IR. | ES: Normalizar la IR.
}

// EN: Processes the input audio buffer using the convolution effect.
// ES: Procesa el buffer de audio de entrada utilizando el efecto de convolución.
void Convolution::process(juce::AudioBuffer<float> inBuffer)
{
    // EN: Wrap the audio buffer into an AudioBlock for JUCE's DSP processing.
    // ES: Envuelve el buffer de audio en un AudioBlock para el procesamiento DSP de JUCE.
    juce::dsp::AudioBlock<float> block(inBuffer);

    // EN: Define a processing context that replaces the input audio with the processed audio.
    // ES: Define un contexto de procesamiento que reemplaza el audio de entrada con el audio procesado.
    juce::dsp::ProcessContextReplacing<float> context(block);

    // EN: Apply the convolution effect to the audio buffer.
    // ES: Aplica el efecto de convolución al buffer de audio.
    convolution.process(context);
}

// EN: Constructor for the Convolution class.
// ES: Constructor de la clase Convolution.
Convolution::Convolution()
{
}

// EN: Destructor for the Convolution class.
// ES: Destructor de la clase Convolution.
Convolution::~Convolution()
{
}