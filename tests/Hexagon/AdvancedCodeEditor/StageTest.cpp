
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>

#include <allegro5/allegro_font.h>

#include <allegro5/allegro_ttf.h>
#include <AllegroFlare/Timer.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/util.hpp>

class Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture() {}
};

class Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;

public:
   Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , font_bin()
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      al_init_primitives_addon();
      al_init_font_addon();
      al_init_ttf_addon();

      font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

      display = al_create_display(1280 * 2, 720 * 2);
      al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 0.05f});
   }

   virtual void TearDown() override
   {
      font_bin.clear();
      al_destroy_display(display);
      al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
      al_uninstall_system();
   }

   placement3d centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }
};

class Hexagon_AdvancedCodeEditor_StageTest_WithEventQueueFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   AllegroFlare::FontBin font_bin;
   ALLEGRO_EVENT_QUEUE *event_queue;

public:
   Hexagon_AdvancedCodeEditor_StageTest_WithEventQueueFixture()
      : display(nullptr)
      , font_bin()
      , event_queue(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      al_init_primitives_addon();
      al_init_font_addon();
      al_init_ttf_addon();
      al_install_keyboard();

      event_queue = al_create_event_queue();
      al_register_event_source(event_queue, al_get_keyboard_event_source());

      font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

      display = al_create_display(1280 * 2, 720 * 2);
      al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 0.05f});
   }

   virtual void TearDown() override
   {
      font_bin.clear();
      al_destroy_display(display);
      al_destroy_event_queue(event_queue);
      al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
      al_uninstall_system();
   }

   placement3d centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }
};

static std::string FIXTURE_PASSAGE = R"PASSAGE(       - 64 -
Act without doing;
work without effort.
Think of the small as large
and the few as many.
Confront the difficult
while it is still easy;
accomplish the great task
by a series of small acts.

The Master never reaches for the great;
thus she achieves greatness.
When she runs into a difficulty,
she stops and gives herself to it.
She doesn't cling to her own comfort;
thus problems are no problem for her.
)PASSAGE";

const std::string SONNET_TEXT = R"END(Sonnet 15

When I consider every thing that grows
Holds in perfection but a little moment.
That this huge stage presenteth nought but shows
Whereon the stars in secret influence comment.
When I perceive that men as plants increase,
Cheered and checked even by the self-same sky:
Vaunt in their youthful sap, at height decrease,
And wear their brave state out of memory.
Then the conceit of this inconstant stay,
Sets you most rich in youth before my sight,
Where wasteful time debateth with decay
To change your day of youth to sullied night,
And all in war with Time for love of you,
As he takes from you, I engraft you new.)END";

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   initialize__when_allegro_is_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::initialize: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, initialize__without_a_font_bin__raises_an_error)
{
   al_init();

   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::initialize: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.initialize(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture, initialize__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture, initialize__sets_initialized_to_true)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   ASSERT_EQ(false, stage.get_initialized());
   stage.initialize();
   ASSERT_EQ(true, stage.get_initialized());
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture, initialize__sets_the_cursor_width_and_height)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();

   EXPECT_EQ(10, stage.get_cursor().get_width());
   EXPECT_EQ(20, stage.get_cursor().get_height());
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, render__if_not_initialized__raises_an_error)
{
   al_init();

   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::render: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.render(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, process_local_event__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   stage.process_local_event("cursor_move_up");
   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, process_event__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   stage.process_event();
   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED_set_content__fills_the_text_mesh_with_the_expected_content)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED_set_content__if_wider_than_the_width__clips_the_filled_text_mesh)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED_set_content__if_taller_than_the_height__clips_the_filled_text_mesh)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED_set_content__will_unmark_the_content_as_modified__if_it_was_previously_modified)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED__filter_text_mesh_for_syntax_highlights__will_safely_sanitize_syntax_strings_that_are_longer_than_the_grid)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED__filter_text_mesh_for_comments__will_safely_sanitize_syntax_strings_that_are_longer_than_the_grid)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED__filter_text_mesh_for_test_case__will_safely_sanitize_syntax_strings_that_are_longer_than_the_grid)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   show_line_too_long__for_now__has_getter_and_setter_and_is_initialied_with_the_expected_default_values)
{
   // TODO it has "for now" in the test description because enabling showing the line too long should refresh the mesh
   Hexagon::AdvancedCodeEditor::Stage stage;
   EXPECT_EQ(false, stage.get_show_line_too_long());
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   max_line_length__for_now__)
{
   // TODO it has "for now" in the test description because modifying the number should trigger a refresh of the mesh
   Hexagon::AdvancedCodeEditor::Stage stage;
   EXPECT_EQ(120, stage.get_max_line_length());
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture, render__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 40, 30);
   stage.initialize();
   stage.render();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, set_content__if_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::set_content: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.set_content(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   set_content__sets_the_lines_to_the_expected_content)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 40, 30);
   stage.initialize();

   stage.set_content(FIXTURE_PASSAGE);

   std::vector<std::string> lines = stage.get_lines();

   ASSERT_EQ(16, lines.size());

   EXPECT_EQ("       - 64 -", lines[0]);
   EXPECT_EQ("Confront the difficult", lines[5]);
   EXPECT_EQ("by a series of small acts.", lines[8]);
   EXPECT_EQ("thus problems are no problem for her.", lines.back());
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   set_content__refreshes_the_mesh_to_the_expected_content)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 40, 30);
   stage.initialize();

   stage.set_content(FIXTURE_PASSAGE);

   stage.render();
   al_flip_display();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEventQueueFixture,
   DISABLED__interactive_test_works)
{
   AllegroFlare::Timer timer;
   std::string filename = std::tmpnam(nullptr);
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 123, 40);
   stage.initialize();

   stage.set_filename(filename);
   stage.set_content(FIXTURE_PASSAGE + "\n" + SONNET_TEXT);
   stage.get_place().position = vec3d(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   //stage.get_place().scale = vec3d(0.8, 0.8, 0.8);

   stage.set_current_search_regex("of");
   stage.refresh_search_regex_selections();
   
   al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 0.05f});
   stage.render();
   al_flip_display();

   //ALLEGRO_EVENT e;
   //e.type = ALLEGRO_EVENT_KEY_DOWN;
   //e.keyboard.keycode = ALLEGRO_KEY_ESCAPE;
   //EXPECT_EQ(true, al_emit_user_event(al_get_keyboard_event_source(), &e, nullptr));

   bool abort_test = false;
   while(!abort_test)
   {
      ALLEGRO_EVENT this_event;
      al_wait_for_event(event_queue, &this_event);

      if (this_event.type == ALLEGRO_EVENT_KEY_DOWN && this_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
      {
         abort_test = true;
      }
      else if (this_event.type == ALLEGRO_EVENT_KEY_CHAR)
      {
         timer.reset();
         timer.start();
         stage.process_event(this_event);
         timer.pause();
         int update_duration = timer.get_elapsed_time_microseconds();

         EXPECT_LT(200, update_duration);

         al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 0.05f});
         timer.reset();
         timer.start();
         stage.render();
         timer.pause();
         int render_duration = timer.get_elapsed_time_microseconds();

         EXPECT_LT(200, render_duration);

         al_flip_display();
      }
   }
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, delete_character__if_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::delete_character: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.delete_character(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture, delete_character__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.delete_character();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   delete_character__removes_the_character_at_the_cursor)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_content(FIXTURE_PASSAGE);

   std::vector<std::string> lines;

   lines = stage.get_lines();
   ASSERT_EQ(16, lines.size());

   EXPECT_EQ("Act without doing;", lines[1]);

   stage.cursor_move_down();
   stage.delete_character();
   stage.cursor_move_right();
   stage.cursor_move_right();
   stage.cursor_move_right();
   stage.delete_character();

   lines = stage.get_lines();
   EXPECT_EQ("ct ithout doing;", lines[1]);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_delete_character__refreshes_the_text_mesh)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_delete_word_under_character__with_the_cursor_out_of_bounds__returns_false)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_delete_word_under_character__when_the_cursor_is_not_over_a_word__returns_false)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_delete_word_under_character__removes_the_word_underneath_the_cursor)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_delete_word_under_character__returns_true)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_delete_word_under_character__moves_the_cursor_to_the_beginning_of_the_word_that_was_deleted)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_delete_word_under_character__refreshes_the_text_mesh)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   grab_word_under_cursor__will_return_the_word_under_the_cursor)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 40, 30);
   stage.initialize();

   stage.set_content(FIXTURE_PASSAGE);
   stage.cursor_move_to(21, 11);

   std::string expected_word_under_cursor = "greatness";
   std::string actual_word_under_cursor = stage.grab_word_under_cursor();

   EXPECT_EQ(expected_word_under_cursor, actual_word_under_cursor);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   grab_word_under_cursor__if_the_cursor_is_out_of_bounds__will_return_an_empty_string)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   grab_word_under_cursor__if_there_is_no_word_under_the_cursor__will_return_an_empty_string)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, join_lines__if_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::join_lines: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.join_lines(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   join_lines__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_content(SONNET_TEXT);
   stage.join_lines();
   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   join_lines__on_the_last_line__does_nothing_and_returns_false)
{
   std::vector<std::string> lines;
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_content(SONNET_TEXT);

   lines = stage.get_lines();
   ASSERT_TRUE(stage.cursor_move_to(0, lines.size()-1));

   std::string &current_cursor_line = lines[stage.get_cursor().get_y()];
   EXPECT_EQ("As he takes from you, I engraft you new.", current_cursor_line);

   ASSERT_EQ(false, stage.join_lines());

   std::string &current_cursor_line_after_action = lines[stage.get_cursor().get_y()];
   EXPECT_EQ("As he takes from you, I engraft you new.", current_cursor_line_after_action);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   join_lines__on_a_line_number_that_is_out_of_bounds__does_nothing_and_returns_false)
{
   std::vector<std::string> lines, original_lines;
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_content(SONNET_TEXT);

   original_lines = stage.get_lines();

   int line_numbers_to_test[] = { -1, (int)(original_lines.size()+10), -10, };

   for (auto &line_number_to_test : line_numbers_to_test)
   {
      stage.cursor_move_to(0, line_number_to_test);

      ASSERT_EQ(false, stage.join_lines());

      lines = stage.get_lines();
      ASSERT_EQ(lines, original_lines);
   }
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   join_lines__will_concat_the_contents_of_the_current_line_and_the_line_below_it_and_returns_true)
{
   std::vector<std::string> lines;
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_content(SONNET_TEXT);

   stage.cursor_move_to(0, 4);
   ASSERT_EQ(true, stage.join_lines());

   std::string expected_line_at_cursor = "That this huge stage presenteth nought but showsWhereon the stars in " \
                                         "secret influence comment.";

   std::string expected_line_below_cursor = "When I perceive that men as plants increase,";

   lines = stage.get_lines();

   std::string &actual_line_at_cursor = lines[stage.get_cursor().get_y()];
   ASSERT_EQ(expected_line_at_cursor, actual_line_at_cursor);

   std::string &actual_line_below_cursor = lines[stage.get_cursor().get_y()+1];
   ASSERT_EQ(expected_line_below_cursor, actual_line_below_cursor);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   cursor_jump_up_half_page__will_move_the_cursor_up_half_the_number_of_rows_of_the_window)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   cursor_jump_up_half_page__if_it_would_jump_beyond_the_top_line__will_set_the_cursor_on_the_first_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   cursor_jump_down_half_page__will_move_the_cursor_down_half_the_number_of_rows_of_the_window)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   cursor_jump_down_half_page__if_it_would_jump_beyond_the_bottom_line__will_set_the_cursor_to_the_bottom_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   join_lines__refreshes_the_text_mesh)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, split_lines__if_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::split_lines: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.split_lines(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture, delete_line__if_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::delete_line: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.delete_line(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   delete_line__will_remove_all_existing_message_points_on_that_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   delete_line__will_move_up_all_existing_message_points_after_the_deleted_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   join_lines__will_remove_all_code_message_points_on_the_subsequent_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   join_lines__will_refresh_hilights_on_the_current_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   join_lines__will_move_up_all_existing_message_points_after_the_deleted_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   split_lines__will_refresh_all_code_message_points_on_the_current_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   split_lines__will_refresh_all_code_message_points_on_the_subsequent_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   split_lines__will_shift_down_all_code_message_points_after_initial_first_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   delete_character__will_refresh_the_regex_search_code_message_points_on_the_current_line)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   insert_blank_line__will_insert_a_blank_line_at_the_cursor)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED_insert_three_spaces_at_start_of_line__TODO)
{
   // TODO
   // will insert three spaces at the beginning
   // will position the cursor over by three spaces
   // will do nothing if outsize the bounds of existing lines
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   DISABLED_insert_three_spaces_at_start_of_line__will_mark_content_as_modified)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   insert_string_from_input_buffer__if_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::insert_string_from_input_buffer: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.insert_string_from_input_buffer(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   insert_string_from_input_buffer__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.insert_string_from_input_buffer();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   insert_lines__if_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::insert_lines: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.insert_lines(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_insert_string_from_input_buffer__when_the_cursor_is_out_of_bounds__does_nothing_and_returns_false)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   insert_string_from_input_buffer__inserts_the_string_to_the_content_and_returns_true)
{
   std::vector<std::string> lines;
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_content(SONNET_TEXT);

   stage.cursor_move_to(14, 4);

   lines = stage.get_lines();
   EXPECT_EQ("That this huge stage presenteth nought but shows", lines[4]);

   stage.set_input_buffer(", massive");
   ASSERT_EQ(true, stage.insert_string_from_input_buffer());

   lines = stage.get_lines();
   EXPECT_EQ("That this huge, massive stage presenteth nought but shows", lines[4]);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_insert_string__refreshes_the_text_mesh)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   save_file__will_create_the_file_from_the_filename_if_it_does_not_already_exist)
{
   std::string filename = std::tmpnam(nullptr);

   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_filename(filename);
   stage.set_content(SONNET_TEXT);

   ASSERT_EQ(false, Blast::FileExistenceChecker(filename).exists());

   ASSERT_EQ(true, stage.save_file());

   ASSERT_EQ(true, Blast::FileExistenceChecker(filename).exists());
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   save_file__will_save_the_current_content_to_the_file)
{
   std::string filename = std::tmpnam(nullptr);

   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_filename(filename);
   stage.set_content(SONNET_TEXT);

   ASSERT_EQ(true, stage.save_file());

   std::vector<std::string> lines_read_from_created_file;
   ASSERT_EQ(true, ::read_file(lines_read_from_created_file, filename));

   std::vector<std::string> lines_from_stage = stage.get_lines();

   ASSERT_EQ(lines_read_from_created_file, lines_from_stage);
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   save_file_and_touch_if_symlink__will_create_the_file_from_the_filename_if_it_does_not_already_exist)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   save_file_and_touch_if_symlink__will_save_the_current_content_to_the_file)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   save_file_and_touch_if_symlink__will_touch_the_symlink_file_in_order_to_update_the_modified_file_timestamp)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   save_file__and__save_file_and_touch_if_symlink__will_mark_content_as_unmodified)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   first_row_offset_jump_up_half_page__will_move_the_first_row_offset_up_by_half_the_number_of_rows)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   first_row_offset_jump_down_half_page__will_move_the_first_row_offset_down_by_half_the_number_of_rows)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   first_row_offset_adjust_so_cursor_is_vertically_centered__will_move_the_first_row_offset_to_center_the_cursor)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED__render__will_respect_the_first_row_offset)
{
   std::string filename = std::tmpnam(nullptr);

   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 50, 40);
   stage.initialize();
   stage.set_filename(filename);
   stage.set_content(SONNET_TEXT);

   stage.get_place().position = vec3d(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);

   stage.render();

   for (int i=0; i<50; i++)
   {
      al_clear_to_color(al_color_name("black"));
      stage.first_row_offset_move_up();
      stage.render();
      al_flip_display();
      //usleep(18000*2);
   }
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   build_dirty_grid_from_lines_respecting_offset__will_create_a_drity_grid_of_the_current_lines__respecting_offset)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 69, 420);
   stage.initialize();
   std::string content = "This line that will not appear,\nbecause\noffset\nhere.";
   stage.set_content(content);

   stage.first_row_offset_move_down();
   Hexagon::DirtyGrid dirty_grid = stage.build_dirty_grid_from_lines_respecting_offset();
   ASSERT_EQ(18, dirty_grid.build_vector().size());
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   build_dirty_grid_from_lines_respecting_offset__respects_negative_values_for_offset)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 69, 420);
   stage.initialize();
   std::string content = "because\noffset\nhere.";
   stage.set_content(content);

   stage.first_row_offset_move_up();
   Hexagon::DirtyGrid dirty_grid = stage.build_dirty_grid_from_lines_respecting_offset();
   ASSERT_EQ(18, dirty_grid.build_vector().size());
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   calculate_natural_width__returns_the_expected_width)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   calculate_natural_height__returns_the_expected_width)
{
   // TODO
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED__cursor_jump_to_next_code_message_point__will_move_the_cursor_to_the_next_code_message_point)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 40, 30);
   stage.initialize();
   stage.get_place().position = vec3d(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   std::vector<CodeMessagePoint> code_message_points = { { 3, 3, 9 } };
   stage.set_content(FIXTURE_PASSAGE);
   stage.set_code_message_points(code_message_points);

   // TODO
   stage.cursor_jump_to_next_code_message_point();

   stage.render();
   al_flip_display();
   sleep(2);
}

TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   keyboard_input__SHIFT__KEY_O__will_insert_a_newline)
{
   // TODO
}

