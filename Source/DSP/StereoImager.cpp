/*
  ==============================================================================

    StereoImager.cpp
    Created: 31 Aug 2024 11:53:59am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "StereoImager.h"

// EN: Sets the width of the stereo image by storing the input value in the `widthValue` variable.
// ES: Establece el ancho de la imagen estéreo almacenando el valor de entrada en la variable `widthValue`.
void StereoImager::setStereoImagerValue(float inStereoImagerWidthValue)
{
    widthValue = inStereoImagerWidthValue;
}

// EN: Processes the audio buffer to apply the stereo imaging effect.
// ES: Procesa el buffer de audio para aplicar el efecto de imagen estéreo.
void StereoImager::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Ensure there are at least two channels (stereo). If not, exit the function.
    // ES: Asegura que haya al menos dos canales (estéreo). Si no, sale de la función.
    if (buffer.getNumChannels() < 2)
        return;

    // EN: Iterate over each sample in the buffer.
    // ES: Itera sobre cada muestra en el buffer.
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        // EN: Get the left and right channel samples.
        // ES: Obtiene las muestras de los canales izquierdo y derecho.
        float left = buffer.getSample(0, i);
        float right = buffer.getSample(1, i);

        // EN: Encode the left and right channels into mid/side representation.
        // Mid is the average of left and right, and side is the difference.
        // ES: Codifica los canales izquierdo y derecho en representación mid/side.
        // Mid es el promedio de izquierdo y derecho, y side es la diferencia.
        float mid = 0.5f * (left + right);
        float side = 0.5f * (left - right);

        // EN: Process the mid/side signals based on the `widthValue`.
        // `newMid` reduces the mid signal as width increases.
        // `newSide` amplifies the side signal as width increases.
        // ES: Procesa las señales mid/side en función de `widthValue`.
        // `newMid` reduce la señal mid a medida que aumenta el ancho.
        // `newSide` amplifica la señal side a medida que aumenta el ancho.
        float newMid = (2.0f - widthValue) * mid;
        float newSide = widthValue * side;

        // EN: Decode the processed mid/side signals back into left and right channels.
        // ES: Decodifica las señales mid/side procesadas de nuevo en canales izquierdo y derecho.
        float newLeft = newMid + newSide;
        float newRight = newMid - newSide;

        // EN: Write the processed samples back to the buffer.
        // You could also choose to output only the mid, side, or other processed signals if needed.
        // ES: Escribe las muestras procesadas de vuelta en el buffer.
        // También se podría elegir salir solo con mid, side u otras señales procesadas si es necesario.
        buffer.setSample(0, i, newLeft);
        buffer.setSample(1, i, newRight);
    }
}

// EN: Constructor initializes the StereoImager object.
// ES: El constructor inicializa el objeto StereoImager.
StereoImager::StereoImager()
{
}

// EN: Destructor cleans up any resources used by the StereoImager object.
// ES: El destructor limpia cualquier recurso utilizado por el objeto StereoImager.
StereoImager::~StereoImager()
{
}