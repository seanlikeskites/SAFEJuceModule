#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

// Our editor inherits from SAFEAudioProcessorEditor
class SimpleDistortionAudioProcessorEditor  : public SAFEAudioProcessorEditor
{
public:
    SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor&);
    ~SimpleDistortionAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:
    SimpleDistortionAudioProcessor& processor;

    Label title;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDistortionAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
