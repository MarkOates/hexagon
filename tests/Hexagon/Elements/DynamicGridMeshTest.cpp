
#include <gtest/gtest.h>

#include <Hexagon/Elements/DynamicGridMesh.hpp>

TEST(Hexagon_Elements_DynamicGridMeshTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::DynamicGridMesh dynamic_grid_mesh;
}

TEST(Hexagon_Elements_DynamicGridMeshTest, run__returns_the_expected_response)
{
   Hexagon::Elements::DynamicGridMesh dynamic_grid_mesh;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, dynamic_grid_mesh.run());
}
