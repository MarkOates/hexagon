
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/TextMesh.hpp>

TEST(Hexagon_Elements_TextMeshTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextMesh text_mesh;
}

TEST(Hexagon_Elements_TextMeshTest, initialize__without_a_valid_font__will_raise_an_error)
{
   Hexagon::Elements::TextMesh text_mesh(nullptr);
   std::string expected_error_message = "TextMesh::initialize: error: guard \"font\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_mesh.initialize(), std::runtime_error, expected_error_message);
}
