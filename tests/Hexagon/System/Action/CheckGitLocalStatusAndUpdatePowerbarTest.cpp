
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/System/Action/CheckGitLocalStatusAndUpdatePowerbar.hpp>
#include <Hexagon/Powerbar/Powerbar.hpp>

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar action;
}

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest,
   execute__without_a_valid_powerbar__throws_an_error)
{
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar action;
   std::string expected_error_message =
      "CheckGitLocalStatusAndUpdatePowerbar::execute: error: guard \"powerbar\" not met";
   ASSERT_THROW_WITH_MESSAGE(action.execute(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_Action_CheckGitLocalStatusAndUpdatePowerbarTest,
   execute__does_not_blow_up)
{
   std::string current_project_directory = "/Users/markoates/Repos/hexagon/";
   Hexagon::Powerbar::Powerbar powerbar;
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar action(current_project_directory, &powerbar);
   ASSERT_EQ(true, action.execute());
}

