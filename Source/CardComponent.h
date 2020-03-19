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
    void timerCallback() override;

    std::function<void(bool)> onClick;
    void rotateAnimated(float angle, int animationLengthMillisecs);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseUp (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void animationTick();

    struct Idle
    {
        float angle = 0.0;
    };

    struct Animating
    {
        float originalAngle = 0.0;
        float finalAngle = 0.0;
        double startTime = 0.0;
        int animationLength = 0;
    };

    std::variant<Idle, Animating> state = Idle{};
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CardComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

