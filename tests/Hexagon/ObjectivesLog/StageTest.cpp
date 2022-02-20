
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/ObjectivesLog/Stage.hpp>

class Hexagon_ObjectivesLog_StageTest : public ::testing::Test {};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_ObjectivesLog_StageTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


TEST_F(Hexagon_ObjectivesLog_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::Stage stage;
}


TEST_F(Hexagon_ObjectivesLog_StageTest, render__without_a_font_bin__throws_an_error)
{
   Hexagon::ObjectivesLog::Stage stage;
   std::string expected_error_message = "Stage::render: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_ObjectivesLog_StageTestWithAllegroRenderingFixture, render__without_an_objectives_log__throws_an_error)
{
   AllegroFlare::FontBin font_bin;
   Hexagon::ObjectivesLog::Stage stage(&font_bin);

   std::string expected_error_message = "Stage::render: error: guard \"objectives_log\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_ObjectivesLog_StageTestWithAllegroRenderingFixture, render__does_not_blow_up)
{
   Hexagon::ObjectivesLog::ObjectivesLog objectives_log({
         { "Write a Passing Test", "Before continuing to use a feature in production, you should write a test.", false },
         { "Add Full Test Coverage Or Setup For It.",
           "Being able to isolate problems when they occour is critical to happy software development.  Make sure"
              " all of your features are tested, or, at least write empty DISABLED tests for the features so you"
              " can anticipate developing the feature in isolation when you need it.",
           false },
      });
   Hexagon::ObjectivesLog::Stage stage(&get_font_bin_ref(), &objectives_log);

   stage.render();
   al_flip_display();
   sleep(1);

   SUCCEED();
}


TEST_F(Hexagon_ObjectivesLog_StageTest, process_local_event__does_not_blow_up)
{
   Hexagon::ObjectivesLog::Stage stage;
   stage.process_local_event();
   SUCCEED();
}


TEST_F(Hexagon_ObjectivesLog_StageTest, process_event__does_not_blow_up)
{
   Hexagon::ObjectivesLog::Stage stage;
   stage.process_event();
   SUCCEED();
}


