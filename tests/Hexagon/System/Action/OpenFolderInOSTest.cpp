
#include <gtest/gtest.h>

#include <Hexagon/System/Action/OpenFolderInOS.hpp>


#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


TEST(Hexagon_System_Action_OpenFolderInOSTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::OpenFolderInOS open_folder_in_os;
}


TEST(Hexagon_System_Action_OpenFolderInOSTest, execute__opens_the_folder)
{
   Hexagon::System::Action::OpenFolderInOS open_folder_in_os;
   open_folder_in_os.execute();
}


TEST(Hexagon_System_Action_OpenFolderInOSTest, execute__on_a_folder_that_does_not_exist__throws_an_error)
{
   Hexagon::System::Action::OpenFolderInOS open_folder_in_os("a_folder_that_does_not_exist");
   std::string expected_error_message = "Hexagon::System::Action::OpenFolderInOS::"
      "build_shell_command_to_open_folder_in_os: error: \"/Users/markoates/Repos/hexagon/"
      "a_folder_that_does_not_exist\" is not a directory.";

   EXPECT_THROW_WITH_MESSAGE(
      open_folder_in_os.execute(),
      std::runtime_error,
      expected_error_message
   );
}


