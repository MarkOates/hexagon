
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/CodeEditor/CachedLineRenderer.hpp>
#include <allegro5/allegro.h>

TEST(Hexagon_CodeEditor_CachedLineRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer;
}

TEST(Hexagon_CodeEditor_CachedLineRendererTest, initialize__with_proper_dependencies_can_be_called_without_blowing_up)
{
   al_init();
   al_init_font_addon();

   ALLEGRO_DISPLAY *display = al_create_display(300, 200);
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer(font);
   cached_line_renderer.initialize();

   al_uninstall_system();
   SUCCEED();
}

