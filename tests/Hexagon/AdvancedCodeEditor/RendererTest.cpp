#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>

TEST(Hexagon_AdvancedCodeEditor_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Renderer renderer;
}

TEST(Hexagon_AdvancedCodeEditor_RendererTest, render__without_a_valid_text_mesh__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Renderer renderer;
   std::string expected_error_message = "Renderer::render: error: guard \"text_mesh\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_AdvancedCodeEditor_RendererTest, render__without_a_valid_cursor__raises_an_error)
{
   Hexagon::Elements::TextMesh text_mesh;

   Hexagon::AdvancedCodeEditor::Renderer renderer(&text_mesh);
   std::string expected_error_message = "Renderer::render: error: guard \"cursor\" not met";
   ASSERT_THROW_WITH_MESSAGE(renderer.render(), std::runtime_error, expected_error_message);
}

