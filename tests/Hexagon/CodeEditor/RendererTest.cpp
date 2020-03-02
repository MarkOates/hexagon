
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Renderer.hpp>

TEST(Hexagon_CodeEditor_RendererTest, can_be_created_without_blowing_up)
{
   CodeEditor::Renderer renderer(true, nullptr, nullptr, nullptr, 0, 0);
}

