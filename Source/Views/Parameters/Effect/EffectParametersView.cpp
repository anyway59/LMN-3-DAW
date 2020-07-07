#include "EffectParametersView.h"
EffectParametersView::EffectParametersView(PresetSlot** ps)
    : presetSlot(ps)
{

    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setText("Effect Parameters", juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(knobsView);

}

void EffectParametersView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void EffectParametersView::resized()
{

    titleLabel.setFont (juce::Font (getHeight()/ 8, juce::Font::bold));
    titleLabel.setBounds(0, 15, getWidth(), getHeight() / 8);
    juce::Rectangle<int> knobsBounds(0, getHeight() / 4, getWidth(), getHeight() / 2);
    knobsView.setBounds(knobsBounds);

}
