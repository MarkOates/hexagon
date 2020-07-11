
#include <gtest/gtest.h>

#include <Hexagon/Elements/TextMesh.hpp>

TEST(Hexagon_Elements_TextMeshTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextMesh text_mesh;
}

TEST(Hexagon_Elements_TextMeshTest, run__returns_the_expected_response)
{
   Hexagon::Elements::TextMesh text_mesh;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, text_mesh.run());
}
