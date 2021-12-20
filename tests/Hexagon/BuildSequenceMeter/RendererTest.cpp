
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/BuildSequenceMeter/Renderer.hpp>

class Hexagon_BuildSequenceMeter_RendererTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::BuildSequenceMeter::Renderer renderer;
}


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture,
   render__without_a_font_bin__raises_an_error)
{
   Hexagon::BuildSequenceMeter::Renderer renderer;
   std::string expected_error_message =
      "Renderer::obtain_font: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture,
   render__without_allegro_initialized__raises_an_error)
{
   // TODO
}


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   Hexagon::BuildSequenceMeter::Renderer renderer(&get_font_bin_ref());
   renderer.render();
   al_flip_display();
   SUCCEED();
}


TEST_F(Hexagon_BuildSequenceMeter_RendererTestWithAllegroRenderingFixture,
   render__will_draw_the_build_stages)
{
   std::vector<std::pair<std::string, std::string>> build_stages = {
     { "started", "not_started" },
     { "generating_sources_files_from_quintessence", "not_started" },
     { "building_component_object_files", "not_started" },
     { "delete_focused_component_test_object_file_and_test_executable", "not_started" },
     { "build_focused_component_test_object_file_and_test_executable", "not_started" },
     { "run_test_for_focused_component", "not_started" },
     { "make_all_programs", "not_started" },
     { "make_documentation", "not_started" },
     { "signal_component_built_and_integrated", "not_started" },
     { "completed", "not_started" },
   };

   Hexagon::BuildSequenceMeter::Renderer renderer(&get_font_bin_ref(), "not_started", build_stages);
   renderer.render();
   al_flip_display();
   sleep(2);
   SUCCEED();
}


