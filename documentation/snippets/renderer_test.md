```cpp

#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/QuoteRenderer.hpp>

class Hexagon_Elements_QuoteRendererTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};

TEST_F(Hexagon_Elements_QuoteRendererTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
}

TEST_F(Hexagon_Elements_QuoteRendererTestWithEmptyFixture, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
   std::string expected_error_message =
      "QuoteRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(quote_renderer.render(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
   quote_renderer.render();
   SUCCEED();
}
```
