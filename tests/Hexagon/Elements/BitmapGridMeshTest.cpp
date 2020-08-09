
#include <gtest/gtest.h>

#include <Hexagon/Elements/BitmapGridMesh.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#define FLOATING_POINT_ERROR_MARGIN (0.00001f)

#include<allegro_flare/placement3d.h> // for placement3d
#include<allegro5/allegro_color.h> // for al_color_name

static void EXPECT_EQ_COLOR(ALLEGRO_COLOR expected, ALLEGRO_COLOR actual)
{
   std::string color_name_for_expected = al_color_rgb_to_name(expected.r, expected.g, expected.b);
   std::string color_name_for_actual = al_color_rgb_to_name(actual.r, actual.g, actual.b);

   EXPECT_EQ(color_name_for_expected, color_name_for_actual);
   EXPECT_NEAR(expected.a, actual.a, FLOATING_POINT_ERROR_MARGIN);
}

class Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture() {}
};

class Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   ALLEGRO_BITMAP* multi_colored_bitmap_fixture;

public:
   Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , multi_colored_bitmap_fixture(nullptr)
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
      if (multi_colored_bitmap_fixture) al_destroy_bitmap(multi_colored_bitmap_fixture);
      al_destroy_display(display);
      al_uninstall_system();
   }

   ALLEGRO_BITMAP* get_or_build_multi_colored_bitmap_fixture()
   {
      if (multi_colored_bitmap_fixture) return multi_colored_bitmap_fixture;

      multi_colored_bitmap_fixture = al_create_bitmap(30, 30);
      al_set_target_bitmap(multi_colored_bitmap_fixture);
      al_clear_to_color({1.0f, 1.0f, 1.0f, 1.0f});

      al_draw_filled_rectangle(0, 0, 10, 10, al_color_name("pink"));
      al_draw_filled_rectangle(10, 0, 20, 10, al_color_name("orange"));
      al_draw_filled_rectangle(20, 0, 30, 10, al_color_name("blue"));

      al_draw_filled_rectangle(0, 10, 10, 20, al_color_name("yellow"));
      al_draw_filled_rectangle(10, 10, 20, 20, al_color_name("green"));
      al_draw_filled_rectangle(20, 10, 30, 20, al_color_name("red"));

      al_draw_filled_rectangle(0, 20, 10, 30, al_color_name("black"));
      al_draw_filled_rectangle(10, 20, 20, 30, al_color_name("gray"));
      al_draw_filled_rectangle(20, 20, 30, 30, al_color_name("white"));

      // restore previous state
      al_set_target_bitmap(al_get_backbuffer(display));

      return multi_colored_bitmap_fixture;
   }
};

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture,
   resize__sets_the_width__height__cell_width__and__cell_height)
{
   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(32, 67, 7.25f, 9.64f);

   EXPECT_EQ(32, bitmap_grid_mesh.get_num_columns());
   EXPECT_EQ(67, bitmap_grid_mesh.get_num_rows());
   EXPECT_EQ(7.25f, bitmap_grid_mesh.get_cell_width());
   EXPECT_EQ(9.64f, bitmap_grid_mesh.get_cell_height());
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture, resize__sets_the_number_of_vertexes)
{
   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(2, 5);

   EXPECT_EQ(60, bitmap_grid_mesh.get_vertexes().size());
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture, resize__sets_the_number_of_elements_in_the_grid)
{
   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(2, 5);

   std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid = bitmap_grid_mesh.get_grid();

   int expected_num_columns = 5;
   EXPECT_EQ(expected_num_columns, grid.size());
   for (auto &row : grid)
   {
      EXPECT_EQ(2, row.size());
   }
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture, calculate_width__returns_the_width_of_the_mesh)
   // TODO
{
   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture, calculate_height__returns_the_height_of_the_mesh)
   // TODO
{
   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture, render__without_a_valid_bitmap__raises_an_error)
{
   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.set_bitmap(nullptr);
   std::string expected_error_message = "BitmapGridMesh::render: error: guard \"bitmap\" not met";
   ASSERT_THROW_WITH_MESSAGE(bitmap_grid_mesh.render(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture, render__draws_the_grid)
{
   ALLEGRO_BITMAP *white_bitmap = al_create_bitmap(40, 60);
   al_set_target_bitmap(white_bitmap);
   al_clear_to_color({1.0f, 1.0f, 1.0f, 1.0f});
   al_set_target_bitmap(al_get_backbuffer(display));

   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(8*40, 5*60, 0);

   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(8, 5, 40, 60);
   bitmap_grid_mesh.set_bitmap(white_bitmap);

   place.size = vec3d(bitmap_grid_mesh.calculate_width(), bitmap_grid_mesh.calculate_height(), 0);

   place.start_transform();
   bitmap_grid_mesh.render();
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithEmptyFixture, set_cell_color__sets_the_color_of_the_cell)
{
   ALLEGRO_COLOR color = {0.2f, 1.0f, 0.2f, 1.0f};
   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(3, 2, 20.0f, 30.0f);
   bitmap_grid_mesh.set_cell_color(2, 1, color);

   std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid = bitmap_grid_mesh.get_grid();

   ALLEGRO_COLOR expected_color = color;
   ALLEGRO_COLOR actual_color = std::get<2>(grid[1][2]);

   EXPECT_EQ_COLOR(expected_color, actual_color);
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture, render__draws_the_grid_cell_colors)
{
   ALLEGRO_BITMAP *white_bitmap = al_create_bitmap(40, 60);
   al_set_target_bitmap(white_bitmap);
   al_clear_to_color({1.0f, 1.0f, 1.0f, 1.0f});
   al_set_target_bitmap(al_get_backbuffer(display));

   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(8*40, 5*60, 0);

   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.set_bitmap(white_bitmap);
   bitmap_grid_mesh.resize(30, 20, 13, 22);

   bitmap_grid_mesh.set_cell_color(2, 2, al_color_name("pink"));
   bitmap_grid_mesh.set_cell_color(0, 0, al_color_name("orange"));
   bitmap_grid_mesh.set_cell_color(29, 19, al_color_name("orange"));

   bitmap_grid_mesh.set_cell_color(7, 4, al_color_name("red"));
   bitmap_grid_mesh.set_cell_color(8, 4, al_color_name("red"));
   bitmap_grid_mesh.set_cell_color(9, 4, al_color_name("red"));

   bitmap_grid_mesh.set_cell_color(12, 4, al_color_name("green"));
   bitmap_grid_mesh.set_cell_color(13, 4, al_color_name("green"));
   bitmap_grid_mesh.set_cell_color(14, 4, al_color_name("green"));

   place.size = vec3d(bitmap_grid_mesh.calculate_width(), bitmap_grid_mesh.calculate_height(), 0);

   place.start_transform();
   bitmap_grid_mesh.render();
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture, render__uses_the_uv_cordinates_on_the_bitmap)
{
   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(8*40, 5*60, 0);

   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(18, 16, 32, 18);
   bitmap_grid_mesh.set_bitmap(get_or_build_multi_colored_bitmap_fixture());

   int last_row = bitmap_grid_mesh.get_num_rows() - 1;
   int last_column = bitmap_grid_mesh.get_num_columns() - 1;
   bitmap_grid_mesh.set_cell_uv(0,           0,        {0, 0, 10, 10});
   bitmap_grid_mesh.set_cell_uv(last_column, 0,        {10, 10, 20, 20});
   bitmap_grid_mesh.set_cell_uv(0,           last_row, {20, 10, 30, 20});
   bitmap_grid_mesh.set_cell_uv(last_column, last_row, {20, 10, 30, 20});

   bitmap_grid_mesh.set_cell_uv(3, 2, {10, 10, 20, 20});
   bitmap_grid_mesh.set_cell_uv(5, 2, {20, 10, 30, 20});

   place.start_transform();
   bitmap_grid_mesh.render();
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture,
   render_only_select_cells__will_only_render_cells_from_the_provided_list)
{
   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(8*40, 5*60, 0);

   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(18, 16, 32, 18);
   bitmap_grid_mesh.set_bitmap(get_or_build_multi_colored_bitmap_fixture());

   // fill with pink
   for (unsigned y=0; y<bitmap_grid_mesh.get_num_rows(); y++)
   {
      for (unsigned x=0; x<bitmap_grid_mesh.get_num_columns(); x++)
      {
         bitmap_grid_mesh.set_cell_uv(x, y, {0, 0, 10, 10});
      }
   }

   int last_row = bitmap_grid_mesh.get_num_rows() - 1;
   int last_column = bitmap_grid_mesh.get_num_columns() - 1;

   std::vector<std::pair<int, int>> cell_coordinates_out_of_range = {
      { 0,           0 },
      { 1,           1 },
      { last_column, 0 },
      { 0,           last_row },
      { last_column, last_row },
   };

   place.start_transform();
   bitmap_grid_mesh.render_only_select_cells(cell_coordinates_out_of_range);
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture,
   render_only_select_cells__will_ignore_cells_that_are_out_of_bounds)
{
   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(8*40, 5*60, 0);

   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(18, 16, 32, 18);
   bitmap_grid_mesh.set_bitmap(get_or_build_multi_colored_bitmap_fixture());

   // fill with pink
   for (unsigned y=0; y<bitmap_grid_mesh.get_num_rows(); y++)
   {
      for (unsigned x=0; x<bitmap_grid_mesh.get_num_columns(); x++)
      {
         bitmap_grid_mesh.set_cell_uv(x, y, {0, 0, 10, 10});
      }
   }

   int last_row = bitmap_grid_mesh.get_num_rows() - 1;
   int last_column = bitmap_grid_mesh.get_num_columns() - 1;

   std::vector<std::pair<int, int>> cell_coordinates_out_of_range = {
      { -1,            0 },
      { 0,             -1 },
      { last_column+1, 0 },
      { 0,             last_row+1 },
      { last_column+1, last_row },
   };

   place.start_transform();
   bitmap_grid_mesh.render_only_select_cells(cell_coordinates_out_of_range);
   place.restore_transform();

   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_BitmapGridMeshTest_WithAllegroRenderingFixture, render__will_respect_the_clipping_values)
{
   int num_columns = 30;
   int num_rows = 40;
   int cell_width = 16;
   int cell_height = 16;

   Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
   bitmap_grid_mesh.resize(num_columns, num_rows, cell_width, cell_height);
   bitmap_grid_mesh.set_bitmap(get_or_build_multi_colored_bitmap_fixture());

   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(bitmap_grid_mesh.calculate_width(), bitmap_grid_mesh.calculate_height(), 0);

   // fill with pink
   for (unsigned y=0; y<bitmap_grid_mesh.get_num_rows(); y++)
   {
      for (unsigned x=0; x<bitmap_grid_mesh.get_num_columns(); x++)
      {
         bitmap_grid_mesh.set_cell_uv(x, y, {0, 0, 10, 10});
      }
   }
   int last_row = bitmap_grid_mesh.get_num_rows() - 1;
   int last_column = bitmap_grid_mesh.get_num_columns() - 1;
   bitmap_grid_mesh.set_cell_uv(0, 0, {10, 10, 20, 20});
   bitmap_grid_mesh.set_cell_uv(last_column, 0, {20, 10, 30, 20});
   bitmap_grid_mesh.set_cell_uv(0, last_row, {20, 10, 30, 20});
   bitmap_grid_mesh.set_cell_uv(last_column, last_row, {20, 10, 30, 20});

   std::vector<std::tuple<int, int, int, ALLEGRO_COLOR>> coordinates_to_check =
      {
         { 0, 406, 48, al_color_name("green") },
      };

   for (auto &coordinate_to_check : coordinates_to_check)
   {
      int clip_y = std::get<0>(coordinate_to_check);
      int pixel_x = std::get<1>(coordinate_to_check);
      int pixel_y = std::get<2>(coordinate_to_check);
      ALLEGRO_COLOR expected_pixel_color = std::get<3>(coordinate_to_check);

      bitmap_grid_mesh.set_clip_inclusive_y(clip_y);

      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      place.start_transform();
      bitmap_grid_mesh.render();
      place.restore_transform();

      ALLEGRO_COLOR actual_color = al_get_pixel(al_get_backbuffer(display), pixel_x, pixel_y);
      EXPECT_EQ_COLOR(expected_pixel_color, actual_color);

      al_flip_display();
   }

   for (int y=0; y<20; y++)
   {
      bitmap_grid_mesh.set_clip_inclusive_y(y);

      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});

      place.start_transform();
      bitmap_grid_mesh.render();
      place.restore_transform();

      al_flip_display();

      usleep(50000);
   }
}

