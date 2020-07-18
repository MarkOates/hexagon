
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/SingleBlockBarGraph.hpp>

TEST(Hexagon_Elements_SingleBlockBarGraphTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
}

TEST(Hexagon_Elements_SingleBlockBarGraphTest, draw__without_allegro_initalized__raises_an_error)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   std::string expected_error_message = "SingleBlockBarGraph::draw: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(single_block_bar_graph.draw(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Elements_SingleBlockBarGraphTest, draw__when_the_primitives_addon_is_not_initalized__raises_an_error)
{
   al_init();

   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   std::string expected_error_message =
      "SingleBlockBarGraph::draw: error: guard \"al_is_primitives_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(single_block_bar_graph.draw(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}

