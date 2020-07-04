
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer;
}

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest, render__will_render_the_text_as_expected)
{
   al_init();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(800, 460);
   ALLEGRO_FONT *font = al_create_builtin_font();
   ALLEGRO_COLOR font_color = al_color_name("white");
   ALLEGRO_COLOR backfill_color = al_color_name("black");

   EXPECT_NE(nullptr, font);

   float x = 100;
   float y = al_get_display_height(display)/2;
   std::string text = "Hello World!";

   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer(
      font, &font_color, &backfill_color, x, y, text
   );

   al_clear_to_color(al_color_name("black"));
   advanced_line_renderer.render();
   al_flip_display();

   //sleep(1);

   al_destroy_font(font);
   al_destroy_display(display);

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest, render__will_render_quoted_strings_with_a_different_color)
{
   al_init();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(800, 460);
   ALLEGRO_FONT *font = al_create_builtin_font();
   ALLEGRO_COLOR font_color = al_color_name("white");
   ALLEGRO_COLOR backfill_color = al_color_name("black");

   EXPECT_NE(nullptr, font);

   float x = 100;
   float y = al_get_display_height(display)/2;
   std::string text = "Hello World! \"Quoted string\" woo \"A second string\"";

   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer(
      font, &font_color, &backfill_color, x, y, text
   );

   al_clear_to_color(al_color_name("black"));
   advanced_line_renderer.render();
   al_flip_display();

   //sleep(1);

   al_destroy_font(font);
   al_destroy_display(display);

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest,
   render__will_properly_render_comments_outside_and_inside_quoted_strings)
{
   al_init();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1000, 460);
   ALLEGRO_FONT *font = al_create_builtin_font();
   ALLEGRO_COLOR font_color = al_color_name("white");
   ALLEGRO_COLOR backfill_color = al_color_name("black");

   EXPECT_NE(nullptr, font);

   float x = 100;
   float y = al_get_display_height(display)/2;
   std::string text = "Hello World! \"Quoted string // that has comments\" woo // comment that has \"A second string\"";

   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer(
      font, &font_color, &backfill_color, x, y, text
   );

   al_clear_to_color(al_color_name("black"));
   advanced_line_renderer.render();
   al_flip_display();

   //sleep(1);

   al_destroy_font(font);
   al_destroy_display(display);

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest,
   build_quintessence_yaml_name_element_tokens__will_hilight_single_indented_yaml_name_element)
{
   al_init();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1000, 460);
   ALLEGRO_FONT *font = al_create_builtin_font();
   ALLEGRO_COLOR font_color = al_color_name("white");
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   al_clear_to_color(al_color_name("black"));

   EXPECT_NE(nullptr, font);

   float x = 100;
   float y = al_get_display_height(display)/2;

   std::vector<std::string> texts = {
      "  - name: function_or_property_name",
      "    name: another_function_or_property_name",
      "    name:something_that_should_not_hilight",
      "    namely: something_that_is_not_a_property_name",
      "   name: a_not_properly_indented_name",
   };

   int passes = 0;
   for (auto &text : texts)
   {
      Hexagon::CodeEditor::Renderer::AdvancedLineRenderer(
         font, &font_color, &backfill_color, x, y + 20*passes, text
      ).render();
      passes++;
   }

   al_flip_display();

   //sleep(1);

   al_destroy_font(font);
   al_destroy_display(display);

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest,
   render_tokens__only_renders_characters_that_are_within_the_bounds_of_the_max_num_columns)
{
   al_init();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1000, 460);
   ALLEGRO_FONT *font = al_create_builtin_font();
   ALLEGRO_COLOR font_color = al_color_name("white");
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   al_clear_to_color(al_color_name("black"));

   EXPECT_NE(nullptr, font);

   float x = 100;
   float y = al_get_display_height(display)/2;

   std::vector<std::string> texts = {
      "    carat_should_render: ^",
      " carat_should_not_render: ^",
      "  - name: an_decorated_identifier_that_extends_beyond_the_column_concatination",
      "    type: std::string",
      "    body: |",
      "      std::string concatinated_string = \"a special decorated string that starts beyond the column limit\"",
      "      return concatinated_string",
   };

   int passes = 0;
   for (auto &text : texts)
   {
      Hexagon::CodeEditor::Renderer::AdvancedLineRenderer(
         font, &font_color, &backfill_color, x, y + 20*passes, text, 26
      ).render();
      passes++;
   }

   al_flip_display();

   sleep(2);

   al_destroy_font(font);
   al_destroy_display(display);

   al_uninstall_system();
}

