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

#include "SpectraViewComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SpectraViewComponent::SpectraViewComponent ()
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    sampleBuffer = new AudioSampleBuffer(1,1);
    //[/Constructor]
}

SpectraViewComponent::~SpectraViewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SpectraViewComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff111111));

    g.setGradientFill (ColourGradient (Colour (0xd2525668),
                                       376.0f, 64.0f,
                                       Colour (0xd818181c),
                                       152.0f, 424.0f,
                                       true));
    g.fillRect (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));

    //[UserPaint] Add your own custom painting code here..
    if (sampleBuffer->getNumSamples() > 100) {
        g.setColour(Colour::fromRGB(255, 1, 1));
        for(int x = 0; x < sampleBuffer->getNumSamples(); x++)
        {

            float sample = *sampleBuffer->getSampleData(0, x*10);
            int height = proportionOfHeight (sample ) > 1 ? proportionOfHeight (sample ) : 1;

            g.fillRect(x, proportionOfHeight(0.5f), 1, height );
        }

    }

    //[/UserPaint]
}

void SpectraViewComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SpectraViewComponent::initSampleBuffer(int numChannels, int numSamples)
{
    sampleBuffer = new AudioSampleBuffer(numChannels, numSamples);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SpectraViewComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff111111">
    <RECT pos="0 0 100% 100%" fill=" radial: 376 64, 152 424, 0=d2525668, 1=d818181c"
          hasStroke="0"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
