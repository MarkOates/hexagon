
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <allegro5/allegro_color.h>
static void EXPECT_COLOR_EQ(const ALLEGRO_COLOR &color1, const ALLEGRO_COLOR &color2)
{
   EXPECT_EQ(color1.r, color2.r);
   EXPECT_EQ(color1.g, color2.g);
   EXPECT_EQ(color1.b, color2.b);
   EXPECT_EQ(color1.a, color2.a);
}

#include <Blast/FileExistenceChecker.hpp>

#include <Hexagon/System/Config.hpp>

static const std::string TEST_FIXTURE_DIRECTORY_ROOT = "/Users/markoates/Repos/hexagon/tests/fixtures/";
static const std::string TEST_FIXTURE_EMPTY_CONFIG_FILENAME = TEST_FIXTURE_DIRECTORY_ROOT + "hexagon.empty.cfg";
static const std::string TEST_FIXTURE_CONFIG_FILENAME = TEST_FIXTURE_DIRECTORY_ROOT + "hexagon.test.cfg";

TEST(Hexagon_System_ConfigTest,
   expected_fixture_files_exist)
{
   ASSERT_EQ(true, Blast::FileExistenceChecker(TEST_FIXTURE_EMPTY_CONFIG_FILENAME).exists());
   ASSERT_EQ(true, Blast::FileExistenceChecker(TEST_FIXTURE_CONFIG_FILENAME).exists());
}

TEST(Hexagon_System_ConfigTest,
   can_be_created_without_blowing_up)
{
   Hexagon::System::Config config;
}

TEST(Hexagon_System_ConfigTest,
   config_filename__has_a_getter_with_the_expected_default)
{
   Hexagon::System::Config config;

   std::string expected_default_config_filename =
      "/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg";
   std::string actual_default_config_filename = config.get_config_filename();

   EXPECT_EQ(expected_default_config_filename, actual_default_config_filename);
}

TEST(DISABLED_Hexagon_System_ConfigTest,
   initialize__can_be_called_multiple_times_without_side_effects)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);

   // test needs to be modified to expect no extranious calls to config.load()

   config.initialize();
   config.initialize();
   config.initialize();
}

// get_initial_display_width

TEST(Hexagon_System_ConfigTest,
   get_initial_display_width__without_initialization__throws_an_error)
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

TEST(Hexagon_System_ConfigTest,
   get_initial_display_width__returns_the_expected_value_from_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   int expected_fixture_initial_display_width = 1234;
   ASSERT_EQ(expected_fixture_initial_display_width, config.get_initial_display_width());
}

// get_initial_display_height

TEST(Hexagon_System_ConfigTest,
   get_initial_display_height__without_initialization__throws_an_error)
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

TEST(Hexagon_System_ConfigTest,
   get_initial_display_height__returns_the_expected_value_from_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   int expected_fixture_initial_display_height = 5678;
   ASSERT_EQ(expected_fixture_initial_display_height, config.get_initial_display_height());
}

// get_default_navigator_directory

TEST(Hexagon_System_ConfigTest,
   get_default_navigator_directory__without_initialization__throws_an_error)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);

   std::string expected_error_message = "[Hexagon::System::Config error:] cannot call " \
                                        "\"get_default_navigator_directory\". This component must be " \
                                        "initialized before this function can be used.";

   ASSERT_THROW_WITH_MESSAGE(config.get_default_navigator_directory(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_ConfigTest,
   get_default_navigator_directory__returns_the_expected_value_from_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   std::string expected_fixture_default_navigator_directory = "/Some/path/on/the/system";
   ASSERT_EQ(expected_fixture_default_navigator_directory, config.get_default_navigator_directory());

   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_ConfigTest,
   get_regex_temp_filename__returns_the_expected_default_value)
{
   al_init();

   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   std::string expected_default = "/Some/path/on/the/system";
   ASSERT_EQ(expected_default, config.get_regex_temp_filename());

   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_ConfigTest,
   get_clipboard_temp_filename__returns_the_expected_default_value)
{
}

TEST(DISABLED_Hexagon_System_ConfigTest,
   get_file_navigator_selection_filename__returns_the_expected_default_value)
{
}

TEST(DISABLED_Hexagon_System_ConfigTest,
   get_make_command_filename__returns_the_expected_default_value)
{
}

TEST(DISABLED_Hexagon_System_ConfigTest,
   get_focused_component_filename__returns_the_expected_default_value)
{
}

TEST(Hexagon_System_ConfigTest, is_dark_mode__before_initialization__raises_an_error)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   std::string expected_error_message = "Config::is_dark_mode: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(config.is_dark_mode(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   is_dark_mode__returns_true_if_the_a_true_value_is_set_in_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(true, config.is_dark_mode());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   is_dark_mode__returns_false_by_default)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(false, config.is_dark_mode());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest, get_objective__before_initialization__raises_an_error)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   std::string expected_error_message = "Config::get_objective: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(config.get_objective(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   get_objective__returns_the_value_if_it_is_set_in_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ("Load objective text from test config file", config.get_objective());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   get_objective__returns_the_expected_default_value)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ("- objective not set -", config.get_objective());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest, is_fullscreen__before_initialization__raises_an_error)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   std::string expected_error_message = "Config::is_fullscreen: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(config.is_fullscreen(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   is_fullscreen__returns_true_if_the_a_true_value_is_set_in_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(true, config.is_fullscreen());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   is_fullscreen__returns_false_by_default)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(false, config.is_fullscreen());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest, get_hud_show_focus_timer_bar__before_initialization__raises_an_error)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   std::string expected_error_message = "Config::get_hud_show_focus_timer_bar: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(config.get_hud_show_focus_timer_bar(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   get_hud_show_focus_timer_bar__returns_true_if_the_a_true_value_is_set_in_the_config)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(true, config.get_hud_show_focus_timer_bar());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   get_hud_show_focus_timer_bar__returns_false_by_default)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(false, config.get_hud_show_focus_timer_bar());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   get_initial_baseline_camera_stepback__returns_the_expected_value)
{
   al_init();

   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();
   ASSERT_EQ(130, config.get_initial_baseline_camera_stepback());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest, get_initial_baseline_camera_stepback__before_initialization__raises_an_error)
{
   // TODO
}

TEST(Hexagon_System_ConfigTest,
   get_backfill_color__when_in_dark_mode__returns_the_expected_color)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(true, config.is_dark_mode());

   ALLEGRO_COLOR expected_color = al_color_name("black");
   //ALLEGRO_COLOR expected_color = al_color_html("a67d5a"); // color of lamp light against wall
   EXPECT_COLOR_EQ(expected_color, config.get_backfill_color());

   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_ConfigTest,
   get_backfill_color__when_in_not_in_dark_mode__returns_the_expected_color)
   // disabled because changing the background color breaks this test
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(false, config.is_dark_mode());

   ALLEGRO_COLOR expected_color = al_color_html("d2dbd6");
   EXPECT_COLOR_EQ(expected_color, config.get_backfill_color());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   get_base_text_color__when_in_dark_mode__returns_white)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(true, config.is_dark_mode());

   ALLEGRO_COLOR expected_color = al_color_name("white");
   EXPECT_COLOR_EQ(expected_color, config.get_base_text_color());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   get_base_text_color__when_in_not_in_dark_mode__returns_black)
{
   al_init();
   Hexagon::System::Config config(TEST_FIXTURE_EMPTY_CONFIG_FILENAME);
   config.initialize();

   ASSERT_EQ(false, config.is_dark_mode());

   ALLEGRO_COLOR expected_color = al_color_name("black");
   EXPECT_COLOR_EQ(expected_color, config.get_base_text_color());

   al_uninstall_system();
}

TEST(Hexagon_System_ConfigTest,
   get_backfill_opacity__returns_the_expected_value)
{
   Hexagon::System::Config config(TEST_FIXTURE_CONFIG_FILENAME);
   ASSERT_EQ(0.8f, config.get_backfill_opacity());
}

