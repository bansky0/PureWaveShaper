/*
  ==============================================================================

    EchoFeedBackAndFordward.cpp
    Created: 19 Sep 2024 11:16:08am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "EchoFeedBackAndFordward.h"

// EN: Prepares the effect with the provided sample rate.
// ES: Prepara el efecto con la frecuencia de muestreo proporcionada.
void EchoFBF::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

// EN: Sets the delay time based on the tempo (BPM).
// ES: Establece el tiempo de retardo basado en el tempo (BPM).
void EchoFBF::setBPM(float BPM)
{
    float beatsPerMin = BPM;                 // EN: Beats per minute.
                                             // ES: Latidos por minuto.
    float beatsPerSec = beatsPerMin / 60;    // EN: Convert BPM to beats per second.
                                             // ES: Convierte BPM a latidos por segundo.
    float secPerBeat = 1 / beatsPerSec;      // EN: Seconds per beat.
                                             // ES: Segundos por latido.
    float noteDiv = 1;                       // EN: Note division factor (e.g., 1 for quarter notes).
                                             // ES: Factor de división de notas (ej., 1 para negras).
    auto timeSec = noteDiv * secPerBeat;     // EN: Total delay time in seconds.
                                             // ES: Tiempo total de retardo en segundos.
    delay = static_cast<int>(std::floor(timeSec * sampleRate)); // EN: Convert delay to samples.
                                                                // ES: Convierte el retardo a muestras.
}

// EN: Sets the forward gain coefficient.
// ES: Establece el coeficiente de ganancia para el forward.
void EchoFBF::setAmpFordward(float inAmpFordward)
{
    bM = inAmpFordward;
}

// EN: Sets the feedback gain coefficient.
// ES: Establece el coeficiente de ganancia para el feedback.
void EchoFBF::setAmpFeedback(float inAmpFeedback)
{
    aW = inAmpFeedback;
}

// EN: Processes the audio buffer, applying the feedback and forward echo effect.
// ES: Procesa el buffer de audio aplicando el efecto de eco con feedback y forward.
void EchoFBF::process(juce::AudioBuffer<float>& buffer)
{
    auto outputCircularBuffer = 0.0f; // EN: Temporary storage for the output sample.
    // ES: Almacenamiento temporal para la muestra de salida.

// EN: Iterate through each channel in the audio buffer.
// ES: Iterar a través de cada canal en el buffer de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Iterate through each sample in the current channel.
        // ES: Iterar a través de cada muestra en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (delay >= 1) // EN: Process only if the delay is valid.
                // ES: Procesar solo si el retardo es válido.
            {
                auto currentSample = buffer.getReadPointer(channel)[i]; // EN: Read the current sample.
                // ES: Leer la muestra actual.

// EN: Calculate the position for x[n - dM] (delayed input).
// ES: Calcular la posición para x[n - dM] (entrada retrasada).
                int readerPointerInput = writterPointer[channel] - delay;
                if (readerPointerInput < 0)
                {
                    readerPointerInput += circularBufferSize; // EN: Wrap around if pointer is negative.
                    // ES: Envolver si el puntero es negativo.
                }
                float delayedInputSample = circularBuffer[readerPointerInput][channel]; // EN: Delayed input sample.
                // ES: Muestra de entrada retrasada.

// EN: Calculate the position for y[n - dW] (delayed output).
// ES: Calcular la posición para y[n - dW] (salida retrasada).
                int readerPointerOutput = writterPointer[channel] - (delay / 2);
                if (readerPointerOutput < 0)
                {
                    readerPointerOutput += circularBufferSize; // EN: Wrap around if pointer is negative.
                    // ES: Envolver si el puntero es negativo.
                }
                float delayedOutputSample = circularBuffer[readerPointerOutput][channel]; // EN: Delayed output sample.
                // ES: Muestra de salida retrasada.

// EN: Apply the echo formula:
//     y[n] = b0⋅x[n] + bM⋅x[n−dM] − aW⋅y[n−dW]
// ES: Aplicar la fórmula del eco:
//     y[n] = b0⋅x[n] + bM⋅x[n−dM] − aW⋅y[n−dW]
                float outputSample = b0 * currentSample +
                    bM * delayedInputSample -
                    aW * delayedOutputSample;

                // EN: Store the output sample in the circular buffer.
                // ES: Almacenar la muestra de salida en el buffer circular.
                circularBuffer[writterPointer[channel]][channel] = outputSample;

                // EN: Increment the write pointer and wrap around if necessary.
                // ES: Incrementar el puntero de escritura y envolver si es necesario.
                writterPointer[channel]++;
                if (writterPointer[channel] >= circularBufferSize)
                {
                    writterPointer[channel] = 0;
                }

                // EN: Write the processed sample to the audio buffer.
                // ES: Escribir la muestra procesada en el buffer de audio.
                buffer.getWritePointer(channel)[i] = outputSample;
            }
        }
    }
}

// Constructor
// EN: Initializes the EchoFBF object with default values.
// ES: Inicializa el objeto EchoFBF con valores predeterminados.
EchoFBF::EchoFBF()
{
}

// Destructor
// EN: Cleans up resources (none in this case).
// ES: Libera recursos (ninguno en este caso).
EchoFBF::~EchoFBF()
{
}
