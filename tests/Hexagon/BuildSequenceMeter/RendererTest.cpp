
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/BuildSequenceMeter/Renderer.hpp>
#include <allegro_flare/placement2d.h>

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
   placement2d place{1920 - 60, 1080 / 2, 90, 690};
   std::vector<std::tuple<std::string, std::string, std::string>> build_stages = {
     { "started", "0001", "finished" },
     { "generating_sources_files_from_quintessence", "0002", "finished" },
     { "building_component_object_files", "0003", "finished" },
     { "delete_focused_component_test_object_file_and_test_executable", "0004", "running" },
     { "build_focused_component_test_object_file_and_test_executable", "0005", "not_started" },
     { "run_test_for_focused_component", "0006", "not_started" },
     { "make_all_programs", "0007", "not_started" },
     { "make_documentation", "0008", "not_started" },
     { "signal_component_built_and_integrated", "0009", "not_started" },
     { "completed", "0010", "not_started" },
   };
   Hexagon::BuildSequenceMeter::Renderer renderer(
      &get_font_bin_ref(),
      "not_started",
      build_stages,
      place.size.x,
      place.size.y
   );

   place.start_transform();
   renderer.render();
   place.restore_transform();

   al_flip_display();
   sleep(2);
   SUCCEED();
}


