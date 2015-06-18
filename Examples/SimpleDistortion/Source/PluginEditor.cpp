#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDistortionAudioProcessorEditor::SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor& p)
    : SAFEAudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);
}

SimpleDistortionAudioProcessorEditor::~SimpleDistortionAudioProcessorEditor()
{
}

void SimpleDistortionAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void SimpleDistortionAudioProcessorEditor::resized()
{
}
