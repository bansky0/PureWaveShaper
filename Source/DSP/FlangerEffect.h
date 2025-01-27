/*
  ==============================================================================

    FlangerEffect.h
    Created: 30 Oct 2024 3:56:42pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: FlangerFX class definition for creating a flanger effect with adjustable parameters.
//     The class allows for depth, rate, and predelay adjustment for the effect, and processes the audio buffer.
class FlangerFX
{
public:
    // EN: Constructor for FlangerFX class. Initializes the variables and prepares the flanger effect.
    // ES: Constructor para la clase FlangerFX. Inicializa las variables y prepara el efecto flanger.
    FlangerFX();

    // EN: Destructor for FlangerFX class. Cleans up any resources when the effect is no longer needed.
    // ES: Destructor para la clase FlangerFX. Limpia los recursos cuando el efecto ya no es necesario.
    ~FlangerFX();

    // EN: Prepares the effect by setting the sample rate.
    //     This method should be called before processing audio to configure the necessary settings.
    // ES: Prepara el efecto configurando la frecuencia de muestreo.
    //     Este método debe ser llamado antes de procesar el audio para configurar los ajustes necesarios.
    void prepare(double theSampleRate);

    // EN: Sets the depth of the flanger effect.
    //     Depth determines the intensity of the modulation effect applied to the audio.
    // ES: Establece la profundidad del efecto flanger.
    //     La profundidad determina la intensidad de la modulación aplicada al audio.
    void setDepth(float inDepth);

    // EN: Sets the rate of modulation as a percentage.
    //     The rate determines the speed at which the flanger effect cycles.
    // ES: Establece la tasa de modulación como un porcentaje.
    //     La tasa determina la velocidad a la que el efecto flanger se repite.
    void setRate(float inRatePercentage);

    // EN: Sets the predelay for the flanger effect in milliseconds.
    //     Predelay adjusts the time delay before the effect begins to modulate.
    // ES: Establece el predelay para el efecto flanger en milisegundos.
    //     El predelay ajusta el tiempo de retardo antes de que comience la modulación del efecto.
    void setPredelay(float inPredelayMs);

    // EN: Processes the audio buffer and applies the flanger effect.
    //     The audio buffer is modified in-place with the flanger effect applied.
    // ES: Procesa el búfer de audio y aplica el efecto flanger.
    //     El búfer de audio se modifica en su lugar con el efecto flanger aplicado.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: Sample rate of the audio signal.
    // ES: Frecuencia de muestreo de la señal de audio.
    float sampleRate;

    // EN: Time variable for controlling the position in the modulation cycle.
    // ES: Variable de tiempo para controlar la posición en el ciclo de modulación.
    float t;

    // EN: Depth of the flanger effect.
    // ES: Profundidad del efecto flanger.
    float depth;

    // EN: Rate of the flanger effect, as a percentage.
    // ES: Tasa del efecto flanger, como porcentaje.
    float ratePercentage;

    // EN: Target rate percentage to apply over time, used for smooth transitions.
    // ES: Porcentaje objetivo de tasa a aplicar a lo largo del tiempo, utilizado para transiciones suaves.
    float targetRatePercentage;

    // EN: Predelay time before the effect begins, in milliseconds.
    // ES: Tiempo de predelay antes de que comience el efecto, en milisegundos.
    float predelay;

    // EN: Size of the circular buffer used for storing the delayed samples.
    //     The buffer is used to create the delay effect by storing past audio samples.
    // ES: Tamaño del búfer circular utilizado para almacenar las muestras retardadas.
    //     El búfer se usa para crear el efecto de retardo almacenando muestras de audio pasadas.
    static const int circularBufferSize = 48000;

    // EN: Circular buffer for storing stereo audio data. 
    //     The buffer holds audio data for both the left and right channels.
    // ES: Búfer circular para almacenar datos de audio estéreo.
    //     El búfer almacena datos de audio para los canales izquierdo y derecho.
    float circularBuffer[circularBufferSize][2];

    // EN: Write pointers for both left and right channels, to keep track of the current position in the buffer.
    // ES: Punteros de escritura para los canales izquierdo y derecho, para hacer un seguimiento de la posición actual en el búfer.
    int writterPointer[2] = { 0, 0 };
};
