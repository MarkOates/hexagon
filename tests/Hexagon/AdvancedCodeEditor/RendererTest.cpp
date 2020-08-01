#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>

class Hexagon_AdvancedCodeEditor_RendererTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};

TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Renderer renderer;
}

TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithEmptyFixture, render__without_a_valid_text_mesh__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Renderer renderer;
   std::string expected_error_message = "Renderer::render: error: guard \"text_mesh\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithEmptyFixture, render__without_a_valid_cursor__raises_an_error)
{
   Hexagon::Elements::TextMesh text_mesh;

   Hexagon::AdvancedCodeEditor::Renderer renderer(&text_mesh);
   std::string expected_error_message = "Renderer::render: error: guard \"cursor\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_AdvancedCodeEditor_RendererTestWithAllegroRenderingFixture, render__does_not_blow_up)
{
   ALLEGRO_FONT *font = get_any_font();
   Hexagon::Elements::TextMesh text_mesh(font);
   Hexagon::AdvancedCodeEditor::Cursor cursor;

   text_mesh.initialize();

   Hexagon::AdvancedCodeEditor::Renderer renderer(&text_mesh, &cursor);
   renderer.render();

   al_flip_display();

   SUCCEED();
}

