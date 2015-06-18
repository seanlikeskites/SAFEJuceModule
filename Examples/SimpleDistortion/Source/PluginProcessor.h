#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

// We start by making a class which inherits SAFEAudioProcessor.
class SimpleDistortionAudioProcessor  : public SAFEAudioProcessor
{
public:
    SimpleDistortionAudioProcessor();
    ~SimpleDistortionAudioProcessor();

    void pluginPreparation (double sampleRate, int samplesPerBlock) override;
    void pluginProcessing (AudioSampleBuffer &buffer, MidiBuffer &midiMessages) override;   
    void releaseResources() override;
    
    int getAnalysisFrameSize() override;
    int getAnalysisStepSize() override;
    
    String getPluginCode() override;
    
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

private:
    // Declare some variables which will hold our parameter values
    float drive, symmetry, gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDistortionAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED