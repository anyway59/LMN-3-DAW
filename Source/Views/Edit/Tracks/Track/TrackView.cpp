#include "TrackView.h"

TrackView::TrackView(juce::String title)
{

    // set default colors
    getLookAndFeel().setColour(selectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(unselectedBackgroundColourId, juce::Colours::black);
    getLookAndFeel().setColour(unselectedTextColourId, juce::Colours::white);
    getLookAndFeel().setColour(selectedTextColourId, juce::Colours::white);
    backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
    textColour = getLookAndFeel().findColour(unselectedTextColourId);

    titleLabel.setFont (juce::Font (getHeight() * .7, juce::Font::bold));
    titleLabel.setText(title, juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(titleLabel);

}

void TrackView::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColour);
}

void TrackView::resized()
{

    juce::Font font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .7,  juce::Font::plain);
    titleLabel.setFont(font);
    titleLabel.setBounds(0, 0, getWidth(), getHeight());
}

void TrackView::setTitle(juce::String t)
{
    titleLabel.setText(t, juce::dontSendNotification);
}

void TrackView::setSelected(bool selected)
{
    if (selected)
    {
        backgroundColour = getLookAndFeel().findColour(selectedBackgroundColourId);
        textColour = getLookAndFeel().findColour(selectedTextColourId);

    } else {

        backgroundColour = getLookAndFeel().findColour(unselectedBackgroundColourId);
        textColour = getLookAndFeel().findColour(unselectedTextColourId);

    }

    titleLabel.setColour(juce::Label::textColourId, textColour);
    repaint();
}