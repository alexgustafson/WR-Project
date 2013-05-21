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

#include "MainViewComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
MainViewComponent::MainViewComponent ()
{
    addAndMakeVisible (audioWavformViewer = new Component());
    audioWavformViewer->setName ("audio waveform viewer");

    addAndMakeVisible (AudioSpectraViewer = new Component());
    AudioSpectraViewer->setName ("audio spectra viewer");

    addAndMakeVisible (audioSelectButton = new TextButton ("audio select button"));
    audioSelectButton->setButtonText ("select audio file");
    audioSelectButton->addListener (this);

    addAndMakeVisible (startProcessButton = new TextButton ("start process button"));
    startProcessButton->setButtonText ("start processing");
    startProcessButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainViewComponent::~MainViewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    audioWavformViewer = nullptr;
    AudioSpectraViewer = nullptr;
    audioSelectButton = nullptr;
    startProcessButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainViewComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffededed));

    g.setColour (Colours::grey);
    g.fillRect (0, 0, 600, 400);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainViewComponent::resized()
{
    audioWavformViewer->setBounds (8, 40, 584, 112);
    AudioSpectraViewer->setBounds (8, 160, 584, 232);
    audioSelectButton->setBounds (8, 8, 150, 24);
    startProcessButton->setBounds (168, 8, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainViewComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == audioSelectButton)
    {
        //[UserButtonCode_audioSelectButton] -- add your button handler code here..
        FileChooser myChooser ("Please select the audio file you want to load...",
                               File::getSpecialLocation (File::userHomeDirectory),
                               String::empty);
        if (myChooser.browseForFileToOpen())
        {
            audioFile = (myChooser.getResult());
            std::cout << audioFile.getFileName();

        }
        //[/UserButtonCode_audioSelectButton]
    }
    else if (buttonThatWasClicked == startProcessButton)
    {
        //[UserButtonCode_startProcessButton] -- add your button handler code here..
        //[/UserButtonCode_startProcessButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainViewComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffededed">
    <RECT pos="0 0 600 400" fill="solid: ff808080" hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="audio waveform viewer" id="8c88d9e639609ba1" memberName="AudioWavformViewer"
                    virtualName="" explicitFocusOrder="0" pos="8 40 584 112" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="audio spectra viewer" id="2cb179ec12bf0b43" memberName="AudioSpectraViewer"
                    virtualName="" explicitFocusOrder="0" pos="8 160 584 232" class="Component"
                    params=""/>
  <TEXTBUTTON name="audio select button" id="22779fde320537b4" memberName="audioSelectButton"
              virtualName="" explicitFocusOrder="0" pos="8 8 150 24" buttonText="select audio file"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="start process button" id="84404b26681951e" memberName="startProcessButton"
              virtualName="" explicitFocusOrder="0" pos="168 8 150 24" buttonText="start processing"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
