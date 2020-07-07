#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Views/Parameters/Knobs/KnobsView.h"
#include "PresetSlot.h"

class LFOParametersView : public juce::Component 
{
public:
    LFOParametersView(PresetSlot** ps);

    void paint(juce::Graphics&) override;
    void resized() override;
    
private:
    PresetSlot** presetSlot;
    juce::Label titleLabel;
    KnobsView knobsView;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFOParametersView)
};

