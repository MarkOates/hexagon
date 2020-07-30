
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture, initialize__sets_the_cursor_width_and_height)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();

   EXPECT_EQ(16, stage.get_cursor_ref().get_width());
   EXPECT_EQ(30, stage.get_cursor_ref().get_height());
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
   DISABLED_set_content__sets_the_lines_to_the_expected_content)
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


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture, delete_character__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.delete_character();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_delete_character__removes_the_character_at_the_cursor)
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

   std::string &current_cursor_line = lines[stage.get_cursor_ref().get_y()];
   EXPECT_EQ("As he takes from you, I engraft you new.", current_cursor_line);

   ASSERT_EQ(false, stage.join_lines());

   std::string &current_cursor_line_after_action = lines[stage.get_cursor_ref().get_y()];
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
   DISABLED_join_lines__will_concat_the_contents_of_the_current_line_and_the_line_below_it_and_returns_true)
{
   std::vector<std::string> lines;
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_content(SONNET_TEXT);

   stage.cursor_move_to(0, 4);
   ASSERT_EQ(true, stage.join_lines());

   std::string expected_line_at_cursor = "That this huge stage presenteth nought but showsWhereon the stars in secret " \
                                         "influence comment.";

   std::string expected_line_below_cursor = "When I perceive that men as plants increase,";

   lines = stage.get_lines();

   std::string &actual_line_at_cursor = lines[stage.get_cursor_ref().get_y()];
   ASSERT_EQ(expected_line_at_cursor, actual_line_at_cursor);

   std::string &actual_line_below_cursor = lines[stage.get_cursor_ref().get_y()+1];
   ASSERT_EQ(expected_line_below_cursor, actual_line_below_cursor);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithEmptyFixture,
   join_lines__refreshes_the_text_mesh)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture, insert_string__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.insert_string();
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_insert_string__when_the_cursor_is_out_of_bounds__does_nothing_and_returns_false)
{
   // TODO
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_insert_string__inserts_the_string_to_the_content_and_returns_true)
{
   std::vector<std::string> lines;
   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 30, 40);
   stage.initialize();
   stage.set_content(SONNET_TEXT);

   stage.cursor_move_to(14, 4);

   lines = stage.get_lines();
   EXPECT_EQ("That this huge stage presenteth nought but shows", lines[4]);

   ASSERT_EQ(true, stage.insert_string(", massive"));

   lines = stage.get_lines();
   EXPECT_EQ("That this huge, massive stage presenteth nought but shows", lines[4]);
}


TEST_F(Hexagon_AdvancedCodeEditor_StageTest_WithAllegroRenderingFixture,
   DISABLED_insert_string__refreshes_the_text_mesh)
{
   // TODO
}

