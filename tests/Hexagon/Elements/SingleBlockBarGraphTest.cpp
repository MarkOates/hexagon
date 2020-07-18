
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/SingleBlockBarGraph.hpp>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement3d.h>

class Hexagon_Elements_SingleBlockBarGraphTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_SingleBlockBarGraphTest_WithEmptyFixture() {}
};

class Hexagon_Elements_SingleBlockBarGraphTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;

public:
   Hexagon_Elements_SingleBlockBarGraphTest_WithAllegroRenderingFixture()
      : display(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_primitives_addon());
      display = al_create_display(1280*2, 720*2);
      al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   }

   virtual void TearDown() override
   {
      al_destroy_display(display);
      al_uninstall_system();
   }

   placement3d build_centered_placement(float width, float height)
   {
      placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0f);
      place.size = vec3d(width, height, 0);
      return place;
   }
};

TEST_F(Hexagon_Elements_SingleBlockBarGraphTest_WithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
}

TEST_F(Hexagon_Elements_SingleBlockBarGraphTest_WithEmptyFixture,
   draw__without_allegro_initalized__raises_an_error)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   std::string expected_error_message = "SingleBlockBarGraph::draw: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(single_block_bar_graph.draw(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_SingleBlockBarGraphTest_WithEmptyFixture,
   draw__when_the_primitives_addon_is_not_initalized__raises_an_error)
{
   al_init();

   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   std::string expected_error_message =
      "SingleBlockBarGraph::draw: error: guard \"al_is_primitives_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(single_block_bar_graph.draw(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}

TEST_F(Hexagon_Elements_SingleBlockBarGraphTest_WithEmptyFixture,
   draw__when_there_is_no_rendering_target__raises_an_error)
{
   al_init();
   al_init_primitives_addon();

   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   std::string expected_error_message =
      "SingleBlockBarGraph::draw: error: guard \"al_get_target_bitmap()\" not met";
   ASSERT_THROW_WITH_MESSAGE(single_block_bar_graph.draw(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}

TEST_F(Hexagon_Elements_SingleBlockBarGraphTest_WithAllegroRenderingFixture,
   draw__respects__number_of_bg_bars__bar_width__bar_height__bar_spacing__bg_bar_color)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   placement3d place = build_centered_placement(0, 0);

   single_block_bar_graph.set_number_of_bg_bars(7);
   single_block_bar_graph.set_bar_width(20);
   single_block_bar_graph.set_bar_height(60);
   single_block_bar_graph.set_bar_spacing(30);
   single_block_bar_graph.set_bg_bar_color(ALLEGRO_COLOR{0.0f, 0.2f, 0.0f, 1.0f});

   place.start_transform();
   single_block_bar_graph.draw();
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_SingleBlockBarGraphTest_WithAllegroRenderingFixture,
   draw__respects__number_of_active_bars__bar_width__bar_height__bar_spacing__main_bar_color)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   placement3d place = build_centered_placement(0, 0);

   single_block_bar_graph.set_number_of_active_bars(3);
   single_block_bar_graph.set_bar_width(20);
   single_block_bar_graph.set_bar_height(60);
   single_block_bar_graph.set_bar_spacing(30);
   single_block_bar_graph.set_main_bar_color(ALLEGRO_COLOR{0.0f, 0.2f, 0.0f, 1.0f});

   place.start_transform();
   single_block_bar_graph.draw();
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_SingleBlockBarGraphTest_WithAllegroRenderingFixture,
   draw__will_render_the_correct_active_and_non_active_bars)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   placement3d place = build_centered_placement(0, 0);

   single_block_bar_graph.set_number_of_bg_bars(8);
   single_block_bar_graph.set_number_of_active_bars(5);
   single_block_bar_graph.set_bar_width(20);
   single_block_bar_graph.set_bar_height(60);
   single_block_bar_graph.set_bar_spacing(30);
   single_block_bar_graph.set_main_bar_color(ALLEGRO_COLOR{0.0f, 0.4f, 0.4f, 1.0f});
   single_block_bar_graph.set_bg_bar_color(ALLEGRO_COLOR{0.2f, 0.2f, 0.2f, 1.0f});

   place.start_transform();
   single_block_bar_graph.draw();
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_SingleBlockBarGraphTest_WithAllegroRenderingFixture,
   draw__respects__stroke_with__stroke_color)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   placement3d place = build_centered_placement(0, 0);

   single_block_bar_graph.set_number_of_bg_bars(8);
   single_block_bar_graph.set_number_of_active_bars(5);
   single_block_bar_graph.set_bar_width(20);
   single_block_bar_graph.set_bar_height(60);
   single_block_bar_graph.set_bar_spacing(40);
   single_block_bar_graph.set_main_bar_color(ALLEGRO_COLOR{0.4f, 0.4f, 0.4f, 1.0f});
   single_block_bar_graph.set_bg_bar_color(ALLEGRO_COLOR{0.2f, 0.2f, 0.2f, 1.0f});

   single_block_bar_graph.set_stroke_width(5.0f);
   single_block_bar_graph.set_stroke_color(ALLEGRO_COLOR{0.0f, 0.5f, 0.0f, 1.0f});

   place.start_transform();
   single_block_bar_graph.draw();
   place.restore_transform();

   al_flip_display();

   sleep(1);
}

