#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDistortionAudioProcessorEditor::SimpleDistortionAudioProcessorEditor (SimpleDistortionAudioProcessor& p)
    : SAFEAudioProcessorEditor (&p), processor (p),
      title ("", "Distortion")
{
    // Start by setting the size of our editor. Remember to make
    // it large enough for the extra screens to fit (they are 390 by 295 pixels).
    int width = 400;
    int height = 340;
    setSize (width, height);

    // Some variables for positioning the sliders.
    int spacing = 10;
    int sliderWidth = 80;
    int sliderHeight = 100;
    int sliderY = spacing;

    // Here we loop through our parameter sliders and add them to the interface.
    for (int i = 0; i < sliders.size(); ++i)
    {
        // The sliders all live in the sliders array.
        // They are in the same order they were added to the processor.
        SAFESlider *currentSlider = sliders [i];

        // Add the slider to the interface.
        addAndMakeVisible (currentSlider);
        currentSlider->setBounds (spacing, sliderY, sliderWidth, sliderHeight);
        currentSlider->setColour (SAFEColours::green);

        sliderY += spacing + sliderHeight;
    }

    // The SAFEAudioProcessorEditor class will automatically label
    // the sliders with the parameter names you gave. These may be too 
    // long (as with the name 'symmetry') so we can set the text explicitly.
    //
    // Note the use of the enum from our processor to index the slider array.
    // Much more readable than using magic numbers.
    sliders [SimpleDistortionAudioProcessor::ParamSymmetry]->setText ("Symm");

    // Some variables for positioning the load and record buttons.
    int longButtonWidth = 100;
    int longButtonHeight = 22;
    int longButtonY = height - spacing - longButtonHeight;

    // The loadButton is a protected member of SAFEAudioProcessorEditor which
    // will bring up an extra screen for loading semantic terms.
    addAndMakeVisible (loadButton);
    int loadButtonX = width - spacing - longButtonWidth;
    loadButton.setBounds (loadButtonX, longButtonY, longButtonWidth, longButtonHeight);
    
    // The recordButton is a protected member of SAFEAudioProcessorEditor which
    // starts the analysis of the audio.
    addAndMakeVisible (recordButton);
    int recordButtonX = loadButtonX - spacing - longButtonWidth;
    recordButton.setBounds (recordButtonX, longButtonY, longButtonWidth, longButtonHeight);

    // The descriptorBox is a protected member of SAFEAudioProcessorEditor in
    // which the user will type descriptors to save. Any error messages
    // for the user are also displayed in this box.
    addAndMakeVisible (descriptorBox);
    int descriptorBoxWidth = spacing + 2 * longButtonWidth;
    int descriptorBoxHeight = 100;
    int descriptorBoxY = longButtonY - spacing - descriptorBoxHeight;
    descriptorBox.setBounds (recordButtonX, descriptorBoxY,
                             descriptorBoxWidth, descriptorBoxHeight);

    // Some variables for positioning the meta data info and file access.
    int squareButtonWidth = 30;
    int squareButtonHeight = 30;
    int squareButtonY = descriptorBoxY - spacing - squareButtonHeight;

    // The metaDataButton is a protected member of SAFEAudioProcessorEditor which
    // will bring up an extra screen for the user to enter meta data
    // about themselves and the track they are working on.
    addAndMakeVisible (metaDataButton);
    metaDataButton.setBounds (recordButtonX, squareButtonY,
                              squareButtonWidth, squareButtonHeight);
    
    // The infoButton is a protected member of SAFEAudioProcessorEditor which
    // will bring up an extra screen with instructions on how to 
    // use the SAFE plug-ins.
    addAndMakeVisible (infoButton);
    int infoButtonX = recordButtonX + squareButtonWidth + spacing;
    infoButton.setBounds (infoButtonX, squareButtonY,
                          squareButtonWidth, squareButtonHeight);

    // The fileAccessButton is a protected member of SAFEAudioProcessorEditor which
    // toggles between sending data to the server or saving it locally.
    addAndMakeVisible (fileAccessButton);
    int fileAccessButtonX = infoButtonX + squareButtonWidth + spacing;
    fileAccessButton.setBounds (fileAccessButtonX, squareButtonY,
                          squareButtonWidth, squareButtonHeight);

    // The title of the plug-in.
    addAndMakeVisible (title);
    title.setFont (40);
    title.setJustificationType (Justification::centred);
    int titleX = spacing + sliderWidth;
    int titleWidth = width - titleX;
    title.setBounds (titleX, 0, titleWidth, squareButtonY); 

    // We need to tell the editor where the top left corner of the extra screens 
    // (loading, meta data and information) should be positioned when they
    // are visible.
    setExtraScreenPosition ((getWidth() - extraScreenWidth) / 2,
                            (getHeight() - extraScreenHeight) / 2);
}

SimpleDistortionAudioProcessorEditor::~SimpleDistortionAudioProcessorEditor()
{
}

void SimpleDistortionAudioProcessorEditor::paint (Graphics& g)
{
    // Legendary graphic design skills here.
    g.fillAll (Colours::grey);
}

void SimpleDistortionAudioProcessorEditor::resized()
{
}
