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
#include "SerializableAudioBuffer.h"
#include "MPIHandler.h"
#include <boost/serialization/vector.hpp>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainViewComponent  : public Component,
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
    SerializableAudioBuffer* getNextSampleSlice();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> currentAudioFileSource;
    ScopedPointer<AudioFormatReader> audioReader;
    ScopedPointer<SerializableAudioBuffer> serializeableAudioBuffer;
    File audioFile;
    int sliceSize = 2048;
    int64 currentSamplePosition = 0;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<AudioWavViewComponent> audioWavformViewer;
    ScopedPointer<Component> audioSpectraViewer;
    ScopedPointer<TextButton> audioSelectButton;
    ScopedPointer<TextButton> startProcessButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainViewComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_16D92098AB691ACA__
