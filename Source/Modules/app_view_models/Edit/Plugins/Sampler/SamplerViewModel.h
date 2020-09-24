namespace app_view_models
{

    namespace IDs
    {

        const juce::Identifier SAMPLER_VIEW_STATE("SAMPLER_VIEW_STATE");

    }

    class SamplerViewModel
        : public juce::ChangeListener,
          public juce::ValueTree::Listener,
          public app_view_models::ItemListState::Listener,
          public FlaggedAsyncUpdater
    {

    public:

        SamplerViewModel(tracktion_engine::SamplerPlugin* sampler);

        juce::StringArray getSampleNames();
        juce::File getSelectedSampleFile();


        juce::AudioThumbnail& getThumbnail();

        void selectedIndexChanged(int newIndex) override;

        void changeListenerCallback(juce::ChangeBroadcaster* source) override;

        class Listener {
        public:
            virtual ~Listener() = default;

            virtual void sampleChanged() {};


        };

        void addListener(Listener *l);
        void removeListener(Listener *l);

    private:

        tracktion_engine::SamplerPlugin* samplerPlugin;

        juce::ValueTree state;

        juce::AudioFormatManager formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioThumbnailCache thumbnailCache;
        juce::AudioThumbnail thumbnail;

        juce::ListenerList<Listener> listeners;

        bool shouldUpdateSample = false;

        void handleAsyncUpdate() override;


    public:
        ItemListState itemListState;

    };

}


