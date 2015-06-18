#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDistortionAudioProcessor::SimpleDistortionAudioProcessor()
    : threshold (0.5),
      negativeThreshold (-threshold)
{
    // Add some parameters to the plug-in.
    //
    // The variables we declared to hold our parameter values are passed 
    // to the new parameters by reference. This way their values will 
    // be updated whenever the host or user changes a parameter. 
    //
    // addDBParameter() adds a new parameter whose values will be automatically
    // converted from a dB gain to a gain factor we can use in the processing block.
    //
    // Make sure you remember the order you added the parameters in
    // so you can refer to them later. If you have used an enum to label 
    // your parameters, like I did in this plug-in, make sure you add the
    // parameters in the same order they appear in the enum.
    addDBParameter ("Drive", drive, 0, -20, 20, "dB");
    addParameter ("Symmetry", symmetry, 1, 0, 1);
    addDBParameter ("Gain", gain, 0, -20, 20);

    // Add some features to extract.
    //
    // The SAFE JUCE module has LibXtract built in. LibXtract features can
    // be added to a plug-in like so.
    addLibXtractFeature (LibXtract::SpectralCentroid);

    // Extra audio features can be added through the use of vamp
    // plug-ins. These are added using addVampPlugin(). The user needs
    // to have the vamp plug-ins installed to the correct directory
    // on their system for them to be used. If the SAFE plug-in can't
    // find a vamp plug-in on the system it will ignore it.
    //
    // Here we use MTG's HPCP plug-in which can be downloaded here:
    // http://mtg.upf.edu/technologies/hpcp
    addVampPlugin ("vamp-hpcp-mtg", "MTG-HPCP");

    // When making a new SAFE plug-in you need to register the plug-in 
    // in our database. The saveDetailsToXml() function will create
    // an xml file which you will use the register the plug-in. 
    // It is good to wrap it in an '#ifdef JUCE_DEBUG' so that 
    // your release builds won't clutter the users machines with useless
    // xml files.
    //
    // This must be called after the parameters have been added!
#ifdef JUCE_DEBUG
    saveDetailsToXml();
#endif
}

SimpleDistortionAudioProcessor::~SimpleDistortionAudioProcessor()
{
}

void SimpleDistortionAudioProcessor::pluginPreparation (double sampleRate, int samplesPerBlock)
{
    // This function is equivalent to the standard JUCE plug-in
    // prepareToPlay() function. Use it to do any preparation your
    // plug-in needs to do before we start processing audio.
    //
    // We don't actually need to do anything in this plug-in though.
}

void SimpleDistortionAudioProcessor::pluginProcessing (AudioSampleBuffer &buffer, MidiBuffer &midiMessages)
{
    // This function is equivalent to the standard JUCE plug-in
    // processBlock(). Use it to do your plug-in's processing.
    //
    // Parameter values can be accessed using the variables passed
    // to them by reference in the constructor.
    
    // Apply the gain in our drive variable.
    // Note we do not need to convert from dB as we added it as a dB parameter.
    buffer.applyGain (drive);

    // Get info about the amount of audio we have been 
    // given to process.
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();

    // Loop through each channel
    for (int channel = 0; channel < numChannels; ++channel)
    {
        // Get a pointer to the current channel of audio.
        float *audioData = buffer.getWritePointer (channel);

        // Loop through the samples.
        for (int sample = 0; sample < numSamples; ++sample)
        {
            // Clip the audio.
            if (audioData [sample] > threshold)
            {
                audioData [sample] = threshold;
            }
            else if (audioData [sample] < negativeThreshold)
            {
                audioData [sample] = negativeThreshold;
            }
        }
    }

    // Apply the gain in our gain variable.
    buffer.applyGain (gain);
}

void SimpleDistortionAudioProcessor::releaseResources()
{
    // Use this function to release any resources you
    // may have aquired in pluginPreparation().
}

void SimpleDistortionAudioProcessor::parameterUpdateCalculations (int index)
{
    // This function is called whenever a parameter value is changed.
    // Use it to do anything your plug-in needs to when parameters
    // are changed.
    //
    // In this plug-in we need to update the negative threshold whenever 
    // the symmetry changes.
    if (index == ParamSymmetry)
    {
        negativeThreshold = -symmetry * threshold;
    }
}
    
int SimpleDistortionAudioProcessor::getAnalysisFrameSize()
{
    // We can override this function to set a default analysis frame size
    // in samples. The given value should be a power of two.
    //
    // This frame size will be used for any LibXtract features. And any
    // vamp plug-ins which do not give a preferred block size. 
    //
    // All other vamp plug-ins will be set to use their preferred block size.
    //
    // If you do not override this function the default frame size of
    // 4096 samples will be used.
    return 2048;
}

int SimpleDistortionAudioProcessor::getAnalysisStepSize()
{
    // We can override this function to set a default analysis step size
    // in samples.
    //
    // This step size will be used for any LibXtract features. And any
    // vamp plug-ins which do not give a preferred step size. 
    //
    // All other vamp plug-ins will be set to use their preferred step size.
    //
    // If you do not override this function the default step size of
    // 4096 samples will be used.
    return 512;
}
    
String SimpleDistortionAudioProcessor::getPluginCode()
{
    // Because plug-ins use multi-character constants for their
    // unique ids (and I can't be bothered to deal with that) override
    // this function to return your plug-ins code as a string.
    return "SFEX";
}

bool SimpleDistortionAudioProcessor::hasEditor() const
{
    return false;
}

AudioProcessorEditor* SimpleDistortionAudioProcessor::createEditor()
{
    return nullptr;
    //return new SimpleDistortionAudioProcessorEditor (*this);
}

// This creates new instance of the plug-in..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDistortionAudioProcessor();
}
