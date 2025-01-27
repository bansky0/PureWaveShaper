/*
  ==============================================================================

    StereoImager.h
    Created: 31 Aug 2024 11:53:59am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: A class for implementing a stereo imaging effect that adjusts the stereo width of audio.
// ES: Una clase para implementar un efecto de imagen estéreo que ajusta el ancho estéreo del audio.
class StereoImager
{
public:
    // EN: Sets the stereo width value. A higher value widens the stereo image, while a lower value narrows it.
    // ES: Establece el valor del ancho estéreo. Un valor más alto amplía la imagen estéreo, mientras que un valor más bajo la estrecha.
    void setStereoImagerValue(float inStereoImagerWidthValue);

    // EN: Processes the audio buffer to apply the stereo imaging effect.
    // ES: Procesa el buffer de audio para aplicar el efecto de imagen estéreo.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for initializing the StereoImager class.
    // ES: Constructor para inicializar la clase StereoImager.
    StereoImager();

    // EN: Destructor for cleaning up any resources used by the StereoImager class.
    // ES: Destructor para liberar cualquier recurso utilizado por la clase StereoImager.
    ~StereoImager();

private:
    // EN: The value representing the width of the stereo image. Default is 0.0 (no stereo width adjustment).
    // ES: El valor que representa el ancho de la imagen estéreo. Por defecto es 0.0 (sin ajuste de ancho estéreo).
    float widthValue{ 0.0f };
};