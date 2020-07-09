```cpp
#include <gtest/gtest.h>

#include <Hexagon/Elements/FlashingGrid.hpp>

#include <allegro5/allegro.h>

class Hexagon_Elements_FlashingGridTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_FlashingGridTest_WithEmptyFixture() {}
};

class Hexagon_Elements_FlashingGridTest_WithAllegroRenderingFixture : public ::testing::Test
{
private:
   ALLEGRO_DISPLAY *display;

public:
   Hexagon_Elements_FlashingGridTest_WithAllegroRenderingFixture()
      : display(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      display = al_create_display(1280, 720);
   }

   virtual void TearDown() override
   {
      al_destroy_display(display);
      al_uninstall_system();
   }
};

TEST_F(Hexagon_Elements_FlashingGridTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FlashingGrid flashing_grid;
}

TEST_F(Hexagon_Elements_FlashingGridTest_WithAllegroRenderingFixture, run__returns_the_expected_response)
{
   Hexagon::Elements::FlashingGrid flashing_grid;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, flashing_grid.run());

   sleep(1);
}
```
