#ifndef SAFE_FEATURE_EXTRACTOR_H_INCLUDED
#define SAFE_FEATURE_EXTRACTOR_H_INCLUDED

typedef Vamp::HostExt::PluginLoader VampPluginLoader;
typedef Vamp::HostExt::PluginLoader::PluginKey VampPluginKey;
typedef Vamp::Plugin VampPlugin;
typedef Vamp::RealTime VampTime;
typedef Vamp::Plugin::OutputList VampOutputList;
typedef Vamp::Plugin::OutputDescriptor VampOutputDescriptor;
typedef Vamp::Plugin::FeatureSet VampFeatureSet;
typedef Vamp::Plugin::FeatureList VampFeatureList;
typedef Vamp::Plugin::Feature VampFeature;

struct AudioFeature
{
    int timeStamp;
    Array <double> values;
    int duration;
};

/** 
 *  A class for extracting features from a block of audio.
 */
class SAFEFeatureExtractor
{
public:
    //==========================================================================
    //      Constructor and Destructor
    //==========================================================================
    /** Create a new feature extractor. */
    SAFEFeatureExtractor();

    /** Destructor */
    ~SAFEFeatureExtractor();

    //==========================================================================
    //      Setup
    //==========================================================================
    /** Initialise the feature extractor.
     *
     *  @param numChannelsInit  the number of input channels
     *  @param frameOrderInit   the size of the analysis frames - this is given as an exponent
     *                          of two, the frame length in samples will be 2 ^ frameOrder
     *  @param stepSizeInit     the step size between analysis frames in samples - if this is
     *                          greater than the frame length it will be set to the 
     *                          frame length
     *  @param sampleRate       the sample rate of the audio to be analysed
     */
    void initialise (int numChannelsInit, int defaultFrameSizeInit, int defaultStepSizeInit, double sampleRate);

    //==========================================================================
    //      Add Features
    //==========================================================================
    /** Add libxtract features to extract from the audio.
     * 
     *  @param feature  the feature to extract
     */
    void addLibXtractFeature (LibXtract::Feature feature);

    /** Add vamp plug-in to extract features from the audio.
     * 
     *  @param libraryName  the name of the vamp plug-in library
     *  @param pluginName   the name of the plug-in in the library
     *
     *  The vamp plug-ins added should be installed in the standard vamp
     *  plug-in directory on the users system. If they are not on the system the features
     *  will not be extracted.
     *
     *  Vamp plug-ins will be initialised to use their preferred block and step sizes.
     *  If they do not declare one they will use the sizes passed to initialise().
     */
    void addVampPlugin (const String &libraryName, const String &pluginName);

    //==========================================================================
    //      Analyse Audio
    //==========================================================================
    /** Analyse a buffer of audio.
     *
     *  This function steps through the buffer of audio at the various
     *  frame and step sizes that are enabled. The features values are saved locally
     *  to the feature extractor object for reference later.
     *
     *  @param buffer  the buffer of audio to analyse.
     */
    void analyseAudio (AudioSampleBuffer &buffer);

    /** Set a windowing function for use in the spectral analysis.
     *
     *  During spectral analysis each frame of audio is passed to the windowing 
     *  function to have a window applied. By default the spectral analysis uses
     *  a Hann window.
     *
     *  @param newWindowingFunction  a pointer to the new windowing function to use -
     *                               the function should apply a window function of length
     *                               numSamples to the audioData
     */
    void setWindowingFunction (void (*newWindowingFunction) (float*, int));

    /** Add the recorded audio features to an xml element.
     *
     *  This should be called after a call to analyseAudio() has returned.
     *  It will put all the audio features which were recorded into an xml element
     *  you pass it.
     */
    void addFeaturesToXmlElement (XmlElement *element);

private:
    bool initialised;
    int numChannels, defaultFrameSize, defaultStepSize;
    double fs;

    // some fft bits
    std::map <int, ScopedPointer <FFT> > fftCache;
    std::map <int, AudioSampleBuffer> spectraCache;

    void cacheNewFFT (int size);

    void calculateSpectra (const AudioSampleBuffer &frame);
    void (*windowingFunction) (float*, int);
    static void applyHannWindow (float *data, int numSamples);

    struct AnalysisConfiguration
    {
        int frameSize;
        int stepSize;
        bool libXtractConfiguration;
        Array <int> vampPluginIndicies;
    };

    OwnedArray <AnalysisConfiguration> analysisConfigurations;

    AnalysisConfiguration* addNewAnalysisConfiguration (int frameSize, int stepSize, bool libXtractConfiguration);
    void addVampPluginToAnalysisConfigurations (int pluginIndex, int frameSize, int stepSize);
    const AnalysisConfiguration* getVampPluginAnalysisConfiguration (int pluginIndex);

    void addAudioFeatureToXmlElement (XmlElement *element, const AudioFeature &feature);
    String doubleToString (double value);
    
    //==========================================================================
    //      libxtract stuff
    //==========================================================================
    bool libXtractSpectrumNeeded, libXtractPeakSpectrumNeeded, libXtractHarmonicSpectrumNeeded;
    bool calculateLibXtractScalarFeature [LibXtract::NumScalarFeatures];
    Array <Array <double> > libXtractScalarFeatureValues;

    static const int numLibXtractBarkBands = 25;
    HeapBlock <int> libXtractBarkBandLimits;
    bool calculateLibXtractBarkCoefficients;
    Array <Array <double> > libXtractBarkCoefficients;

    static const int numLibXtractMelFilters = 13;
    xtract_mel_filter libXtractMelFilters;
    bool libXtractMelFiltersInitialised;
    bool calculateLibXtractMFCCs;
    Array <Array <double> > libXtractMFCCs;
    void deleteLibXtractMelFilters();

    Array <Array <double> > libXtractSpectra, libXtractPeakSpectra, libXtractHarmonicSpectra;

    HeapBlock <double> libXtractChannelData;

    struct LibXtractFeature
    {
        LibXtract::Feature featureNumber;
        Array <Array <AudioFeature> > featureValues;
    };

    OwnedArray <LibXtractFeature> libXtractFeatureValues;

    void initialiseLibXtract();
    void calculateLibXtractSpectra();
    void calculateLibXtractFeatures (const AudioSampleBuffer &frame);
    void addLibXtractFeaturesToList (int timeStamp);
    void clearLibXtractFeatures();

    //==========================================================================
    //      vamp stuff
    //==========================================================================
    struct VampPluginConfiguration
    {
        int frameSize;
        int stepSize;
        ScopedPointer <VampPlugin> plugin;
        VampOutputList outputs;
        Array <Array <AudioFeature> > featureValues;
    };

    VampPluginLoader *vampPluginLoader;
    Array <VampPluginKey> vampPluginKeys;
    OwnedArray <VampPluginConfiguration> vampPlugins;

    void initialiseVampPlugins();
    void resetVampPlugins();
    void loadAndInitialiseVampPlugin (const VampPluginKey &key);
    void calculateVampPluginFeatures (const Array <int> &plugins, const AudioSampleBuffer &frame, int timeStamp);
    void getRemainingVampPluginFeatures();
    void addVampPluginFeaturesToList (int pluginIndex, VampFeatureSet &features, int timeStamp);
    bool getVampPluginFeatureTimeAndDuration (AudioFeature &newFeature, 
                                              const VampOutputDescriptor &output,
                                              const VampFeature &feature,
                                              int timeStamp);
    void clearVampFeatures();
    int nextVampFeatureTimeStamp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SAFEFeatureExtractor);
};

#endif // SAFE_FEATURE_EXTRACTOR_H_INCLUDED
    void clearVampFeatures();
