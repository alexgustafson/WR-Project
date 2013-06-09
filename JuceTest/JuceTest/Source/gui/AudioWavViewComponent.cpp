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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "AudioWavViewComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AudioWavViewComponent::AudioWavViewComponent (AudioFormatManager& formatManager)
    : thumbnailCache (5),
      thumbnail (512, formatManager, thumbnailCache)
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    thumbnail.addChangeListener (this);
    //[/Constructor]
}

AudioWavViewComponent::~AudioWavViewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    thumbnail.removeAllChangeListeners();
    //[/Destructor]
}

//==============================================================================
void AudioWavViewComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff9ab2ba));

    //[UserPaint] Add your own custom painting code here..
    if (thumbnail.getTotalLength() > 0)
    {
        g.fillAll (Colours::white);
        g.setColour (Colours::lightblue);
        thumbnail.drawChannels (g, getLocalBounds().reduced (2),
                                startTime, endTime, 1.0f);
    }
    else
    {
        g.setFont (14.0f);
        g.drawFittedText ("(No audio file selected)", getLocalBounds(), Justification::centred, 2);
    }
    //[/UserPaint]
}

void AudioWavViewComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void AudioWavViewComponent::setFile (const File& file)
{
    thumbnail.setSource (new FileInputSource (file));
    startTime = 0;
    endTime = thumbnail.getTotalLength();
    //startTimer (1000 / 40);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudioWavViewComponent" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams="AudioFormatManager&amp; formatManager"
                 variableInitialisers="thumbnailCache (5),&#10;thumbnail (512, formatManager, thumbnailCache)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff9ab2ba"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
