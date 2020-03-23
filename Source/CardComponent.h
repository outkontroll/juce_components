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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include <variant>
#include "TransformInfo.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CardComponent  : public Component,
                       private Timer
{
public:
    //==============================================================================
    CardComponent ();
    ~CardComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    std::function<void(bool, bool)> onClick;
    void rotateAnimated(const TransformInfo& transformInfo, int animationLengthMillisecs);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseUp (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void timerCallback() override;
    void animationTick();

    float angle = 0.0;
    float factorX = 1.0;
    float factorY = 1.0;

    struct Idle
    {
    };

    struct Animating
    {
        double startTime = 0.0;
        int animationLength = 0.0;

        struct Scaling
        {
            float originalFactorX = 1.0;
            float originalFactorY = 1.0;
            float finalFactorX = 1.0;
            float finalFactorY = 1.0;
        };

        struct Rotating
        {
            float originalAngle = 0.0;
            float finalAngle = 0.0;
        };

        std::variant<Rotating, Scaling> type;
    };

    std::variant<Idle, Animating> state = Idle{};
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CardComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

