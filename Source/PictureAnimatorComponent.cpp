/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include <iostream>
//[/Headers]

#include "PictureAnimatorComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PictureAnimatorComponent::PictureAnimatorComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    cViewer.reset (new CardComponent());
    addAndMakeVisible (cViewer.get());
    cViewer->setName ("card viewer");

    cViewer->setBounds (100, 100, 140, 220);


    //[UserPreSize]
    cViewer->onClick = [this](bool leftMouse, bool scale){
        if(scale)
            triggerScale(leftMouse);
        else
            triggerRotation(leftMouse);
    };
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PictureAnimatorComponent::~PictureAnimatorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    cViewer = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PictureAnimatorComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PictureAnimatorComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    repaint();
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PictureAnimatorComponent::triggerRotation(bool cw)
{
    static auto index = 0;
    index += (cw ? 1 : -1);
    const auto angle = MathConstants<float>::pi / 2 * index;
    TransformInfo transformInfo{Rotation{angle}};

    constexpr auto animationDurationMs = 300;
    cViewer->rotateAnimated(transformInfo, animationDurationMs);
}

void PictureAnimatorComponent::triggerScale(bool increase)
{
    static auto scale = 1.0f;
    if(increase)
        scale *= 1.4f;
    else
        scale /= 1.4f;

    TransformInfo transformInfo{Scale{scale, scale}};

    constexpr auto animationDurationMs = 300;
    cViewer->rotateAnimated(transformInfo, animationDurationMs);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PictureAnimatorComponent"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="card viewer" id="361f419ea92431c5" memberName="cViewer"
                    virtualName="" explicitFocusOrder="0" pos="100 100 140 220" class="CardComponent"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

