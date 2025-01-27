/*
  ==============================================================================

    EchoFeedBackAndFordward2.cpp
    Created: 20 Sep 2024 1:29:43pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "EchoFeedBackAndFordward2.h"

// EN: Prepares the delay by initializing the sample rate, circular buffers, and write pointers.
// ES: Prepara el delay inicializando la frecuencia de muestreo, los buffers circulares y los punteros de escritura.
void EchoFBF2::prepare(double theSampleRate, int totalNumChannels)
{
    sampleRate = theSampleRate;

    // EN: Resize the circular buffers to accommodate the specified size and channels.
    // ES: Redimensiona los buffers circulares para ajustarse al tamaño y canales especificados.
    circularBufferInput.resize(circularBufferSize, std::vector<float>(totalNumChannels, 0.0f));
    circularBufferOutput.resize(circularBufferSize, std::vector<float>(totalNumChannels, 0.0f));

    // EN: Initialize the write pointers for each channel.
    // ES: Inicializa los punteros de escritura para cada canal.
    for (int i = 0; i < numChannels; i++)
    {
        writterPointerInput[i] = 0;
        writterPointerOutput[i] = 0;
    }
}

// EN: Sets the delay time for the input buffer based on the BPM.
// ES: Establece el tiempo de delay para el buffer de entrada basado en los BPM.
void EchoFBF2::setBPM(float BPM)
{
    float beatsPerMin = BPM;
    float beatsPerSec = beatsPerMin / 60.0f;
    float secPerBeat = 1.0f / beatsPerSec;
    float noteDiv = 1.0f; // EN: Can be adjusted for note subdivisions. ES: Puede ajustarse para subdivisiones de notas.
    auto timeSec = noteDiv * secPerBeat;

    delayM = static_cast<int>(std::floor(timeSec * sampleRate));
}

// EN: Sets the delay time for the output buffer based on the BPM.
// ES: Establece el tiempo de delay para el buffer de salida basado en los BPM.
void EchoFBF2::setBPMOutput(float BPM)
{
    float beatsPerMin = BPM;
    float beatsPerSec = beatsPerMin / 60.0f;
    float secPerBeat = 1.0f / beatsPerSec;
    float noteDiv = 1.0f; // EN: Can also be adjusted for subdivisions. ES: También puede ajustarse para subdivisiones.
    auto timeSec = noteDiv * secPerBeat;

    delayW = static_cast<int>(std::floor(timeSec * sampleRate));
}

// EN: Sets the forward gain coefficient (bM).
// ES: Establece el coeficiente de ganancia forward (bM).
void EchoFBF2::setAmpFordward(float inAmpFordward)
{
    bM = inAmpFordward;
}

// EN: Sets the feedback gain coefficient (aW).
// ES: Establece el coeficiente de ganancia feedback (aW).
void EchoFBF2::setAmpFeedback(float inAmpFeedback)
{
    aW = inAmpFeedback;
}

// EN: Sets the overall feedback level (scaled to a percentage).
// ES: Establece el nivel general de feedback (escalado a un porcentaje).
void EchoFBF2::setFeedback(float inFeedback)
{
    feedback = inFeedback / 100.0f;
}

// EN: Processes the audio buffer, applying the delay effect with feedback and forward components.
// ES: Procesa el buffer de audio aplicando el efecto de delay con componentes feedback y forward.
void EchoFBF2::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (delayM >= 1 && delayW >= 1) // EN: Only process if delays are valid. ES: Procesa solo si los retardos son válidos.
            {
                auto sampleInput = buffer.getReadPointer(channel)[i];

                // EN: Calculate the read pointer for the input delay (x[n - dM]).
                // ES: Calcula el puntero de lectura para el retardo de entrada (x[n - dM]).
                int readerPointerInput = writterPointerInput[channel] - delayM;
                if (readerPointerInput < 0)
                    readerPointerInput += circularBufferSize;

                float delayedSampleInput = circularBufferInput[readerPointerInput][channel];

                // EN: Calculate the read pointer for the output delay (y[n - dW]).
                // ES: Calcula el puntero de lectura para el retardo de salida (y[n - dW]).
                int readerPointerOutput = writterPointerOutput[channel] - delayW;
                if (readerPointerOutput < 0)
                    readerPointerOutput += circularBufferSize;

                float delayedSampleOutput = circularBufferOutput[readerPointerOutput][channel];

                // EN: Apply the delay formula: y[n] = b0 * x[n] + bM * x[n - dM] - aW * y[n - dW].
                // ES: Aplica la fórmula del delay: y[n] = b0 * x[n] + bM * x[n - dM] - aW * y[n - dW].
                float output = b0 * sampleInput + bM * delayedSampleInput - aW * delayedSampleOutput;

                // EN: Store the input sample with feedback in the circular input buffer.
                // ES: Almacena la muestra de entrada con feedback en el buffer circular de entrada.
                circularBufferInput[writterPointerInput[channel]][channel] = sampleInput + delayedSampleInput * feedback;

                // EN: Store the processed output sample in the circular output buffer.
                // ES: Almacena la muestra de salida procesada en el buffer circular de salida.
                circularBufferOutput[writterPointerOutput[channel]][channel] = output;

                // EN: Advance the write pointers for input and output buffers.
                // ES: Avanza los punteros de escritura para los buffers de entrada y salida.
                writterPointerInput[channel]++;
                if (writterPointerInput[channel] >= circularBufferSize)
                    writterPointerInput[channel] = 0;

                writterPointerOutput[channel]++;
                if (writterPointerOutput[channel] >= circularBufferSize)
                    writterPointerOutput[channel] = 0;

                // EN: Write the processed output to the audio buffer.
                // ES: Escribe la salida procesada en el buffer de audio.
                buffer.getWritePointer(channel)[i] = output;
            }
        }
    }
}

// EN: Constructor (empty, default initialization done in the class definition).
// ES: Constructor (vacío, la inicialización predeterminada se realiza en la definición de la clase).
EchoFBF2::EchoFBF2()
{
}

// EN: Destructor (no specific cleanup needed here).
// ES: Destructor (no se necesita limpieza específica aquí).
EchoFBF2::~EchoFBF2()
{
}
