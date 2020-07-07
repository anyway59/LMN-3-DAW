#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/KnobsView.h"

class ADSRParametersView : public juce::Component 
{
public:
    ADSRParametersView();

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    juce::Label titleLabel;
    KnobsView knobsView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ADSRParametersView)
};

