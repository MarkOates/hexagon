#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/StageFactory.hpp>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/UI/LittleMenu.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <Hexagon/UI/DrawingBox.hpp>
#include <Hexagon/Notifications/Stage.hpp>

TEST(Hexagon_StageFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::StageFactory stage_factory;
}

TEST(Hexagon_StageFactoryTest, obtain_component_navigator_font__without_a_font_bin__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::obtain_component_navigator_font: error: guard " \
                                        "\"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(
      stage_factory.obtain_component_navigator_font(),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Hexagon_StageFactoryTest, obtain_component_navigator_font__returns_a_font)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::StageFactory stage_factory(nullptr, &font_bin);

   ALLEGRO_FONT *font = stage_factory.obtain_component_navigator_font();

   ASSERT_NE(nullptr, font);

   font_bin.clear();
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest, obtain_git_commit_message_box_font__without_a_font_bin__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::obtain_git_commit_message_box_font: error: guard " \
                                        "\"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(
      stage_factory.obtain_git_commit_message_box_font(),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Hexagon_StageFactoryTest, obtain_git_commit_message_box_font__returns_a_font)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::StageFactory stage_factory(nullptr, &font_bin);

   ALLEGRO_FONT *font = stage_factory.obtain_git_commit_message_box_font();

   ASSERT_NE(nullptr, font);

   font_bin.clear();
   al_shutdown_ttf_addon();
   al_uninstall_system();
}


TEST(Hexagon_StageFactoryTest,
   create_notification__creates_a_notificaiton_with_the_expected_properties)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config, &font_bin);

   std::string notification_body_text = "This is the notification text.";
   StageInterface *created_stage = stage_factory.create_notification(notification_body_text);
   Hexagon::Notifications::Stage *stage = static_cast<Hexagon::Notifications::Stage*>(created_stage);

   ASSERT_NE(nullptr, created_stage);

   StageInterface::type_t expected_type = StageInterface::NOTIFICATION;
   StageInterface::type_t actual_type = created_stage->get_type();
   Hexagon::Notifications::Notification &notification = stage->get_component_ref();

   ASSERT_EQ(expected_type, actual_type);
   EXPECT_EQ(true, stage->get_render_on_hud());
   EXPECT_EQ(notification_body_text, notification.get_body_text());

   font_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}


TEST(Hexagon_StageFactoryTest,
   create_class_brief_menu__creates_a_class_brief_menu_stage_with_the_expected_properties)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config, &font_bin);

   StageInterface *created_stage = stage_factory.create_class_brief_menu();
   Hexagon::UI::LittleMenu *stage = static_cast<Hexagon::UI::LittleMenu*>(created_stage);

   StageInterface::type_t expected_type = StageInterface::LITTLE_MENU;
   StageInterface::type_t actual_type = created_stage->get_type();

   ASSERT_NE(nullptr, created_stage);
   ASSERT_EQ(expected_type, actual_type);

   EXPECT_EQ(true, stage->get_render_on_hud());

   font_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}


TEST(Hexagon_StageFactoryTest,
   create_drawing_box__creates_a_drawing_box_tage_with_the_expected_properties)
{
   // TODO
}


TEST(Hexagon_StageFactoryTest,
   create_fancy__creates_a_fancy_stage_with_the_expected_properties)
{
   // TODO
}


TEST(Hexagon_StageFactoryTest,
   create_missing_file__creates_a_missing_file_stage_with_the_expected_properties)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *created_stage = stage_factory.create_missing_file();
   Hexagon::MissingFile::Stage *stage = static_cast<Hexagon::MissingFile::Stage*>(created_stage);

   StageInterface::type_t expected_type = StageInterface::MISSING_FILE;
   StageInterface::type_t actual_type = created_stage->get_type();

   ASSERT_NE(nullptr, created_stage);
   ASSERT_EQ(expected_type, actual_type);

   ALLEGRO_FONT *expected_font = stage_factory.obtain_global_font();
   ALLEGRO_FONT *actual_font = stage->get_font();

   EXPECT_EQ(expected_font, actual_font);

   EXPECT_EQ(10, stage->get_cell_width());
   EXPECT_EQ(20, stage->get_cell_height());
   EXPECT_EQ(display, stage->get_display());

   font_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest,
   create_code_editor__creates_a_code_editor_stage_with_the_expected_properties)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   std::string filename = "foobar.txt";
   std::string file_category = "whatever";
   StageInterface *created_stage = stage_factory.create_code_editor(filename, file_category);

   ASSERT_NE(nullptr, created_stage);

   StageInterface::type_t expected_type = StageInterface::CODE_EDITOR;
   StageInterface::type_t actual_type = created_stage->get_type();

   ASSERT_EQ(expected_type, actual_type);

   Hexagon::CodeEditor::Stage *stage = static_cast<Hexagon::CodeEditor::Stage*>(created_stage);
   ::CodeEditor::CodeEditor *code_editor = &stage->get_code_editor_ref();

   ASSERT_EQ(filename, code_editor->get_filename());
   ASSERT_EQ(file_category, code_editor->get_file_category());

   ALLEGRO_FONT *expected_font = stage_factory.obtain_global_font();
   ALLEGRO_FONT *actual_font = stage->get_font();

   EXPECT_EQ(expected_font, actual_font);
   EXPECT_EQ(10, stage->get_cell_width());
   EXPECT_EQ(20, stage->get_cell_height());
   EXPECT_EQ(display, stage->get_display());

   font_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest,
   create_advanced_code_editor__creates_a_code_editor_stage_with_the_expected_properties)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *created_stage = stage_factory.create_advanced_code_editor("foobar_filename.htm", 80, 35);

   ASSERT_NE(nullptr, created_stage);

   StageInterface::type_t expected_type = StageInterface::ADVANCED_CODE_EDITOR;
   StageInterface::type_t actual_type = created_stage->get_type();

   ASSERT_EQ(expected_type, actual_type);

   Hexagon::AdvancedCodeEditor::Stage *stage = static_cast<Hexagon::AdvancedCodeEditor::Stage*>(created_stage);
   EXPECT_EQ(80, stage->get_num_columns());
   EXPECT_EQ(35, stage->get_num_rows());
   EXPECT_EQ("foobar_filename.htm", stage->get_filename());

   font_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest,
   create_delete_multiplex_menu__creates_a_multiplex_menu_with_the_expected_properties)
{
   // TODO
}

TEST(Hexagon_StageFactoryTest,
   create_git_commit_message_box__creates_a_git_commit_message_box_with_the_expected_properties)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *created_stage = stage_factory.create_git_commit_message_box();
   Hexagon::CodeEditor::Stage *stage = static_cast<Hexagon::CodeEditor::Stage*>(created_stage);

   StageInterface::type_t expected_type = StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX;
   StageInterface::type_t actual_type = created_stage->get_type();

   ASSERT_NE(nullptr, created_stage);
   ASSERT_EQ(expected_type, actual_type);

   ALLEGRO_FONT *expected_font = stage_factory.obtain_git_commit_message_box_font();
   ALLEGRO_FONT *actual_font = stage->get_font();

   EXPECT_EQ(expected_font, actual_font);

   font_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest, DISABLED__create_advanced_component_navigator__without_a_config__raises_an_exception)
{
   // TODO
}

TEST(Hexagon_StageFactoryTest, create_advanced_component_navigator__without_a_font_bin__raises_an_exception)
{
   //AllegroFlare::FontBin font_bin;
   Hexagon::StageFactory stage_factory(nullptr, nullptr);//&font_bin);

   std::string expected_error_message = "StageFactory::create_advanced_component_navigator: error: guard " \
                                        "\"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(
      stage_factory.create_advanced_component_navigator(),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Hexagon_StageFactoryTest, obtain_regex_temp_filename__without_a_config__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::obtain_regex_temp_filename: error: guard " \
                                        "\"config\" not met";
   ASSERT_THROW_WITH_MESSAGE(
      stage_factory.obtain_regex_temp_filename(),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Hexagon_StageFactoryTest, obtain_base_text_color__without_a_config__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::obtain_base_text_color: error: guard \"config\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_factory.obtain_base_text_color(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_StageFactoryTest,
   create_advanced_component_navigator__creates_an_advanced_component_navigator_with_the_expected_properties)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *created_stage = stage_factory.create_advanced_component_navigator();
   Hexagon::AdvancedComponentNavigator::Stage *stage =
      static_cast<Hexagon::AdvancedComponentNavigator::Stage*>(created_stage);

   StageInterface::type_t expected_type = StageInterface::COMPONENT_NAVIGATOR;
   StageInterface::type_t actual_type = created_stage->get_type();

   ASSERT_NE(nullptr, created_stage);
   ASSERT_EQ(expected_type, actual_type);

   ALLEGRO_COLOR expected_base_text_color = config.get_base_text_color();
   ALLEGRO_COLOR actual_base_text_color = stage->get_base_text_color();

   ALLEGRO_COLOR expected_base_backfill_color = config.get_backfill_color();
   ALLEGRO_COLOR actual_base_backfill_color = stage->get_base_backfill_color();

   placement3d expected_place = stage_factory.build_component_navigator_initial_place();
   placement3d actual_place = stage->get_place();

   //EXPECT_EQ(true, stage->get_render_on_hud());
   EXPECT_EQ(expected_base_text_color.r, actual_base_text_color.r); // for now, just comparing red component
   EXPECT_EQ(expected_base_backfill_color.r, actual_base_backfill_color.r); // for now, just comparing red component
   EXPECT_EQ(expected_place, actual_place);
   //EXPECT_EQ(9, stage->get_cell_width());
   //EXPECT_EQ(18, stage->get_cell_height());
   EXPECT_EQ(4, stage->get_cell_width());
   EXPECT_EQ(19, stage->get_cell_height());

   font_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest, create_file_navigator__creates_a_file_navigator_with_the_expected_properties)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *created_stage = stage_factory.create_file_navigator();
   Hexagon::FileNavigator::Stage *stage = static_cast<Hexagon::FileNavigator::Stage*>(created_stage);

   StageInterface::type_t expected_type = StageInterface::FILE_NAVIGATOR;
   StageInterface::type_t actual_type = created_stage->get_type();

   ASSERT_NE(nullptr, created_stage);
   ASSERT_EQ(expected_type, actual_type);

   EXPECT_EQ(true, stage->get_render_on_hud());

   ALLEGRO_FONT *expected_font = stage_factory.obtain_file_navigator_font();
   ALLEGRO_FONT *actual_font = stage->get_font();

   EXPECT_EQ(expected_font, actual_font);

   font_bin.clear();
   al_destroy_display(display);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryText,
   create_component_relations_navigator__creates_a_component_relations_navigator_with_the_expected_properties)
{
   // TODO
}

TEST(Hexagon_StageFactoryTest, get_current_display__when_allegro_is_not_initialized__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::get_current_display: error: guard " \
                                        "\"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_factory.get_current_display(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_StageFactoryTest, get_current_display__without_a_current_display__raises_an_exception)
{
   al_init();
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::get_current_display: error: guard " \
                                        "\"al_get_current_display()\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_factory.get_current_display(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest, get_current_display__returns_the_current_display)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   Hexagon::StageFactory stage_factory;
   ALLEGRO_DISPLAY *expected_display = display;
   ASSERT_EQ(expected_display, stage_factory.get_current_display());

   al_destroy_display(display);
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest, build_component_navigator_initial_place__returns_the_expected_position)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   Hexagon::StageFactory stage_factory;

   vec3d expected_placement_position = vec3d(1920/2, 1080/2, 0);
   placement3d actual_placement = stage_factory.build_component_navigator_initial_place();

   ASSERT_EQ(expected_placement_position, actual_placement.position);

   al_destroy_display(display);
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest, build_centered_on_hud_initial_place__returns_the_expected_position)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   Hexagon::StageFactory stage_factory;

   vec3d expected_placement_position = vec3d(1920/2, 1080/2, 0);
   float expected_placement_width = 120;
   float expected_placement_height = 160;
   placement3d actual_placement = stage_factory.build_centered_on_hud_initial_place(
      expected_placement_width,
      expected_placement_height
      );

   ASSERT_EQ(expected_placement_position, actual_placement.position);
   ASSERT_EQ(expected_placement_width, actual_placement.size.x);
   ASSERT_EQ(expected_placement_height, actual_placement.size.y);

   al_destroy_display(display);
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest, build_regex_input_box_initial_place__returns_the_expected_position)
{
   // this is untested
}

