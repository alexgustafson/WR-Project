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
    spectraImage = Image (Image::RGB,
                          getWidth(), getHeight(),
                          false);
    spectraImage.clear(spectraImage.getBounds(), Colour::fromFloatRGBA(0.0, 0.0, 0.0, 0.0));
    

    
    numOfFrequencies = 0;
    spectrumLength = 0;
    
    xDrawPostion = 0;
    scopeLineW = 1;
    bufferUntilDraw = 0;
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
    //const ScopedLock sl (lock);
    //[/UserPrePaint]
    
    g.fillAll (Colour (0xff111111));
    
    g.setGradientFill (ColourGradient (Colour (0xd2525668),
                                       376.0f, 64.0f,
                                       Colour (0xd818181c),
                                       152.0f, 424.0f,
                                       true));
    g.fillRect (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    
    //[UserPaint] Add your own custom painting code here..
    
    g.drawImageAt (spectraImage, 0, 0, false);
    //std::cout << "called redraw" << std::endl;

    //[/UserPaint]
}

void SpectraViewComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..
    

    //const ScopedLock sl (lock);
    //std::cout << "called resize" << std::endl;

    xStep = ((float)spectrumLength) / ((float)bufferImage.getWidth() * (float)numOfFrequencies * 2.0);
    spectraImage = spectraImage.rescaled(getWidth(), getHeight());
    
    if (spectrumLength > 10) {
        redrawData();
    }
    
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SpectraViewComponent::initSampleBuffer(int numChannels, int numSamples)
{
}

void SpectraViewComponent::setSpectrumSize(int length, int resolution)
{
    //const ScopedLock sl (lock);
    //std::cout << "called setSpectrumSize" << std::endl;
    bufferUntilDraw = 0;
    spectrumLength = length;
    numOfFrequencies = resolution;
    xStep = ((float)spectrumLength) / ((float)spectraImage.getWidth() * (float)numOfFrequencies * 2.0);
    startTimer(100);
}

void SpectraViewComponent::addDFTData(float *newVector)
{
    const ScopedLock sl (lock);
    buffers.push_back(newVector);
        
    if (bufferUntilDraw > xStep - 1) {
        
        Graphics g (spectraImage);
        
        bufferUntilDraw = 0;
        
        xDrawPostion = xDrawPostion + 1;
        
        for(int y = 0; y < numOfFrequencies; y++)
        {
            float value = buffers[buffers.size() - 1][y] ;
            g.setColour(Colour::fromHSV(value / 5  , 1.0, 1.0, value  ));
            g.fillRect(xDrawPostion , spectraImage.getHeight() - (y/2), 1, 1);
            
            
        }
    

    }
    
    bufferUntilDraw++;
    
}

void SpectraViewComponent::redrawData()
{
    const ScopedLock sl (lock);

    
    int localxStep  = ((float)spectrumLength) / ((float)spectraImage.getWidth() * (float)numOfFrequencies * 2.0);
    
    
    for (int x = 0; x < buffers.size() - 1; x++) {
        
        if ((x % localxStep) == 0) {
            
            Graphics g (spectraImage);
            
            bufferUntilDraw = 0;
            
            xDrawPostion = xDrawPostion + 1;
            
            for(int y = 0; y < numOfFrequencies; y++)
            {
                float value = buffers[buffers.size() - 1][y] ;
                g.setColour(Colour::fromHSV(value / 5  , 1.0, 1.0, value  ));
                g.fillRect(xDrawPostion , spectraImage.getHeight() - (y/2), 1, 1);
                
                
            }
            
            
        }
        
    }
    
    
    //std::cout <<  xStep << std::endl;
}


void SpectraViewComponent::timerCallback()
{
    //const ScopedLock sl (lock);

    repaint();
}

void SpectraViewComponent::resetImage()
{
    
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
