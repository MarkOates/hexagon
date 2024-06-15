
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/LineRenderBin.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>

std::string TEST_OUTPUT_DIRECTORY = "/Users/markoates/Repos/hexagon/tmp/";

TEST(Hexagon_CodeEditor_LineRenderBinTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::LineRenderBin line_render_bin;
}

TEST(Hexagon_CodeEditor_LineRenderBinTest, load_data__without_a_valid_font_raises_an_error)
{
   Hexagon::CodeEditor::LineRenderBin line_render_bin;
   ASSERT_THROW_GUARD_ERROR(
      line_render_bin.load_data(),
      "Hexagon::CodeEditor::LineRenderBin::load_data",
      "font"
   );
}

TEST(Hexagon_CodeEditor_LineRenderBinTest, will_generate_the_expected_render_for_the_identifier)
{
   al_init();
   al_init_font_addon();
   al_init_image_addon();

   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::CodeEditor::LineRenderBin line_render_bin(font);
   line_render_bin.set_full_path("");
   ALLEGRO_BITMAP *rendered_resource = line_render_bin.auto_get("  - name: foobar");

   std::string location_to_save_bitmap = TEST_OUTPUT_DIRECTORY + "string_to_render.png";
   al_save_bitmap(location_to_save_bitmap.c_str(), rendered_resource);

   al_uninstall_system();
}

TEST(Hexagon_CodeEditor_LineRenderBinTest, foobar)
{
   al_init();
   al_init_font_addon();
   al_init_image_addon();

   ALLEGRO_FONT *font = al_create_builtin_font();

   Hexagon::CodeEditor::LineRenderBin line_render_bin(font);
   line_render_bin.set_full_path("");

   std::map<std::string, std::string> test_datas = {
      { "this is a long line that spans several characters", "string_to_render-2.png" },
      { "  - name: name_of_thing", "string_to_render-3.png" },
      { "Hexagon::CodeEditor::Renderer::AdvancedLineRenderer renderer;", "string_to_render-4.png" },
   };

   for (auto &test_data : test_datas)
   {
      std::string filename = test_data.second;
      std::string text_to_render = test_data.first;

      ALLEGRO_BITMAP *rendered_resource = line_render_bin.auto_get(text_to_render);
      std::string location_to_save_bitmap = TEST_OUTPUT_DIRECTORY + filename;
      al_save_bitmap(location_to_save_bitmap.c_str(), rendered_resource);
   }

   ASSERT_EQ(3, line_render_bin.size());

   al_uninstall_system();
}

