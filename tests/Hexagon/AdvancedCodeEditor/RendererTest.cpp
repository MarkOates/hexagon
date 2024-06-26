#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <Hexagon/Testing/ErrorAssertions.hpp>

#include <cmath>

class Hexagon_AdvancedCodeEditor_RendererTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Renderer renderer;
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithEmptyFixture, render__without_a_valid_text_mesh__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Renderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::AdvancedCodeEditor::Renderer::render",
      "text_mesh"
   );
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithEmptyFixture, render__without_a_valid_cursor__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_BITMAP *bitmap = al_create_bitmap(16*40, 9*40);
   al_set_target_bitmap(bitmap);
   ALLEGRO_FONT *font = al_create_builtin_font();
   std::vector<Hexagon::AdvancedCodeEditor::Selection> selections;
   std::vector<std::string> lines;
   Hexagon::Elements::TextMesh text_mesh(font);
   text_mesh.initialize();

   Hexagon::AdvancedCodeEditor::Renderer renderer(
      &text_mesh,
      nullptr,
      nullptr,
      &selections,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      &lines
   );
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "Hexagon::AdvancedCodeEditor::Renderer::render_cursor",
      "cursor"
   );

   al_destroy_font(font);
   al_destroy_bitmap(bitmap);
   al_uninstall_system();
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture, render__does_not_blow_up)
{
   ALLEGRO_FONT *font = get_any_font();
   Hexagon::Elements::TextMesh text_mesh(font);
   std::vector<Hexagon::AdvancedCodeEditor::Selection> selections;
   std::vector<std::string> lines;
   text_mesh.initialize();

   Hexagon::AdvancedCodeEditor::Cursor cursor(0, 0, text_mesh.get_cell_width(), text_mesh.get_cell_height());

   placement3d place = build_centered_placement(800, 600);
   Hexagon::AdvancedCodeEditor::Renderer renderer(
      &text_mesh,
      nullptr,
      &cursor,
      &selections,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      &lines,
      place.size.x,
      place.size.y
   );

   place.start_transform();
   renderer.render();
   place.restore_transform();

   al_flip_display();

   //sleep(1);

   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture,
   render__when_draw_line_numbers_is_true__renders_the_line_numbers)
{
   ALLEGRO_FONT *font = get_any_font();
   Hexagon::Elements::TextMesh text_mesh(font);
   std::vector<Hexagon::AdvancedCodeEditor::Selection> selections;
   std::vector<std::string> lines;
   text_mesh.initialize();

   Hexagon::AdvancedCodeEditor::Cursor cursor(0, 0, text_mesh.get_cell_width(), text_mesh.get_cell_height());

   placement3d place = build_centered_placement(800, 600);
   Hexagon::AdvancedCodeEditor::Renderer renderer(
      &text_mesh,
      nullptr,
      &cursor,
      &selections,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      &lines,
      place.size.x,
      place.size.y
   );
   renderer.set_show_line_numbers(true);
   renderer.set_font(font);

   place.start_transform();
   renderer.render();
   place.restore_transform();

   al_flip_display();

   //sleep(1);

   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture,
   render__when_cursor_is_bar_is_set__renders_the_cursor_as_a_bar)
{
   ALLEGRO_FONT *font = get_any_font();
   Hexagon::Elements::TextMesh text_mesh(font, 200, 100);
   std::vector<Hexagon::AdvancedCodeEditor::Selection> selections;
   std::vector<std::string> lines;
   text_mesh.initialize();

   Hexagon::AdvancedCodeEditor::Cursor cursor(0, 0, text_mesh.get_cell_width(), text_mesh.get_cell_height());

   placement3d place = build_centered_placement(800, 600);
   Hexagon::AdvancedCodeEditor::Renderer renderer(
      &text_mesh,
      nullptr,
      &cursor,
      &selections,
      nullptr,
      nullptr,
      nullptr,
      nullptr,
      &lines,
      place.size.x,
      place.size.y
   );

   place.start_transform();
   renderer.render();
   place.restore_transform();

   al_flip_display();

   //sleep(1);

   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture,
   render___respects_the_mesh_y_offset__and_renders_the_cursor_by_the_offset_as_well)
{
   ALLEGRO_FONT *font = get_any_font();
   Hexagon::Elements::TextMesh text_mesh(font, 30, 20);
   std::vector<Hexagon::AdvancedCodeEditor::Selection> selections;
   std::vector<std::string> lines;
   text_mesh.initialize();

   float width = text_mesh.calculate_width();
   float height = text_mesh.calculate_height();

   ALLEGRO_BITMAP *bitmap = al_create_bitmap(width, height);
   ALLEGRO_STATE previous_drawing_state;
   al_store_state(&previous_drawing_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(bitmap);
   al_clear_to_color(al_color_name("orange"));
   al_restore_state(&previous_drawing_state);

   Hexagon::AdvancedCodeEditor::Cursor cursor(0, 0, text_mesh.get_cell_width(), text_mesh.get_cell_height());

   placement3d place = build_centered_placement(width, height);

   float text_mesh_offset = 0.0f;

   int num_seconds = 1;
   float start_text_mesh_y_offset = 140;
   for (unsigned i=0; i<(60 * num_seconds); i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0,0,0,1});
      float text_mesh_y_offset = std::sin(al_get_time() * 5.0) * 200.0f;

      Hexagon::AdvancedCodeEditor::Renderer renderer(
         &text_mesh,
         bitmap,
         &cursor,
         &selections,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         &lines,
         place.size.x,
         place.size.y,
         false,
         text_mesh_y_offset
      );

      place.start_transform();
      renderer.render();
      place.restore_transform();

      al_flip_display();
   }

   al_destroy_bitmap(bitmap);

   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture, DISABLED__render___renders_the_selections)
{
   ALLEGRO_FONT *font = get_any_font();
   Hexagon::Elements::TextMesh text_mesh(font, 30, 20);
   std::vector<Hexagon::AdvancedCodeEditor::Selection> selections = {
      Hexagon::AdvancedCodeEditor::Selection{
         std::vector<CodeRange>{
            CodeRange{0, 0, 1, 0},
            CodeRange{4, 5, 10, 6},
            CodeRange{4, 9, 10, 11},
         },
      },
   };
   std::vector<std::string> lines;
   text_mesh.initialize();

   float width = text_mesh.calculate_width();
   float height = text_mesh.calculate_height();

   ALLEGRO_BITMAP *bitmap = al_create_bitmap(width, height);
   ALLEGRO_STATE previous_drawing_state;
   al_store_state(&previous_drawing_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(bitmap);
   al_clear_to_color(al_color_name("orange"));
   al_restore_state(&previous_drawing_state);

   Hexagon::AdvancedCodeEditor::Cursor cursor(0, 0, text_mesh.get_cell_width(), text_mesh.get_cell_height());

   placement3d place = build_centered_placement(width, height);

   float text_mesh_offset = 0.0f;

   int num_seconds = 1;
   float start_text_mesh_y_offset = 140;
   for (unsigned i=0; i<(60 * num_seconds); i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0,0,0,1});
      float text_mesh_y_offset = std::sin(al_get_time() * 5.0) * 200.0f;

      Hexagon::AdvancedCodeEditor::Renderer renderer(
         &text_mesh,
         bitmap,
         &cursor,
         &selections,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         &lines,
         place.size.x,
         place.size.y,
         false,
         text_mesh_y_offset
      );

      place.start_transform();
      renderer.render();
      place.restore_transform();

      al_flip_display();
   }

   al_destroy_bitmap(bitmap);

   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture, render___renders_the_code_message_points)
{
   ALLEGRO_FONT *font = get_any_font();
   Hexagon::Elements::TextMesh text_mesh(font, 30, 20);
   std::vector<CodeMessagePoint> code_message_points = {
      CodeMessagePoint{5, 0, 10},
   };
   std::vector<std::string> lines;
   text_mesh.initialize();

   float width = text_mesh.calculate_width();
   float height = text_mesh.calculate_height();

   ALLEGRO_BITMAP *bitmap = al_create_bitmap(width, height);
   ALLEGRO_STATE previous_drawing_state;
   al_store_state(&previous_drawing_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(bitmap);
   al_clear_to_color(al_color_name("orange"));
   al_restore_state(&previous_drawing_state);

   Hexagon::AdvancedCodeEditor::Cursor cursor(0, 0, text_mesh.get_cell_width(), text_mesh.get_cell_height());

   placement3d place = build_centered_placement(width, height);

   float text_mesh_offset = 0.0f;

   int num_seconds = 1;
   float start_text_mesh_y_offset = 140;
   for (unsigned i=0; i<(60 * num_seconds); i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0,0,0,1});
      float text_mesh_y_offset = std::sin(al_get_time() * 5.0) * 200.0f;

      Hexagon::AdvancedCodeEditor::Renderer renderer(
         &text_mesh,
         bitmap,
         &cursor,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         &code_message_points,
         &lines,
         place.size.x,
         place.size.y,
         false,
         text_mesh_y_offset
      );
      renderer.set_font(font);

      place.start_transform();
      renderer.render();
      place.restore_transform();

      al_flip_display();
   }

   al_destroy_bitmap(bitmap);

   SUCCEED();
}


TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture,
   render___with_represents_symlink_on__renders_the_expected_style)
{
   // TODO
}


