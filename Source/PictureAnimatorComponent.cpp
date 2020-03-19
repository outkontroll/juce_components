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
    for (auto i = 0; i < 11; ++i)
    {
        auto* b = createButton(i);
        componentsToAnimate.add (b);
        addAndMakeVisible (b);
        b->onClick = [this] { triggerAnimation(); };
    }

    //cycleCount = 2;
    //startTimerHz (60);
    //cardViewer.reset(new CardComponent());
    //addAndMakeVisible(cardViewer.get());
    //[/Constructor_pre]

    backgroundcomponent.reset (new Component());
    addAndMakeVisible (backgroundcomponent.get());
    backgroundcomponent->setName ("new component");

    backgroundcomponent->setBounds (112, 80, 552, 256);

    cViewer.reset (new CardComponent());
    addAndMakeVisible (cViewer.get());
    cViewer->setName ("card viewer");

    cViewer->setBounds (100, 100, 140, 220);


    //[UserPreSize]
    cViewer->onClick = [this](bool leftMouse){
        static int clickCount = 1;
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

    backgroundcomponent = nullptr;
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

    {
        float x = 135.0f, y = 100.0f, width = 100.0f, height = 200.0f;
        Colour fillColour = Colour (0xff2aa538);
        Colour strokeColour = Colour (0xffffa000);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 5.000f);
    }

    {
        float x = 535.0f, y = 100.0f, width = 100.0f, height = 200.0f;
        Colour fillColour = Colour (0xff2a78a5);
        Colour strokeColour = Colour (0xff0089ff);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 5.000f);
    }

    {
        float x = 335.0f, y = 100.0f, width = 100.0f, height = 200.0f;
        Colour fillColour = Colour (0xffa5442a);
        Colour strokeColour = Colour (0xff00ff14);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 5.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PictureAnimatorComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    triggerAnimation();
    backgroundcomponent->resized();
    repaint();
    //[/UserResized]
}

void PictureAnimatorComponent::mouseDoubleClick (const MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
    if(!e.mods.isShiftDown())
        buttonOffset = swapOffset(buttonOffset);
    std::cout << "Double click with" << (e.mods.isShiftDown() ? " " : "out ") << "shift key, offset: " << buttonOffset << std::endl;
    //[/UserCode_mouseDoubleClick]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PictureAnimatorComponent::triggerAnimation()
{
    const auto width = getWidth();
    const auto height = getHeight();

    const auto finalAlpha = 1.0f;
    const auto useProxyComponent = false;
    const auto startSpeed = 0.0;
    const auto endSpeed = 0.0;

    const bool useWidth = (height > width);
    const auto radius = useWidth ? width  * 0.35f : height * 0.35f;

    for (auto* component : componentsToAnimate)
    {
        const auto newIndex = (componentsToAnimate.indexOf (component) + buttonOffset * cycleCount) % componentsToAnimate.size();

        const auto angle = newIndex * MathConstants<float>::twoPi / componentsToAnimate.size() + 1;

        const Rectangle<int> finalBounds (getWidth()  / 2 + (int) (radius * std::sin (angle)) - 50,
                                          getHeight() / 2 + (int) (radius * std::cos (angle)) - 50,
                                          100, 100);

        const auto animationDurationMs = 900 + static_cast<int>(300 * std::sin (angle));

        animator.animateComponent (component,
                                   finalBounds.reduced (10),
                                   finalAlpha,
                                   animationDurationMs,
                                   useProxyComponent,
                                   startSpeed,
                                   endSpeed);
    }

    ++cycleCount;
}

void PictureAnimatorComponent::triggerRotation(bool cw)
{
    static auto index = 0;
    index += (cw ? 1 : -1);
    const auto angle = MathConstants<float>::pi / 2 * index;
    constexpr auto animationDurationMs = 300;

    cViewer->rotateAnimated(angle, animationDurationMs);
}

int PictureAnimatorComponent::swapOffset(int previousOffset) const
{
    return previousOffset % 3 + 1;
}

Button* PictureAnimatorComponent::createButton(int buttonIndex)
{
    auto* b = new TextButton();
    b->setButtonText(std::to_string(buttonIndex));
    return b;
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
  <METHODS>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="135 100 100 200" cornerSize="10.0" fill="solid: ff2aa538"
               hasStroke="1" stroke="5, mitered, butt" strokeColour="solid: ffffa000"/>
    <ROUNDRECT pos="535 100 100 200" cornerSize="10.0" fill="solid: ff2a78a5"
               hasStroke="1" stroke="5, mitered, butt" strokeColour="solid: ff0089ff"/>
    <ROUNDRECT pos="335 100 100 200" cornerSize="10.0" fill="solid: ffa5442a"
               hasStroke="1" stroke="5, mitered, butt" strokeColour="solid: ff00ff14"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="new component" id="43f53019c114ce7a" memberName="backgroundcomponent"
                    virtualName="" explicitFocusOrder="0" pos="112 80 552 256" class="Component"
                    params=""/>
  <GENERICCOMPONENT name="card viewer" id="361f419ea92431c5" memberName="cViewer"
                    virtualName="" explicitFocusOrder="0" pos="100 100 140 220" class="CardComponent"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

