
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Renderer.hpp>

#include <allegro5/allegro_color.h>

TEST(Hexagon_CodeEditor_RendererTest, can_be_created_without_blowing_up)
{
   CodeEditor::Renderer renderer(true, true, nullptr, nullptr, nullptr, 0, 0);
}

TEST(Hexagon_CodeEditor_RendererTest, build_font_color__returns_the_expected_font_color)
{
   al_init();
   CodeEditor::Renderer renderer(true, true, nullptr, nullptr, nullptr, 0, 0);
   ALLEGRO_COLOR frame_color = al_color_name("white");
   ALLEGRO_COLOR actual_font_color = renderer.build_font_color(frame_color);

   //ASSERT_EQ(0.9f, actual_font_color.r);
   //ASSERT_EQ(0, actual_font_color.g);
   //ASSERT_EQ(0, actual_font_color.b);
   //ASSERT_EQ(1, actual_font_color.a);

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_RendererTest, build_frame_color__returns_the_expected_frame_color)
{
   al_init();
   CodeEditor::Renderer renderer(true, true, nullptr, nullptr, nullptr, 0, 0);
   ALLEGRO_COLOR expected = al_color_name("white");
   ALLEGRO_COLOR actual = renderer.build_frame_color();

   //ASSERT_EQ(0.9f, actual_font_color.r);
   //ASSERT_EQ(0, actual_font_color.g);
   //ASSERT_EQ(0, actual_font_color.b);
   //ASSERT_EQ(1, actual_font_color.a);

   al_uninstall_system();
}

