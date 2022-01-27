
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/ObjectivesLog/Stage.hpp>

TEST(Hexagon_ObjectivesLog_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::Stage stage;
}

TEST(Hexagon_ObjectivesLog_StageTest, render__without_an_objectives_log__throws_an_error)
{
   Hexagon::ObjectivesLog::Stage stage;
   std::string expected_error_message = "Stage::render: error: guard \"objectives_log\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_ObjectivesLog_StageTest, render__does_not_blow_up)
   // TODO
{
   //Hexagon::ObjectivesLog::Stage stage;
   //stage.render();
   //SUCCEED();
}

TEST(Hexagon_ObjectivesLog_StageTest, process_local_event__does_not_blow_up)
{
   Hexagon::ObjectivesLog::Stage stage;
   stage.process_local_event();
   SUCCEED();
}

TEST(Hexagon_ObjectivesLog_StageTest, process_event__does_not_blow_up)
{
   Hexagon::ObjectivesLog::Stage stage;
   stage.process_event();
   SUCCEED();
}
