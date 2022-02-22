
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_ComponentTitleSlateTest : public ::testing::Test
{};

class Hexagon_Elements_ComponentTitleSlateTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


#include <Hexagon/Elements/ComponentTitleSlate.hpp>


TEST_F(Hexagon_Elements_ComponentTitleSlateTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::ComponentTitleSlate component_title_slate;
}


TEST_F(Hexagon_Elements_ComponentTitleSlateTest, DISABLED__render__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::ComponentTitleSlate component_title_slate;
   std::string expected_error_message =
      "Hexagon::Elements::ComponentTitleSlate::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(component_title_slate.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_Elements_ComponentTitleSlateTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::Elements::ComponentTitleSlate component_title_slate;
   component_title_slate.render();
   SUCCEED();
}

