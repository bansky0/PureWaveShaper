/*
  ==============================================================================

    HardClip.h
    Created: 2 Sep 2024 8:43:08pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class for implementing a hard clipping effect, which limits the amplitude of audio samples 
//     to a specified threshold value.
// ES: Clase para implementar un efecto de "hard clipping", que limita la amplitud de las muestras de audio
//     a un valor de umbral especificado.
class HardClip
{
public:
    // EN: Sets the threshold value for the hard clipping effect.
    //     Samples exceeding this value (positive or negative) will be clipped.
    // ES: Establece el valor del umbral para el efecto de "hard clipping".
    //     Las muestras que excedan este valor (positivas o negativas) serán recortadas.
    void setHardClipThresh(float inHardClipThreshValue);

    // EN: Processes an audio buffer by applying the hard clipping effect to each sample.
    // ES: Procesa un búfer de audio aplicando el efecto de "hard clipping" a cada muestra.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the HardClip class. Initializes default values.
    // ES: Constructor de la clase HardClip. Inicializa valores predeterminados.
    HardClip();

    // EN: Destructor for the HardClip class. Cleans up resources if necessary.
    // ES: Destructor de la clase HardClip. Libera recursos si es necesario.
    ~HardClip();

private:
    // EN: Threshold value for the hard clipping effect. Defaults to 0.0f.
    // ES: Valor del umbral para el efecto de "hard clipping". Por defecto es 0.0f.
    float thresh = 0.0f;
};