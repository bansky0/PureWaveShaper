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
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "dutyCicleFreq", 1 }, "DutyCicleFreq", 20.0f, 400.0f, 100.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "dutyCicle", 1 }, "DutyCicle", 1.0f, 99.0f, 50.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "triangleWave", 1 }, "TriangleWave", 2.0f, 100.0f, 100.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "triangleWaveWidth", 1 }, "TriangleWaveWidth", 0.0f, 1.0f, 0.5f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "trainImpulse", 1 }, "TrainImpulse", 20.0f, 400.0f, 100.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "sawtoothWave", 1 }, "SawtoothWave", 20.0f, 400.0f, 100.0f));

    //additiveSynthesis, subtractionSynthesis, ringmodulation
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "osc1", 1 }, "Osc1", 20.0f, 400.0f, 300.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "amp1", 1 }, "Amp1", 0.0f, 1.0f, 0.5f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "osc2", 1 }, "Osc2", 20.0f, 400.0f, 100.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "amp2", 1 }, "Amp2", 0.0f, 1.0f, 0.5f));

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
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "exponentialDistortion", 1 }, "ExponentialDistortion", 1.0f, 10.0f, 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "bitReduction", 1 }, "BitReduction", 2.0f, 16.0f, 4.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "asymetricalDistortion", 1 }, "AsymetricalDistortion", -0.7f, 0.7f, 1.0f));
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "delayTime", 1 }, "DelayTime", 0.0f, 1.0f, 0.5f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "delayTime2", 1 }, "DelayTime2", 0.0f, 2.0f, 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "delayBPM", 1 }, "DelayBPM", 30, 120, 90));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "delayBPM2", 1 }, "DelayBPM2", 30, 120, 90));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "delayAmp", 1 }, "DelayAmp", 0.0f, 1.0f , 0.75f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "delayAmp2", 1 }, "DelayAmp2", 0.0f, 1.0f, 0.75f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "delayFeedback", 1 }, "DelayFeedback", 0.0f, 100.0f, 75.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "panDelay", 1 }, "PanDelay", -100.0f, 100.0f, 0.0f));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "filterFIR", 1 }, "FilterFir", 20.0f, 20000.0f, 2000.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "filterQ", 1 }, "FilterQ", 0.1f, 2.0f, 0.707f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "filterGain", 1 }, "FilterGain", 0.1f, 3.0f, 1.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "filterGCoeficient", 1 }, "FilterGCoeficient", -1.0f, 1.0f, 0.707f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "filterGCoeficient2", 1 }, "FilterGCoeficient2", -1.0f, 1.0f, 0.707f));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "vibratoRate", 1 }, "VibratoRate", 1.0f, 100.0f, 50.0f)); // confirmar que trabajen en ms o samples en cada efecto.
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "vibratoDepth", 1 }, "VibratoDepth", 0.5f, 10.0f, 5.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "chorusPredelay", 1 }, "ChorusPredelay", 0.0f, 30.0f, 15.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "feedbackFlanger", 1 }, "FeedbackFlanger", 0.0f, 100.0f, 30.0f));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "semitonesPitch", 1 }, "SemitonesPitch", -12.0f, 12.0f, 0.0f));

    parameters.add(std::make_unique<juce::AudioParameterInt>(juce::ParameterID{ "wetDry", 1 }, "WetDry", 0.0f, 100.0f, 50.0f));

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
    dutyCicleWave.prepare(sampleRate);
    sawtoothWave.prepare(sampleRate);
    triangleWave.prepare(sampleRate);
    impulseTrain.prepare(sampleRate);
    morphLFO.prepare(sampleRate);
    morphWave.prepare(sampleRate);
    autoPan.prepare(sampleRate);
    additiveSynth.prepare(sampleRate);
    subtractionSynth.prepare(sampleRate);
    ringModulation.prepare(sampleRate);
    simpleDelay.prepare(sampleRate);
    simpleDelay2.prepare(sampleRate);
    juce::dsp::ProcessSpec spec;
    simpleDelay3.prepare(sampleRate, samplesPerBlock, spec, getNumInputChannels());
    echoFBF.prepare(sampleRate);
    echoFBF2.prepare(sampleRate, getNumInputChannels());
    echoStereo.prepare(sampleRate, getNumInputChannels());
    pingPongEcho.prepare(sampleRate, getNumInputChannels());
    convolution.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    firLpf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    firLpf2.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirHpf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirApf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirLpf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirLsf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirBpf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirPeak.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirNotch.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirFoLpf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirFoHpf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    iirFoApf.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    biquadApf.prepare(sampleRate);
    biquadBpf.prepare(sampleRate);
    biquadBpf2.prepare(sampleRate);
    biquadHpf.prepare(sampleRate);
    biquadHsf.prepare(sampleRate);
    biquadLpf.prepare(sampleRate);
    biquadLsf.prepare(sampleRate);
    biquadNotch.prepare(sampleRate);
    biquadPeaking.prepare(sampleRate);
    biquadIILpf.prepare(sampleRate);
    biquadIIApf.prepare(sampleRate);
    biquadIIBpf.prepare(sampleRate);
    biquadIIHpf.prepare(sampleRate);
    biquadIIHsf.prepare(sampleRate);
    biquadIILsf.prepare(sampleRate);
    biquadIINotch.prepare(sampleRate);
    biquadIIPeaking.prepare(sampleRate);
    biquadTDFIILpf.prepare(sampleRate);
    biquadTDFIIApf.prepare(sampleRate);
    biquadTDFIIBpf.prepare(sampleRate);
    biquadTDFIIHpf.prepare(sampleRate);
    biquadTDFIIHsf.prepare(sampleRate);
    biquadTDFIILsf.prepare(sampleRate);
    biquadTDFIINotch.prepare(sampleRate);
    biquadTDFIIPeaking.prepare(sampleRate);
    slewRateDisto.prepare(sampleRate);
    vibratoExample.prepare(sampleRate);
    vibratoEffect.prepare(sampleRate);
    chorusEffect.prepare(sampleRate);
    flangerEffect.prepare(sampleRate);
    feedbackFlangerEffect.prepare(sampleRate);
    barberpoleFlangerEffect.prepare(sampleRate);
    barberpoleFlangerEffect2.prepare(sampleRate);
    pitchDown.prepare(sampleRate);
    pitchUp.prepare(sampleRate);
    pitchShifter.prepare(sampleRate);
    modulatedDelay.prepare(sampleRate);
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
    float inDutyCicleFreqValue = *apvts.getRawParameterValue("dutyCicleFreq");
    float inDutyCicle = *apvts.getRawParameterValue("dutyCicle");
    float inTriangleWaveValue = *apvts.getRawParameterValue("triangleWave");
    float inTriangleWaveWidthValue = *apvts.getRawParameterValue("triangleWaveWidth");
    float inImpulseTrainFrqValue = *apvts.getRawParameterValue("trainImpulse");
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
    float inExponentialDistortion = *apvts.getRawParameterValue("exponentialDistortion");
    float inBitReductionValue = *apvts.getRawParameterValue("bitReduction");
    float inDCValue = *apvts.getRawParameterValue("asymetricalDistortion");
    float inWetDryValue = *apvts.getRawParameterValue("wetDry"); 
    //additive synth
    float inOsc1= *apvts.getRawParameterValue("osc1");
    float inAmp1 = *apvts.getRawParameterValue("amp1");
    float inOsc2 = *apvts.getRawParameterValue("osc2");
    float inAmp2 = *apvts.getRawParameterValue("amp2");
    //subtracction synth
    float inOsc1Sub = *apvts.getRawParameterValue("osc1");
    float inAmp1Sub = *apvts.getRawParameterValue("amp1");
    float inOsc2Sub = *apvts.getRawParameterValue("osc2");
    float inAmp2Sub = *apvts.getRawParameterValue("amp2");
    //ringModulation
    float inOsc1Ring = *apvts.getRawParameterValue("osc1");
    float inAmp1Ring = *apvts.getRawParameterValue("amp1");
    float inOsc2Ring = *apvts.getRawParameterValue("osc2");
    float inAmp2Ring = *apvts.getRawParameterValue("amp2");

    float inDelay = *apvts.getRawParameterValue("delayTime");
    float inDelay2 = *apvts.getRawParameterValue("delayTime2");
    float inBPM = *apvts.getRawParameterValue("delayBPM");
    float inBPM2 = *apvts.getRawParameterValue("delayBPM2");
    float inAmpDelay = *apvts.getRawParameterValue("delayAmp");
    float inAmpDelay2 = *apvts.getRawParameterValue("delayAmp2");
    float inFeedbackDelay = *apvts.getRawParameterValue("delayFeedback");
    float inPanDelayValue = *apvts.getRawParameterValue("panDelay");

    float inCutOff = *apvts.getRawParameterValue("filterFIR");
    float inQFilter = *apvts.getRawParameterValue("filterQ");
    float inGainFilter = *apvts.getRawParameterValue("filterGain");
    float inGCoeficient = *apvts.getRawParameterValue("filterGCoeficient");
    float inGCoeficient2 = *apvts.getRawParameterValue("filterGCoeficient2");

    float inRate= *apvts.getRawParameterValue("vibratoRate");
    float inDepth = *apvts.getRawParameterValue("vibratoDepth");
    float inPredelay = *apvts.getRawParameterValue("chorusPredelay");// same values ar used to implment flanger
    float inFeedbackFlanger = *apvts.getRawParameterValue("feedbackFlanger");

    float inSemitones = *apvts.getRawParameterValue("semitonesPitch");

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
    dutyCicleWave.setFrequency(inDutyCicleFreqValue);
    dutyCicleWave.setDutyCycle(inDutyCicle);
    triangleWave.setFrequency(inTriangleWaveValue);
    triangleWave.setWidth(inTriangleWaveWidthValue);
    sawtoothWave.setFrequency(inSawtoothWaveValue);
    impulseTrain.setFrequency(inImpulseTrainFrqValue);
    
    //additive synth
    additiveSynth.setFrequency1(inOsc1);
    additiveSynth.setAmplitud1(inAmp1);
    additiveSynth.setFrequency2(inOsc2);
    additiveSynth.setAmplitud2(inAmp2);

    //subtraction synth
    subtractionSynth.setFrequency1(inOsc1);
    subtractionSynth.setAmplitud1(inAmp1);
    subtractionSynth.setFrequency2(inOsc2);
    subtractionSynth.setAmplitud2(inAmp2);

    //ringModulation
    ringModulation.setFrequency1(inOsc1);
    ringModulation.setAmplitud1(inAmp1);
    ringModulation.setFrequency2(inOsc2);
    ringModulation.setAmplitud2(inAmp2);

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
    exponentialDistortion.setExponentialDistortionValue(inExponentialDistortion);
    numberBitReduction.setBitNumberValue(inBitReductionValue);
    asymetricalDistortion.setDCValue(inDCValue);

    simpleDelay.setDelay(inDelay);
    simpleDelay2.setBPM(inBPM);
    simpleDelay2.setAmpDelay(inAmpDelay);
    simpleDelay2.setFeedback(inFeedbackDelay);

    simpleDelay3.setTimeDelay(inDelay);

    
    echoFBF.setBPM(inBPM);
    echoFBF.setAmpFeedback(inAmpDelay);
    echoFBF.setAmpFordward(inAmpDelay2);
    
    echoFBF2.setBPM(inBPM);
    echoFBF2.setBPMOutput(inBPM2);
    echoFBF2.setAmpFeedback(inAmpDelay);
    echoFBF2.setAmpFordward(inAmpDelay2);
    echoFBF2.setFeedback(inFeedbackDelay);

    echoStereo.setBPM(inBPM, inBPM2);
    echoStereo.setGains(inAmpDelay, inAmpDelay2);
    //echoStereo.setPan(inPanDelayValue);

    pingPongEcho.setBPM(inBPM, inBPM2);
    pingPongEcho.setGains(inAmpDelay, inAmpDelay2);

    firLpf.setCutoffFrequency(inCutOff);
    firLpf2.setCutoffFrequency(inCutOff);
    iirHpf.setCutoffFrequency(inCutOff);
    iirApf.setCutoffFrequency(inCutOff);
    iirLpf.setCutoffFrequency(inCutOff);
    iirLsf.setCutoffFrequency(inCutOff);
    iirLsf.setGain(inGainFilter);
    iirLsf.setQ(inQFilter);
    iirBpf.setCutoffFrequency(inCutOff);
    iirNotch.setCutoffFrequency(inCutOff);
    iirPeak.setCutoffFrequency(inCutOff);
    iirPeak.setGain(inGainFilter);
    iirPeak.setQ(inQFilter);
    iirFoLpf.setCutoffFrequency(inCutOff);
    iirFoHpf.setCutoffFrequency(inCutOff);
    iirFoApf.setCutoffFrequency(inCutOff);
    biquadApf.setFrequency(inCutOff);
    biquadApf.setQ(inQFilter);
    biquadBpf.setFrequency(inCutOff);
    biquadBpf.setQ(inQFilter);
    biquadBpf2.setFrequency(inCutOff);
    biquadBpf2.setQ(inQFilter);
    biquadHpf.setFrequency(inCutOff);
    biquadHpf.setQ(inQFilter);
    biquadHsf.setFrequency(inCutOff);
    biquadHsf.setQ(inQFilter);
    biquadHsf.setGain(inGainFilter);
    biquadLpf.setFrequency(inCutOff);
    biquadLpf.setQ(inQFilter);
    biquadLsf.setFrequency(inCutOff);
    biquadLsf.setQ(inQFilter);
    biquadLsf.setGain(inGainFilter);
    biquadNotch.setFrequency(inCutOff);
    biquadNotch.setQ(inQFilter);
    biquadPeaking.setFrequency(inCutOff);
    biquadPeaking.setQ(inQFilter);
    biquadPeaking.setGain(inGainFilter);
    dfApf.setG(inGCoeficient);
    dfNApf.setG(inGCoeficient, inGCoeficient2);
    biquadIILpf.setFrequency(inCutOff);
    biquadIILpf.setQ(inQFilter);
    biquadIIApf.setFrequency(inCutOff);
    biquadIIApf.setQ(inQFilter);
    biquadIIBpf.setFrequency(inCutOff);
    biquadIIBpf.setQ(inQFilter);
    biquadIIHpf.setFrequency(inCutOff);
    biquadIIHpf.setQ(inQFilter);
    biquadIIHsf.setFrequency(inCutOff);
    biquadIIHsf.setQ(inQFilter);
    biquadIIHsf.setGain(inGainFilter);
    biquadIILsf.setFrequency(inCutOff);
    biquadIILsf.setQ(inQFilter);
    biquadIILsf.setGain(inGainFilter);
    biquadIINotch.setFrequency(inCutOff);
    biquadIINotch.setQ(inQFilter);
    biquadIIPeaking.setFrequency(inCutOff);
    biquadIIPeaking.setQ(inQFilter);
    biquadIIPeaking.setGain(inGainFilter);
    biquadTDFIILpf.setFrequency(inCutOff);
    biquadTDFIILpf.setQ(inQFilter);
    biquadTDFIIApf.setFrequency(inCutOff);
    biquadTDFIIApf.setQ(inQFilter);
    biquadTDFIIBpf.setFrequency(inCutOff);
    biquadTDFIIBpf.setQ(inQFilter);
    biquadTDFIIHpf.setFrequency(inCutOff);
    biquadTDFIIHpf.setQ(inQFilter);
    biquadTDFIIHsf.setFrequency(inCutOff);
    biquadTDFIIHsf.setQ(inQFilter);
    biquadTDFIIHsf.setGain(inGainFilter);
    biquadTDFIILsf.setFrequency(inCutOff);
    biquadTDFIILsf.setQ(inQFilter);
    biquadTDFIILsf.setGain(inGainFilter);
    biquadTDFIINotch.setFrequency(inCutOff);
    biquadTDFIINotch.setQ(inQFilter);
    biquadTDFIIPeaking.setFrequency(inCutOff);
    biquadTDFIIPeaking.setGain(inGainFilter);
    biquadTDFIIPeaking.setQ(inQFilter);
    slewRateDisto.setMaxFreq(inCutOff);

    vibratoExample.setDepth(inDepth);
    vibratoExample.setRate(inRate);
    vibratoEffect.setDepth(inDepth);
    vibratoEffect.setRate(inRate);

    chorusEffect.setDepth(inDepth);
    chorusEffect.setRate(inRate);
    chorusEffect.setPredelay(inPredelay);

    flangerEffect.setDepth(inDepth);
    flangerEffect.setRate(inRate);
    flangerEffect.setPredelay(inPredelay);
    
    feedbackFlangerEffect.setDepth(inDepth);
    feedbackFlangerEffect.setRate(inRate);
    feedbackFlangerEffect.setPredelay(inPredelay);

    barberpoleFlangerEffect.setDepth(inDepth);
    barberpoleFlangerEffect.setRate(inRate);
    barberpoleFlangerEffect.setPredelay(inPredelay);

    barberpoleFlangerEffect2.setDepth(inDepth);
    barberpoleFlangerEffect2.setRate(inRate);
    barberpoleFlangerEffect2.setPredelay(inPredelay);

    pitchShifter.setSemitones(inSemitones);

    modulatedDelay.setDelay(inDelay);
    
    wetDry.setDryWet(inWetDryValue);

}

void PureWaveShaperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    updateParameters();

    dryBuffer.makeCopyOf(buffer);

    input.process(buffer);
    //pan.process(buffer);
    //panLinear.process(buffer);
    //panSqrt.process(buffer);
    //panSineLaw.process(buffer);
    //panSqrtModified.process(buffer);
    //panSineLawModified.process(buffer);
    //sineWave.process(buffer);
    //squareWave.process(buffer);
    //dutyCicleWave.process(buffer);
    //sawtoothWave.process(buffer);
    //triangleWave.process(buffer);
    //impulseTrain.process(buffer);
    //whiteNoise.process(buffer);
    //additiveSynth.process(buffer);
    //subtractionSynth.process(buffer);
    //ringModulation.process(buffer);

    //morphLFO.process(buffer);
    //morphWave.process(buffer);
    //autoPan.process(buffer);
    //infinitClip.process(buffer);
    //halfWaveRectification.process(buffer);

    //if (midSideState)
        //    midSide.process(buffer);
        //    stereoImager.process(buffer);
        //fullWaveRectification.process(buffer);
        //hardClip.process(buffer);
        //cubicDistortion.process(buffer);
        //arctangenteDistortion.process(buffer);
        //sineDistortion.process(buffer);
        //exponentialDistortion.process(buffer);
        //piceWiseOverdrive.process(buffer);
        //diodeClipping.process(buffer);
        //numberBitReduction.process(buffer);
        //asymetricalDistortion.process(buffer);
    
    
    //if (lfoState)
    //    lfo.process(buffer);
    //if (ampModulationState)
    //    ampModulation.process(buffer);
    //simpleDelay.process(buffer);
    //simpleDelay2.process(buffer);
    //simpleDelay3.process(buffer);
    //echoFBF.process(buffer);
    //echoFBF2.process(buffer);
    //echoStereo.process(buffer);
    //pingPongEcho.process(buffer);
    convolution.process(buffer);
    //firLpf.process(buffer);
    //firLpf2.process(buffer);
    //iirHpf.process(buffer);
    //iirApf.process(buffer);
    //iirLpf.process(buffer);
    //iirLsf.process(buffer);
    //iirBpf.process(buffer);
    //iirNotch.process(buffer);
    //iirPeak.process(buffer);
    //iirFoLpf.process(buffer);
    //iirFoHpf.process(buffer);
    //iirFoApf.process(buffer);
    //biquadApf.process(buffer);
    //biquadBpf.process(buffer);
    //biquadBpf2.process(buffer);
    //biquadHpf.process(buffer);
    //biquadHsf.process(buffer);
    //biquadLpf.process(buffer);
    //biquadLsf.process(buffer);
    //biquadNotch.process(buffer);
    //biquadPeaking.process(buffer);
    //dfApf.process(buffer);
    //dfNApf.process(buffer);
    //biquadIILpf.process(buffer);
    //biquadIIApf.process(buffer);
    //biquadIIBpf.process(buffer);
    //biquadIIHpf.process(buffer);
    //biquadIIHsf.process(buffer);
    //biquadIILsf.process(buffer);
    //biquadIINotch.process(buffer);
    //biquadIIPeaking.process(buffer);
    //biquadTDFIILpf.process(buffer);
    //biquadTDFIIApf.process(buffer);
    //biquadTDFIIBpf.process(buffer);
    //biquadTDFIIHpf.process(buffer);
    //biquadTDFIIHsf.process(buffer);
    //biquadTDFIILsf.process(buffer);
    //biquadTDFIINotch.process(buffer);
    //biquadTDFIIPeaking.process(buffer);
    //slewRateDisto.process(buffer);
    //vibratoExample.process(buffer);
    //vibratoEffect.process(buffer);
    //chorusEffect.process(buffer);
    //flangerEffect.process(buffer);
    //feedbackFlangerEffect.process(buffer);
    //barberpoleFlangerEffect.process(buffer);
    //barberpoleFlangerEffect2.process(buffer);
    //pitchDown.process(buffer);
    //pitchUp.process(buffer);
    //pitchShifter.process(buffer);
    //modulatedDelay.process(buffer);

    wetDry.process(dryBuffer, buffer);

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
