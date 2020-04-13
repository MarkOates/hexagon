
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
   ALLEGRO_COLOR color = al_color_name("white");

   EXPECT_NE(nullptr, font);

   float x = al_get_display_width(display)/2;
   float y = al_get_display_height(display)/2;
   std::string text = "Hello World!";

   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer(font, &color, x, y, text);

   al_clear_to_color(al_color_name("black"));
   advanced_line_renderer.render();
   al_flip_display();

   //sleep(1);

   al_destroy_font(font);
   al_destroy_display(display);

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_Renderer_AdvancedLineRendererTest, render__will_render_comments_with_a_different_color)
{
   al_init();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(800, 460);
   ALLEGRO_FONT *font = al_create_builtin_font();
   ALLEGRO_COLOR color = al_color_name("white");

   EXPECT_NE(nullptr, font);

   float x = al_get_display_width(display)/2;
   float y = al_get_display_height(display)/2;
   std::string text = "Hello World! // this is a comment";

   Hexagon::CodeEditor::Renderer::AdvancedLineRenderer advanced_line_renderer(font, &color, x, y, text);

   al_clear_to_color(al_color_name("black"));
   advanced_line_renderer.render();
   al_flip_display();

   //sleep(1);

   al_destroy_font(font);
   al_destroy_display(display);

   al_uninstall_system();
}

