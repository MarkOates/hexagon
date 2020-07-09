
#include <gtest/gtest.h>

#include <Hexagon/Elements/TextMesh.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#define FLOATING_POINT_ERROR_MARGIN (0.00001f)

static void EXPECT_EQ_COLOR(ALLEGRO_COLOR expected, ALLEGRO_COLOR actual)
{
   EXPECT_NEAR(expected.r, actual.r, FLOATING_POINT_ERROR_MARGIN);
   EXPECT_NEAR(expected.g, actual.g, FLOATING_POINT_ERROR_MARGIN);
   EXPECT_NEAR(expected.b, actual.b, FLOATING_POINT_ERROR_MARGIN);
   EXPECT_NEAR(expected.a, actual.a, FLOATING_POINT_ERROR_MARGIN);
}

#include<allegro_flare/placement3d.h> // for placement3d

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

TEST_F(Hexagon_Elements_TextMeshTest_WithEmptyFixture, resize__sets_the_width__height__cell_width__and__cell_height)
{
   Hexagon::Elements::TextMesh text_mesh;
   text_mesh.resize(32, 67, 7.25f, 9.64f);

   EXPECT_EQ(32, text_mesh.get_num_columns());
   EXPECT_EQ(67, text_mesh.get_num_rows());
   EXPECT_EQ(7.25f, text_mesh.get_cell_width());
   EXPECT_EQ(9.64f, text_mesh.get_cell_height());
}

TEST_F(Hexagon_Elements_TextMeshTest_WithEmptyFixture, resize__sets_the_number_of_vertexes)
{
   Hexagon::Elements::TextMesh text_mesh;
   text_mesh.resize(2, 5);

   EXPECT_EQ(60, text_mesh.get_vertexes().size());
}

TEST_F(Hexagon_Elements_TextMeshTest_WithEmptyFixture, resize__sets_the_number_of_elements_in_the_grid)
{
   Hexagon::Elements::TextMesh text_mesh;
   text_mesh.resize(2, 5);

   std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid = text_mesh.get_grid();

   int expected_num_columns = 5;
   EXPECT_EQ(expected_num_columns, grid.size());
   for (auto &row : grid)
   {
      EXPECT_EQ(2, row.size());
   }
}

TEST_F(Hexagon_Elements_TextMeshTest_WithEmptyFixture, calculate_width__returns_the_width_of_the_mesh)
   // TODO
{
   Hexagon::Elements::TextMesh text_mesh;
}

TEST_F(Hexagon_Elements_TextMeshTest_WithEmptyFixture, calculate_height__returns_the_height_of_the_mesh)
   // TODO
{
   Hexagon::Elements::TextMesh text_mesh;
}

TEST_F(Hexagon_Elements_TextMeshTest_WithAllegroRenderingFixture, render__without_a_valid_bitmap__raises_an_error)
{
   Hexagon::Elements::TextMesh text_mesh;
   text_mesh.set_bitmap(nullptr);
   std::string expected_error_message = "TextMesh::render: error: guard \"bitmap\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_mesh.render(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_TextMeshTest_WithAllegroRenderingFixture, render__draws_the_grid)
{
   ALLEGRO_BITMAP *white_bitmap = al_create_bitmap(40, 60);
   al_set_target_bitmap(white_bitmap);
   al_clear_to_color({1.0f, 1.0f, 1.0f, 1.0f});
   al_set_target_bitmap(al_get_backbuffer(display));

   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(8*40, 5*60, 0);

   Hexagon::Elements::TextMesh text_mesh;
   text_mesh.resize(8, 5, 40, 60);
   text_mesh.set_bitmap(white_bitmap);

   place.size = vec3d(text_mesh.calculate_width(), text_mesh.calculate_height(), 0);

   place.start_transform();
   text_mesh.render();
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_TextMeshTest_WithEmptyFixture, set_cell_color__sets_the_color_of_the_cell)
{
   ALLEGRO_COLOR color = {0.2f, 1.0f, 0.2f, 1.0f};
   Hexagon::Elements::TextMesh text_mesh;
   text_mesh.resize(3, 2, 20.0f, 30.0f);
   text_mesh.set_cell_color(2, 1, color);

   std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid = text_mesh.get_grid();

   ALLEGRO_COLOR expected_color = color;
   ALLEGRO_COLOR actual_color = std::get<2>(grid[1][2]);

   EXPECT_EQ_COLOR(expected_color, actual_color);
}

