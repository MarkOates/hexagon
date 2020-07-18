
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/System/Action/CheckGitSyncAndUpdatePowerbar.hpp>

TEST(Hexagon_System_Action_CheckGitSyncAndUpdatePowerbarTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar check_git_sync_and_update_powerbar;
}

TEST(Hexagon_System_Action_CheckGitSyncAndUpdatePowerbarTest,
   execute__without_a_valid_powerbar__throws_an_error)
{
   Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar check_git_sync_and_update_powerbar;
   std::string expected_error_message = "CheckGitSyncAndUpdatePowerbar::execute: error: guard \"powerbar\" not met";
   ASSERT_THROW_WITH_MESSAGE(check_git_sync_and_update_powerbar.execute(), std::runtime_error, expected_error_message);
}

