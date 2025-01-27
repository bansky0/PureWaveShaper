/*
  ==============================================================================

    PingPongEcho.cpp
    Created: 24 Sep 2024 10:48:08am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "PingPongEcho.h"

// Establecer los tiempos de delay en muestras
// ES: Esta función ajusta los tiempos de delay en función del BPM de cada canal, 
// convirtiéndolos a muestras utilizando la tasa de muestreo.
// EG: This function sets the delay times based on the BPM of each channel, 
// converting them to samples using the sample rate.
void PingPongEcho::setBPM(float BPM1, float BPM2)
{
    // ES: Calcular el tiempo por pulso (segundos) para el primer canal
    // EG: Calculate time per pulse (seconds) for the first channel
    float beatsPerMin1 = BPM1;
    float beatsPerSec1 = beatsPerMin1 / 60.0f;
    float secPerBeat1 = 1.0f / beatsPerSec1;
    float noteDiv1 = 1.0f; // Esto podría ser ajustable para diferentes subdivisiones
    auto timeSec1 = noteDiv1 * secPerBeat1;

    // ES: Convertir el tiempo a muestras
    // EG: Convert time to samples
    delay1Samples = static_cast<int>(std::floor(timeSec1 * sampleRate));

    // ES: Calcular el tiempo por pulso (segundos) para el segundo canal
    // EG: Calculate time per pulse (seconds) for the second channel
    float beatsPerMin2 = BPM2;
    float beatsPerSec2 = beatsPerMin2 / 60.0f;
    float secPerBeat2 = 1.0f / beatsPerSec2;
    float noteDiv2 = 1.0f; // Esto podría ser ajustable para diferentes subdivisiones
    auto timeSec2 = noteDiv2 * secPerBeat2;

    // Convertir el tiempo a muestras
    // Convert time to samples
    delay2Samples = static_cast<int>(std::floor(timeSec2 * sampleRate));
}

// Establecer las ganancias para cada delay
// ES: Esta función permite ajustar la ganancia de cada canal de eco.
// EG: This function allows adjusting the gain for each echo channel.
void PingPongEcho::setGains(float gain1Value, float gain2Value)
{
    gain1 = gain1Value;
    gain2 = gain2Value;
}

// Preparar el procesador de delay
// ES: Esta función prepara los buffers circulares y los punteros para el procesamiento de los delays,
// incluyendo la tasa de muestreo y el número de canales a procesar.
// EG: This function prepares circular buffers and pointers for delay processing, 
// including the sample rate and the number of channels to process.
void PingPongEcho::prepare(double theSampleRate, int inTotalChannels)
{
    sampleRate = theSampleRate;

    // ES: Redimensionar los buffers circulares para los canales
    // EG: Resize circular buffers for the channels
    circularBufferInput1.resize(circularBufferSize, std::vector<float>(inTotalChannels, 0.0f));
    circularBufferInput2.resize(circularBufferSize, std::vector<float>(inTotalChannels, 0.0f));

    // ES: Inicializar los punteros de escritura para cada canal
    // EG: Initialize write pointers for each channel
    writterPointerInput1.resize(inTotalChannels, 0);
    writterPointerInput2.resize(inTotalChannels, 0);
}

// Procesar el buffer de audio
// ES: En esta función se procesa el audio para ambos canales (izquierdo y derecho),
// aplicando el efecto de PingPong Echo con los correspondientes delays y feedbacks cruzados.
// EG: This function processes the audio for both left and right channels, 
// applying the PingPong Echo effect with the corresponding delays and cross-feedbacks.
void PingPongEcho::process(juce::AudioBuffer<float>& buffer)
{
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        // ES: Obtener la señal de entrada de cada canal
        // EG: Get input signal from each channel
        auto leftInput = buffer.getReadPointer(0)[i];  // Canal izquierdo
        auto rightInput = buffer.getReadPointer(1)[i]; // Canal derecho

        // --- Procesamiento del canal izquierdo ---
        // ES: Leer la señal retrasada del canal derecho
        // EG: Read delayed signal from the right channel
        int readerPointerInputLeft = writterPointerInput2[1] - delay1Samples; // Leer del canal derecho
        if (readerPointerInputLeft < 0)
            readerPointerInputLeft += circularBufferSize; // Circularidad del buffer

        // ES: Recuperar la muestra retrasada del canal derecho
        // EG: Retrieve delayed sample from the right channel
        float delayedSampleFromRight = circularBufferInput2[readerPointerInputLeft][1]; // Señal retrasada del derecho
        // ES: Calcular la salida para el canal izquierdo
        // EG: Calculate output for left channel
        float leftOutput = leftInput - gain1 * delayedSampleFromRight; // Canal izquierdo + feedback derecho

        // ES: Guardar la salida procesada en el buffer circular del canal izquierdo
        // EG: Save processed output into the left channel circular buffer
        circularBufferInput1[writterPointerInput1[0]][0] = leftOutput;

        // ES: Avanzar el puntero de escritura del canal izquierdo
        // EG: Move left channel write pointer forward
        writterPointerInput1[0]++;
        if (writterPointerInput1[0] >= circularBufferSize)
            writterPointerInput1[0] = 0;

        // ES: Escribir la salida procesada en el buffer de salida
        // EG: Write processed output to the output buffer
        buffer.getWritePointer(0)[i] = leftOutput;

        // --- Procesamiento del canal derecho ---
        // ES: Leer la señal retrasada del canal izquierdo
        // EG: Read delayed signal from the left channel
        int readerPointerInputRight = writterPointerInput1[0] - delay2Samples; // Leer del canal izquierdo
        if (readerPointerInputRight < 0)
            readerPointerInputRight += circularBufferSize; // Circularidad del buffer

        // ES: Recuperar la muestra retrasada del canal izquierdo
        // EG: Retrieve the delayed sample from the left channel
        float delayedSampleFromLeft = circularBufferInput1[readerPointerInputRight][0]; // Señal retrasada del izquierdo
        // ES: Calcular la salida para el canal derecho
        // EG: Calculate the output for the right channel
        float rightOutput = rightInput - gain2 * delayedSampleFromLeft; // Canal derecho + feedback izquierdo

        // ES: Guardar la salida procesada en el buffer circular del canal derecho
        // EG: Save the processed output into the right channel circular buffer
        circularBufferInput2[writterPointerInput2[1]][1] = rightOutput;

        // ES: Avanzar el puntero de escritura del canal derecho
        // EG: Move the right channel write pointer forward
        writterPointerInput2[1]++;
        if (writterPointerInput2[1] >= circularBufferSize)
            writterPointerInput2[1] = 0;

        // ES: Escribir la salida procesada en el buffer de salida
        // EG: Write the processed output to the output buffer
        buffer.getWritePointer(1)[i] = rightOutput;
    }
}

// Constructor
// ES: Inicializa el objeto PingPongEcho, configurando los valores predeterminados.
// EG: Initializes the PingPongEcho object, setting the default values.
PingPongEcho::PingPongEcho()
{
}

// Destructor
// ES: Libera los recursos utilizados por el objeto PingPongEcho al destruirse.
// EG: Frees the resources used by the PingPongEcho object when destroyed.
PingPongEcho::~PingPongEcho()
{
}