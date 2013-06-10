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

#ifndef __JUCE_HEADER_16D92098AB691ACA__
#define __JUCE_HEADER_16D92098AB691ACA__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "AudioWavViewComponent.h"
#include "MPIHandler.h"
#include <boost/serialization/vector.hpp>
#include "SpectraViewComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainViewComponent  : public Component,
                           public Timer,
                           public ButtonListener
{
public:
    //==============================================================================
    MainViewComponent ();
    ~MainViewComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void showFile (const File& file);
    void loadFileIntoTransport (const File& audioFile);
    void processAudioFile () ;
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* backgrounpanel_png;
    static const int backgrounpanel_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> currentAudioFileSource;
    ScopedPointer<AudioFormatReader> audioReader;
    ScopedPointer<AudioSampleBuffer> serializeableAudioBuffer;
    File audioFile;
    int sliceSize;
    int64 currentSamplePosition;
    MPIHandler* mpiHandle;
    bool audioLoaded;
    std::vector< float* > buffers;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<AudioWavViewComponent> audioWavformViewer;
    ScopedPointer<TextButton> audioSelectButton;
    ScopedPointer<TextButton> startProcessButton;
    ScopedPointer<TextButton> testButton;
    ScopedPointer<SpectraViewComponent> audioWavformViewer2;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainViewComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_16D92098AB691ACA__
