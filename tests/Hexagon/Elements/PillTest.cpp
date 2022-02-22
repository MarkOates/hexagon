
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_PillTest : public ::testing::Test
{};

class Hexagon_Elements_PillTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


#include <Hexagon/Elements/Pill.hpp>


TEST_F(Hexagon_Elements_PillTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Pill pill;
}


TEST_F(Hexagon_Elements_PillTest, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::Pill pill;
   std::string expected_error_message =
      "XXXXXXX::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(pill.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_Elements_PillTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::Elements::Pill pill;
   pill.render();
   SUCCEED();
}

