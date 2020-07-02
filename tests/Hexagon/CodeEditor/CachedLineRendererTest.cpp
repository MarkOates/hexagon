
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

TEST(Hexagon_CodeEditor_CachedLineRendererTest, initialize__without_allegro_initialized__throws_an_error)
{
   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer;
   std::string expected_error_message =
      "CachedLineRenderer::initialize: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(cached_line_renderer.initialize(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_CodeEditor_CachedLineRendererTest, initialize__without_a_valid_font__throws_an_error)
{
   al_init();

   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer;
   std::string expected_error_message = "CachedLineRenderer::initialize: error: guard \"font\" not met";
   ASSERT_THROW_WITH_MESSAGE(cached_line_renderer.initialize(), std::runtime_error, expected_error_message);

   al_uninstall_system();
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

TEST(Hexagon_CodeEditor_CachedLineRendererTest, pull__without_initializing__throws_an_error)
{
   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer;
   std::string expected_error_message = "CachedLineRenderer::pull: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(cached_line_renderer.pull(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_CodeEditor_CachedLineRendererTest, pull__with_an_index_out_of_bounds__throws_an_error)
{
   al_init();
   al_init_font_addon();

   ALLEGRO_DISPLAY *display = al_create_display(300, 200);
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer(font);
   cached_line_renderer.initialize();

   std::string expected_error_message_lt_0 = "CachedLineRenderer::pull: error: guard \"index >= 0\" not met";
   ASSERT_THROW_WITH_MESSAGE(cached_line_renderer.pull(-1), std::runtime_error, expected_error_message_lt_0);

   std::string expected_error_message_gt_size =
      "CachedLineRenderer::pull: error: guard \"index < cache.size()\" not met";
   ASSERT_THROW_WITH_MESSAGE(cached_line_renderer.pull(99999), std::runtime_error, expected_error_message_gt_size);

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_CachedLineRendererTest, size__returns_the_size_of_the_cache)
{
   al_init();
   al_init_font_addon();

   ALLEGRO_DISPLAY *display = al_create_display(300, 200);
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer(font);
   cached_line_renderer.initialize();

   int expected_cache_size = 200;

   ASSERT_EQ(expected_cache_size, cached_line_renderer.size());

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_CachedLineRendererTest, exists__without_initializing__throws_an_error)
{
   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer;
   std::string expected_error_message = "\"CachedLineRenderer::exists\" must call initialize first";
   ASSERT_THROW_WITH_MESSAGE(cached_line_renderer.exists(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_CodeEditor_CachedLineRendererTest, exists__with_indexes_out_of_bounds__returns_false)
{
   al_init();
   al_init_font_addon();

   ALLEGRO_DISPLAY *display = al_create_display(300, 200);
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer(font);
   cached_line_renderer.initialize();

   int cache_size = cached_line_renderer.size();

   ASSERT_EQ(false, cached_line_renderer.exists(-1));
   ASSERT_EQ(false, cached_line_renderer.exists(cache_size+1));

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_CachedLineRendererTest, exists__with_indexes_in_bounds__returns_true)
{
   al_init();
   al_init_font_addon();

   ALLEGRO_DISPLAY *display = al_create_display(300, 200);
   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::CodeEditor::CachedLineRenderer cached_line_renderer(font);
   cached_line_renderer.initialize();

   int cache_size = cached_line_renderer.size();

   for (unsigned i=0; i<cache_size; i++)
   {
      ASSERT_EQ(true, cached_line_renderer.exists(i));
   }

   al_uninstall_system();
}

