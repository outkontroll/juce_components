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
#include "CardComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PictureAnimatorComponent  : public Component
{
public:
    //==============================================================================
    PictureAnimatorComponent ();
    ~PictureAnimatorComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void triggerAnimation();
    void triggerRotation(bool cw);
    int swapOffset(int previousOffset) const;
    Button* createButton(int buttonIndex);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDoubleClick (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    OwnedArray<Component> componentsToAnimate;
    std::unique_ptr<CardComponent> cardViewer;
    ComponentAnimator animator;
    int cycleCount = 2;
    int buttonOffset = 3;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Component> backgroundcomponent;
    std::unique_ptr<CardComponent> cViewer;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PictureAnimatorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

