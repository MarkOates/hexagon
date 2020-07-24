
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/CursorRenderer.hpp>

TEST(Hexagon_CodeEditor_CursorRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
}

TEST(Hexagon_CodeEditor_CursorRendererTest, color__has_a_getter_with_the_default_value)
{
   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
   ALLEGRO_COLOR expected_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
   ALLEGRO_COLOR actual_color = cursor_renderer.get_color();
}

TEST(Hexagon_CodeEditor_CursorRendererTest, render__will_draw_the_cursor)
{
   // TODO
   Hexagon::CodeEditor::CursorRenderer cursor_renderer;
   //cursor_renderer.render();
}

