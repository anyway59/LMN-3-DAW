#include <app_view_models/app_view_models.h>
#include <gtest/gtest.h>
#include "MockAvailablePluginsViewModelListener.h"

namespace AppViewModelsTests {

    class AvailablePluginsViewModelTest : public ::testing::Test {
    protected:

        AvailablePluginsViewModelTest()
                : selectionManager(engine),
                  edit(tracktion_engine::Edit::createSingleTrackEdit(engine)),
                  viewModel(*tracktion_engine::getAudioTracks(*edit)[0], selectionManager)

        {}

        void SetUp() override
        {

            // flush any updates
            viewModel.handleUpdateNowIfNeeded();

        }

        tracktion_engine::Engine engine {"ENGINE"};
        tracktion_engine::SelectionManager selectionManager;
        std::unique_ptr<tracktion_engine::Edit> edit;
        app_view_models::AvailablePluginsViewModel viewModel;

    };



    TEST_F(AvailablePluginsViewModelTest, initialSelectedCategoryIndex)
    {

        EXPECT_EQ(viewModel.getSelectedCategoryIndex(), 0);

    }

    TEST_F(AvailablePluginsViewModelTest, initialSelectedPluginIndex)
    {

        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);

    }

    TEST_F(AvailablePluginsViewModelTest, setSelectedCategoryIndex)
    {

        // should only be 2 categories, effects and instruments
       viewModel.setSelectedCategoryIndex(-1);
        EXPECT_EQ(viewModel.getSelectedCategoryIndex(), 0);
        viewModel.setSelectedCategoryIndex(-2);
        EXPECT_EQ(viewModel.getSelectedCategoryIndex(), 0);
        viewModel.setSelectedCategoryIndex(-100);
        EXPECT_EQ(viewModel.getSelectedCategoryIndex(), 0);
        viewModel.setSelectedCategoryIndex(0);
        EXPECT_EQ(viewModel.getSelectedCategoryIndex(), 0);
        viewModel.setSelectedCategoryIndex(1);
        EXPECT_EQ(viewModel.getSelectedCategoryIndex(), 1);
        viewModel.setSelectedCategoryIndex(2);
        EXPECT_EQ(viewModel.getSelectedCategoryIndex(), 1);
        viewModel.setSelectedCategoryIndex(100);
        EXPECT_EQ(viewModel.getSelectedCategoryIndex(), 1);

    }

    TEST_F(AvailablePluginsViewModelTest, setSelectedPluginIndexInstruments)
    {

        // For instruments there should only be 2
        // 40SC
        // Sampler
        // (VST3 get scanned asynchronously so they wont be present for the test)
        viewModel.setSelectedPluginIndex(-1);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);
        viewModel.setSelectedPluginIndex(-2);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);
        viewModel.setSelectedPluginIndex(-100);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);
        viewModel.setSelectedPluginIndex(0);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);
        viewModel.setSelectedPluginIndex(1);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 1);
        viewModel.setSelectedPluginIndex(2);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 1);
        viewModel.setSelectedPluginIndex(100);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 1);

    }

    TEST_F(AvailablePluginsViewModelTest, setSelectedPluginIndexEffects)
    {

        // For effects there should only be 8
        // EqualiserPlugin
        // ReverbPlugin
        // DelayPlugin
        // ChorusPlugin
        // PhaserPlugin
        // CompressorPlugin
        // PitchShiftPlugin
        // LowPassPlugin
        // (VST3 get scanned asynchronously so they wont be present for the test)

        viewModel.setSelectedCategoryIndex(1);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedPluginIndex(-1);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);
        viewModel.setSelectedPluginIndex(-2);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);
        viewModel.setSelectedPluginIndex(-100);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);
        viewModel.setSelectedPluginIndex(0);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 0);
        viewModel.setSelectedPluginIndex(1);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 1);
        viewModel.setSelectedPluginIndex(2);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 2);
        viewModel.setSelectedPluginIndex(6);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 6);
        viewModel.setSelectedPluginIndex(7);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 7);
        viewModel.setSelectedPluginIndex(8);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 7);
        viewModel.setSelectedPluginIndex(100);
        EXPECT_EQ(viewModel.getSelectedPluginIndex(), 7);

    }

    TEST_F(AvailablePluginsViewModelTest, getSelectedCategory)
    {

        EXPECT_EQ(viewModel.getSelectedCategory()->name, "Instruments");

        viewModel.setSelectedCategoryIndex(1);
        viewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(viewModel.getSelectedCategory()->name, "Effects");

    }

    TEST_F(AvailablePluginsViewModelTest, getSelectedPluginInstruments)
    {

        EXPECT_EQ(viewModel.getSelectedPlugin()->getName(), "4OSC");

        viewModel.setSelectedPluginIndex(1);
        viewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(viewModel.getSelectedPlugin()->getName(), "Sampler");

    }

    TEST_F(AvailablePluginsViewModelTest, getSelectedPluginEffects)
    {

        viewModel.setSelectedCategoryIndex(1);
        viewModel.handleUpdateNowIfNeeded();

        EXPECT_EQ(viewModel.getSelectedPlugin()->getName(), "4-Band Equaliser");

        viewModel.setSelectedPluginIndex(5);
        viewModel.handleUpdateNowIfNeeded();
        EXPECT_EQ(viewModel.getSelectedPlugin()->getName(), "Compressor");

    }

    using ::testing::_;
    TEST_F(AvailablePluginsViewModelTest, selectedCategoryIndexChanges)
    {

        MockAvailablePluginsViewModelListener listener;

        // when we set with -10, the current value is using the default value
        // this causes a property change to be sent even tho the default value
        // and the new value are the same
        // it also gets called when we add a listener
        EXPECT_CALL(listener, selectedCategoryIndexChanged(0)).Times(2);

        EXPECT_CALL(listener, selectedPluginIndexChanged(0)).Times(1);

        EXPECT_CALL(listener, selectedCategoryIndexChanged(1))
                .Times(1);

        viewModel.addListener(&listener);

        viewModel.setSelectedCategoryIndex(-10);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedCategoryIndex(-1);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedCategoryIndex(-100);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedCategoryIndex(0);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedCategoryIndex(1);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedCategoryIndex(2);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedCategoryIndex(100);
        viewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(AvailablePluginsViewModelTest, selectedPluginIndexChanges)
    {

        MockAvailablePluginsViewModelListener listener;

        // when we set with -10, the current value is using the default value
        // this causes a property change to be sent even tho the default value
        // and the new value are the same
        // also gets called when we add a listener
        EXPECT_CALL(listener, selectedPluginIndexChanged(0)).Times(2);

        EXPECT_CALL(listener, selectedCategoryIndexChanged(0)).Times(1);

        EXPECT_CALL(listener, selectedPluginIndexChanged(1)).Times(1);

        viewModel.addListener(&listener);

        viewModel.setSelectedPluginIndex(-10);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedPluginIndex(-1);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedPluginIndex(-100);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedPluginIndex(0);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedPluginIndex(1);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedPluginIndex(2);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.setSelectedPluginIndex(100);
        viewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(AvailablePluginsViewModelTest, selectedCategoryIndexChangesTriggersPluginChange0)
    {

        MockAvailablePluginsViewModelListener listener;

        // gets called when added as listener
        EXPECT_CALL(listener, selectedCategoryIndexChanged(0))
                .Times(1);

        EXPECT_CALL(listener, selectedCategoryIndexChanged(1))
                .Times(1);

        // called when added as listener
        EXPECT_CALL(listener, selectedPluginIndexChanged(1))
                .Times(1);

        // called when triggered by the category change
        EXPECT_CALL(listener, selectedPluginIndexChanged(0))
                .Times(1);

        // set plugin index to something other than 0
        // we expect it to be set back to 0 when the category changes
        viewModel.setSelectedPluginIndex(1);
        viewModel.handleUpdateNowIfNeeded();

        viewModel.addListener(&listener);

        // handle update twice, once for the category change, then again for the plugin change
        viewModel.setSelectedCategoryIndex(1);
        viewModel.handleUpdateNowIfNeeded();
        viewModel.handleUpdateNowIfNeeded();

    }

    TEST_F(AvailablePluginsViewModelTest, addSelectedPluginToTrack)
    {

        auto track = tracktion_engine::getAudioTracks(*edit)[0];
        int numPlugins = track->pluginList.size();
        // 40sc synth is initially selected
        viewModel.addSelectedPluginToTrack();
        EXPECT_EQ(track->pluginList.size(), numPlugins + 1);
        EXPECT_EQ(track->pluginList.getPlugins()[0]->getName(), viewModel.getSelectedPlugin()->getName());

        // try adding it again, it shouldnt get added since its already on track
        numPlugins = track->pluginList.size();
        viewModel.addSelectedPluginToTrack();
        EXPECT_EQ(track->pluginList.size(), numPlugins);

        // select a different synth and add it
        // it should remove the first synth and add this new one
        numPlugins = track->pluginList.size();
        viewModel.setSelectedPluginIndex(1);
        viewModel.handleUpdateNowIfNeeded();
        viewModel.addSelectedPluginToTrack();
        EXPECT_EQ(track->pluginList.size(), numPlugins);
        EXPECT_EQ(track->pluginList.getPlugins()[0]->getName(), viewModel.getSelectedPlugin()->getName());

        // add an effect
        numPlugins = track->pluginList.size();
        viewModel.setSelectedCategoryIndex(1);
        viewModel.handleUpdateNowIfNeeded();
        viewModel.addSelectedPluginToTrack();
        EXPECT_EQ(track->pluginList.size(), numPlugins + 1);
        EXPECT_EQ(track->pluginList.getPlugins().getLast()->getName(), viewModel.getSelectedPlugin()->getName());

    }
}
