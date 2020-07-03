
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Blast/FileExistenceChecker.hpp>

#include <Hexagon/System/Config.hpp>

static const std::string TEST_FIXTURE_DIRECTORY_ROOT = "/Users/markoates/Repos/hexagon/tests/fixtures/";
static const std::string TEST_FIXTURE_EMPTY_CONFIG_FILENAME = TEST_FIXTURE_DIRECTORY_ROOT + "hexagon.empty.cfg";
static const std::string TEST_FIXTURE_CONFIG_FILENAME = TEST_FIXTURE_DIRECTORY_ROOT + "hexagon.test.cfg";

TEST(Hexagon_System_ConfigTest, expected_fixture_files_exist)
{
   ASSERT_EQ(true, Blast::FileExistenceChecker(TEST_FIXTURE_EMPTY_CONFIG_FILENAME).exists());
   ASSERT_EQ(true, Blast::FileExistenceChecker(TEST_FIXTURE_CONFIG_FILENAME).exists());
}

TEST(Hexagon_System_ConfigTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Config config;
}

TEST(Hexagon_System_ConfigTest, config_filename__has_a_getter_with_the_expected_default)
{
   Hexagon::System::Config config;

   std::string expected_default_config_filename =
      "/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg";
   std::string actual_default_config_filename = config.get_config_filename();

   EXPECT_EQ(expected_default_config_filename, actual_default_config_filename);
}

TEST(DISABLED_Hexagon_System_ConfigTest, initialize__can_be_called_multiple_times_without_side_effects)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);

   // test needs to be modified to expect no extranious calls to config.load()

   config.initialize();
   config.initialize();
   config.initialize();
}

// get_initial_display_width

TEST(Hexagon_System_ConfigTest, get_initial_display_width__without_initialization__throws_an_error)
{
   al_init();
   Hexagon::System::Config config;

   std::string expected_error_message = "[Hexagon::System::Config error:] cannot call " \
                                        "\"get_initial_display_width\". This component must be " \
                                        "initialized before this function can be used.";

   ASSERT_THROW_WITH_MESSAGE(config.get_initial_display_width(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_ConfigTest,
   get_initial_display_width__without_the_config_key_present__returns_the_expected_default_value)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(2430, config.get_initial_display_width());
}

TEST(Hexagon_System_ConfigTest, get_initial_display_width__returns_the_expected_value_from_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   int expected_fixture_initial_display_width = 1234;
   ASSERT_EQ(expected_fixture_initial_display_width, config.get_initial_display_width());
}

// get_initial_display_height

TEST(Hexagon_System_ConfigTest, get_initial_display_height__without_initialization__throws_an_error)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);

   std::string expected_error_message = "[Hexagon::System::Config error:] cannot call " \
                                        "\"get_initial_display_height\". This component must be " \
                                        "initialized before this function can be used.";

   ASSERT_THROW_WITH_MESSAGE(config.get_initial_display_height(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_ConfigTest,
   get_initial_display_height__without_the_config_key_present__returns_the_expected_default_value)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(1350, config.get_initial_display_height());
}

TEST(Hexagon_System_ConfigTest, get_initial_display_height__returns_the_expected_value_from_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   int expected_fixture_initial_display_height = 5678;
   ASSERT_EQ(expected_fixture_initial_display_height, config.get_initial_display_height());
}

// get_default_navigator_directory

TEST(Hexagon_System_ConfigTest, get_default_navigator_directory__without_initialization__throws_an_error)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);

   std::string expected_error_message = "[Hexagon::System::Config error:] cannot call " \
                                        "\"get_default_navigator_directory\". This component must be " \
                                        "initialized before this function can be used.";

   ASSERT_THROW_WITH_MESSAGE(config.get_default_navigator_directory(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_ConfigTest,
   get_default_navigator_directory__without_the_config_key_present__returns_the_expected_default_value)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(1350, config.get_initial_display_height());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest, get_default_navigator_directory__returns_the_expected_value_from_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   std::string expected_fixture_default_navigator_directory = "/Some/path/on/the/system";
   ASSERT_EQ(expected_fixture_default_navigator_directory, config.get_default_navigator_directory());

   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_ConfigTest, get_regex_temp_filename__returns_the_expected_default_value)
{
   al_init();

   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   std::string expected_default = "/Some/path/on/the/system";
   ASSERT_EQ(expected_default, config.get_regex_temp_filename());

   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_ConfigTest, get_clipboard_temp_filename__returns_the_expected_default_value)
{
}

TEST(DISABLED_Hexagon_System_ConfigTest, get_file_navigator_selection_filename__returns_the_expected_default_value)
{
}

TEST(DISABLED_Hexagon_System_ConfigTest, get_make_command_filename__returns_the_expected_default_value)
{
}

TEST(DISABLED_Hexagon_System_ConfigTest, is_dark_mode__returns_the_expected_default_value)
{
}

