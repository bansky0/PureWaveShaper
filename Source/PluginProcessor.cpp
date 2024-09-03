/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PureWaveShaperAudioProcessor::PureWaveShaperAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this,nullptr, "Parameters",createParameters())
#endif
{
}

PureWaveShaperAudioProcessor::~PureWaveShaperAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout PureWaveShaperAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    /*
    parameters.add (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "SliderFloat", 1 }, "SliderFloat", 0.0f, 100.0f, 80.0f));
    parameters.add (std::make_unique<juce::AudioParameterInt>(juce::ParameterID{ "SliderInt", 1 }, "SliderInt", 0, 100, 50));
    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "Button", 1 }, "Button", true));
    parameters.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{ "Options", 1 }, "Options", juce::StringArray{"1/2", "1/4", "1/8", "1/16"},0));
    */
    float pi = juce::MathConstants<float>::pi;

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "input", 1 }, "Input", juce::NormalisableRange<float>(-42.0f, 12.0f, 0.01f), 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "pan", 1 }, "Pan", -100.0f, 100.0f, 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "panLinear", 1 }, "PanLinear", -100.0f, 100.0f, 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "panSqrt", 1 }, "PanSqrt", -100.0f, 100.0f, 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "panSineLaw", 1 }, "PanSineLaw", -100.0f, 100.0f, 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "panSqrtModified", 1 }, "PanSqrtModified", -100.0f, 100.0f, 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "panSineLawModified", 1 }, "PanSineLawModified", -100.0f, 100.0f, 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "rate", 1 }, "Rate", 0.0f, 20.0f, 3.0f));
    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "lfoState", 1 }, "LfoState", true));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "depth", 1 }, "Depth", 0.0f, 100.0f, 50.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "speed", 1 }, "Speed", 0.0f, 20.0f, 3.0f));
    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "ampModulationState", 1 }, "AmpModulationState", true));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "sineWave", 1 }, "SineWave", 20.0f, 400.0f, 100.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "squareWave", 1 }, "SquareWave", 20.0f, 400.0f, 100.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "triangleWave", 1 }, "TriangleWave", 20.0f, 400.0f, 100.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "sawtoothWave", 1 }, "SawtoothWave", 20.0f, 400.0f, 100.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "morphLFO", 1 }, "MorphLFO", 1.0f, 20.0f, 3.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "morphShape", 1 }, "MorphShape", 1.0f, 10.0f, 5.0f)); //used for MorphWave
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "morphWave", 1 }, "MorphWave", 20.0f, 1000.0f, 5.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "depthPan", 1 }, "DepthPan", 0.0f, 100.0f, 50.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "speedPan", 1 }, "SpeedPan", 0.0f, 20.0f, 3.0f));
    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "midSide", 1 }, "MidSide", false));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "stereoImagerWidth", 1 }, "StereoImagerWidth", 0.1f, 2.0f, 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "hardClip", 1 }, "HardClip", juce::NormalisableRange<float>(-42.0f, 0.0f, 0.01f), 0.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "cubicDistortion", 1 }, "CubicDistortion", 0.0f, 1.0f, 0.01f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "arctangentDistortion", 1 }, "ArctangentDistortion", 1.0f, 10.0f, 0.5f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "sineDistortion", 1 }, "sineDistortion", 1.0f, 4.0f, 1.0f));

    return parameters;
}

//==============================================================================
const juce::String PureWaveShaperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PureWaveShaperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PureWaveShaperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PureWaveShaperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PureWaveShaperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PureWaveShaperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PureWaveShaperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PureWaveShaperAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PureWaveShaperAudioProcessor::getProgramName (int index)
{
    return {};
}

void PureWaveShaperAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PureWaveShaperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lfo.prepare(sampleRate);
    ampModulation.prepare(sampleRate);
    sineWave.prepare(sampleRate);
    squareWave.prepare(sampleRate);
    triangleWave.prepare(sampleRate);
    sawtoothWave.prepare(sampleRate);
    morphLFO.prepare(sampleRate);
    morphWave.prepare(sampleRate);
    autoPan.prepare(sampleRate);
}

void PureWaveShaperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PureWaveShaperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PureWaveShaperAudioProcessor::updateParameters() //ACTUALIZA LOS VALORES DE ENTRADA CON EL APVTS
{
    float inInputParameter = *apvts.getRawParameterValue("input");
    float inPanParameter = *apvts.getRawParameterValue("pan");
    float inPanLinearParameter = *apvts.getRawParameterValue("panLinear");
    float inPanSqrtParameter = *apvts.getRawParameterValue("panSqrt");
    float inPanSineLawParameter = *apvts.getRawParameterValue("panSineLaw");
    float inPanSqrtModifiedParameter = *apvts.getRawParameterValue("panSqrtModified");
    float inPanSineLawModifiedParameter = *apvts.getRawParameterValue("panSineLawModified");
    float inRateParameter = *apvts.getRawParameterValue("rate");
    bool inLfoStateParameter = *apvts.getRawParameterValue("lfoState");
    float inDepthValue = *apvts.getRawParameterValue("depth");//using to ampmod and mophLFO
    float inSpeedValue = *apvts.getRawParameterValue("speed");
    bool inAmpModulationStateParameter = *apvts.getRawParameterValue("ampModulationState");
    float inSineWaveValue = *apvts.getRawParameterValue("sineWave");
    float inSquareWaveValue = *apvts.getRawParameterValue("squareWave");
    float inTriangleWaveValue = *apvts.getRawParameterValue("triangleWave");
    float inSawtoothWaveValue = *apvts.getRawParameterValue("sawtoothWave");
    float inMorphLFOValue = *apvts.getRawParameterValue("morphLFO");
    float inMorphShapeValue = *apvts.getRawParameterValue("morphShape");
    float inMorphWaveValue = *apvts.getRawParameterValue("morphWave");
    float inAutoPanDepthValue = *apvts.getRawParameterValue("depthPan");
    float inAutoPanSpeedValue = *apvts.getRawParameterValue("speedPan");
    bool inMidSideState = *apvts.getRawParameterValue("midSide");
    float inStereoImagerWidthValue = *apvts.getRawParameterValue("stereoImagerWidth");
    float inHardClipThreshValue = *apvts.getRawParameterValue("hardClip");
    float inCubicDistortionDriveValue = *apvts.getRawParameterValue("cubicDistortion");
    float inArctangtDistortionValue = *apvts.getRawParameterValue("arctangentDistortion");
    float inSineDistortionValue = *apvts.getRawParameterValue("sineDistortion");

    input.setInputValue(inInputParameter);
    pan.setPanValue(inPanParameter);
    panLinear.setPanLinearValue(inPanLinearParameter);
    panSqrt.setPanSqrtValue(inPanSqrtParameter);
    panSineLaw.setPanSineLawValue(inPanSineLawParameter);
    panSqrtModified.setPanSqrtModidiedValue(inPanSqrtModifiedParameter);
    panSineLawModified.setPanSineLawModifiedValue(inPanSineLawModifiedParameter);
    lfo.setLFOValue(inRateParameter);
    lfoState = inLfoStateParameter;
    ampModulation.setDepth(inDepthValue);
    ampModulation.setSpeed(inSpeedValue);
    ampModulationState = inAmpModulationStateParameter;
    sineWave.setFrequency(inSineWaveValue);
    squareWave.setFrequency(inSquareWaveValue);
    triangleWave.setFrequency(inTriangleWaveValue);
    sawtoothWave.setFrequency(inSawtoothWaveValue);
    morphLFO.setFrequency(inMorphLFOValue);
    morphLFO.setShape(inMorphShapeValue);
    morphLFO.setDepth(inDepthValue);
    morphWave.setShape(inMorphShapeValue);
    morphWave.setFrequency(inMorphWaveValue);
    autoPan.setDepth(inAutoPanDepthValue);
    autoPan.setSpeed(inAutoPanSpeedValue);
    midSideState = inMidSideState;
    stereoImager.setStereoImagerValue(inStereoImagerWidthValue);
    hardClip.setHardClipThresh(inHardClipThreshValue);
    cubicDistortion.setCubicDistortionDrive(inCubicDistortionDriveValue);
    arctangenteDistortion.setArctangentDistortionDrive(inArctangtDistortionValue);
    sineDistortion.setSineDistortionValue(inSineDistortionValue);
}

void PureWaveShaperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    updateParameters();

    input.process(buffer);
    //pan.process(buffer);
    //panLinear.process(buffer);
    //panSqrt.process(buffer);
    //panSineLaw.process(buffer);
    //panSqrtModified.process(buffer);
    //panSineLawModified.process(buffer);
    //sineWave.process(buffer);
    //squareWave.process(buffer);
    //triangleWave.process(buffer);
    //sawtoothWave.process(buffer);
    //morphLFO.process(buffer);
    //morphWave.process(buffer);
    //autoPan.process(buffer);
    //infinitClip.process(buffer);
    //halfWaveRectification.process(buffer);

    if (midSideState)
        //    midSide.process(buffer);
        //    stereoImager.process(buffer);
        //fullWaveRectification.process(buffer);
        //hardClip.process(buffer);
        //cubicDistortion.process(buffer);
        //arctangenteDistortion.process(buffer);
        sineDistortion.process(buffer);
    //if (lfoState)
    //    lfo.process(buffer);
    //if (ampModulationState)
    //    ampModulation.process(buffer);

}

//==============================================================================
bool PureWaveShaperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PureWaveShaperAudioProcessor::createEditor()
{
    //return new PureWaveShaperAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void PureWaveShaperAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(apvts.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PureWaveShaperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(apvts.state.getType()))
        {
            auto state = juce::ValueTree::fromXml(*xmlState);
            apvts.replaceState(state);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PureWaveShaperAudioProcessor();
}
