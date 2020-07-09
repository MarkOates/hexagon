
#include <gtest/gtest.h>

#include <Hexagon/Elements/TextMesh.hpp>

class Hexagon_Elements_TextMeshTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_TextMeshTest_WithEmptyFixture() {}
};

class Hexagon_Elements_TextMeshTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;

public:
   Hexagon_Elements_TextMeshTest_WithAllegroRenderingFixture()
      : display(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_primitives_addon());
      display = al_create_display(1280, 720);
   }

   virtual void TearDown() override
   {
      al_destroy_display(display);
      al_uninstall_system();
   }
};

TEST_F(Hexagon_Elements_TextMeshTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextMesh text_mesh;
}

TEST_F(Hexagon_Elements_TextMeshTest_WithAllegroRenderingFixture, render__works_without_blowing_up)
{
   Hexagon::Elements::TextMesh text_mesh;
   text_mesh.render();

   al_flip_display();

   //sleep(1);

   SUCCEED();
}
