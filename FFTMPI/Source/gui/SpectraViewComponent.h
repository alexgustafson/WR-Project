/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_3F3DE5BFAAFCD1F0__
#define __JUCE_HEADER_3F3DE5BFAAFCD1F0__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SpectraViewComponent  : public Component,
                                public Timer
{
public:
    //==============================================================================
    SpectraViewComponent ();
    ~SpectraViewComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    float toDecibels (float absoluteValue);
    void addDFTData(float* newVector);
    void initSampleBuffer(int numChannels, int numSamples);
    void setSpectrumSize(int length, int resolution);
    void timerCallback();
    float xDrawPostion;
    void redrawData();
    void resetImage();
    void saveBufferToFile(String name);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int spectrumLength;
    int numOfFrequencies;
    std::vector< float* > buffers;
    float scopeLineW;
    CriticalSection lock;
    int bufferUntilDraw;
    Image spectraImage;
    Image bufferImage;
    float yStep;
    float xStep;
    float fudgeFactor;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectraViewComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_3F3DE5BFAAFCD1F0__
