#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDistortionAudioProcessor::SimpleDistortionAudioProcessor()
{
}

SimpleDistortionAudioProcessor::~SimpleDistortionAudioProcessor()
{
}

void SimpleDistortionAudioProcessor::pluginPreparation (double sampleRate, int samplesPerBlock)
{
}

void SimpleDistortionAudioProcessor::pluginProcessing (AudioSampleBuffer &buffer, MidiBuffer &midiMessages)
{
}

void SimpleDistortionAudioProcessor::releaseResources()
{
}
    
int SimpleDistortionAudioProcessor::getAnalysisFrameSize()
{
    return 2048;
}

int SimpleDistortionAudioProcessor::getAnalysisStepSize()
{
    return 512;
}
    
String SimpleDistortionAudioProcessor::getPluginCode()
{
    return "SFEX";
}

bool SimpleDistortionAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* SimpleDistortionAudioProcessor::createEditor()
{
    return new SimpleDistortionAudioProcessorEditor (*this);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDistortionAudioProcessor();
}
