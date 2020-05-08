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
//[/Headers]

#include "CardComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // not needed as of C++20
//[/MiscUserDefs]

//==============================================================================
CardComponent::CardComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("CardComponent");

    //[UserPreSize]
    //[/UserPreSize]

    setSize (140, 220);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CardComponent::~CardComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CardComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        float x = 0.0f, y = 0.0f, width = 140.0f, height = 220.0f;
        Colour strokeColour = Colour (0xff3d2aa5);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 5.000f);
    }

    {
        int x = 12, y = 4, width = 116, height = 30;
        String text (TRANS("Hello"));
        Colour fillColour = Colours::yellow;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    {
        const int x = 12, y = 40, width = 140;
        const String text ("Angle: " + std::to_string(angle) + "\nFactor X: " + std::to_string(factorX) + "\nFactor Y: " + std::to_string(factorY) + "\nOffset X: " + std::to_string(offsetX) + "\nOffset Y: " + std::to_string(offsetY));
        const Colour fillColour = Colours::aqua;
        g.setColour (fillColour);
        g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawMultiLineText(text, x, y, width, Justification::centred);
    }
    //[/UserPaint]
}

void CardComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CardComponent::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    if(onClick != nullptr)
    {
        AnimationType animationType{rotation};
        if(e.mods.isShiftDown())
            animationType = scale;
        if(e.mods.isCtrlDown())
            animationType = translation;

        onClick(e.mods.isLeftButtonDown(), animationType);
    }
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CardComponent::timerCallback()
{
    animationTick();
    repaint();
}

void CardComponent::rotateAnimated(const TransformInfo& transformInfo, int animationLengthMillisecs)
{
    constexpr auto hz = 60;
    std::visit(overloaded {/*
        [&](const Animating::Rotating&)
        {
//            const auto now = Time::getMillisecondCounterHiRes();
//            const auto elapsed = static_cast<int>(now - a.startTime);
//            const auto remaining = a.animationLength - elapsed;
//            state = Rotating{a.startTime, a.originalAngle, transformInfo.rotation->angle, remaining + animationLengthMillisecs};
        },
        [&](const Animating::Scaling&)
        {
//            const auto now = Time::getMillisecondCounterHiRes();
//            const auto elapsed = static_cast<int>(now - a.startTime);
//            const auto remaining = a.animationLength - elapsed;
        },*/
        [&](const auto&){},
        [&](const Idle&)
        {
            std::visit(overloaded{
                [](const Identity&){},
                [&](const Rotation& rotationInfo){
                    state = Animating{Time::getMillisecondCounterHiRes(), animationLengthMillisecs, Animating::Rotating{angle, rotationInfo.angle}};
                },
                [&](const Scale& scaleInfo){
                    state = Animating{Time::getMillisecondCounterHiRes(), animationLengthMillisecs, Animating::Scaling{factorX, factorY, scaleInfo.factorX, scaleInfo.factorY}};
                },
                [&](const Translation& offsetInfo){
                    state = Animating{Time::getMillisecondCounterHiRes(), animationLengthMillisecs, Animating::Translating{offsetX, offsetY, offsetX + offsetInfo.offsetX, offsetY + offsetInfo.offsetY}};
                },
            }, transformInfo.transformation);

            startTimerHz(hz);
        },
    }, state);

}

void CardComponent::animationTick()
{
    std::visit(overloaded
    {
        [&](const Animating& a)
        {
            const auto now = Time::getMillisecondCounterHiRes();
            const auto elapsed = now - a.startTime;

            const auto centreX = getBounds().getCentreX();
            const auto centreY = getBounds().getCentreY();

            std::visit(overloaded
            {
                [&](const Animating::Rotating& r)
                {
                    if(elapsed >= a.animationLength)
                    {
                        stopTimer();

                        angle = r.finalAngle;
                        state = Idle{};
                    }
                    else
                    {
                        const auto percentage = elapsed / a.animationLength;
                        angle = (r.finalAngle - r.originalAngle) * percentage + r.originalAngle;
                    }
                },
                [&](const Animating::Scaling& s)
                {
                    if(elapsed >= a.animationLength)
                    {
                        stopTimer();

                        factorX = s.finalFactorX;
                        factorY = s.finalFactorY;
                        state = Idle{};
                    }
                    else
                    {
                        const auto percentage = elapsed / a.animationLength;
                        factorX = (s.finalFactorX - s.originalFactorX) * percentage + s.originalFactorX;
                        factorY = (s.finalFactorY - s.originalFactorY) * percentage + s.originalFactorY;
                    }
                },
                [&](const Animating::Translating& t)
                {
                    if(elapsed >= a.animationLength)
                    {
                        stopTimer();

                        offsetX = t.finalOffsetX;
                        offsetY = t.finalOffsetY;
                        state = Idle{};
                    }
                    else
                    {
                        const auto percentage = elapsed / a.animationLength;
                        offsetX = (t.finalOffsetX - t.originalOffsetX) * percentage + t.originalOffsetX;
                        offsetY = (t.finalOffsetY - t.originalOffsetY) * percentage + t.originalOffsetY;
                    }
                }
            }, a.type);

            setTransform(AffineTransform::rotation(angle, centreX, centreY).
              followedBy(AffineTransform::scale(factorX, factorY, centreX, centreY)).
              followedBy(AffineTransform::translation(offsetX, offsetY)));
        },
        [this](const Idle&)
        {
            if(isTimerRunning())
                stopTimer();
        },
    }, state);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CardComponent" componentName="CardComponent"
                 parentClasses="public Component, private Timer" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="140" initialHeight="220">
  <METHODS>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="0 0 140 220" cornerSize="10.0" fill="image: , 0, 0 0" hasStroke="1"
               stroke="5, mitered, butt" strokeColour="solid: ff3d2aa5"/>
    <TEXT pos="12 4 116 30" fill="solid: ffffff00" hasStroke="0" text="Hello"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

