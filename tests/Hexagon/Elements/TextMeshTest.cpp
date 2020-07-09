
#include <gtest/gtest.h>

#include <Hexagon/Elements/TextMesh.hpp>

TEST(Hexagon_Elements_TextMeshTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextMesh text_mesh;
}

TEST(Hexagon_Elements_TextMeshTest, render__works_without_blowing_up)
{
   Hexagon::Elements::TextMesh text_mesh;
   text_mesh.render();
   SUCCEED();
}
