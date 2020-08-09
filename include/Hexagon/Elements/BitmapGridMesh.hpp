#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <tuple>
#include <utility>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class BitmapGridMesh
      {
      private:
         std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>>& grid;
         static std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> dummy_grid;
         std::vector<ALLEGRO_VERTEX> vertexes;
         int num_columns;
         int num_rows;
         float cell_width;
         float cell_height;
         int clip_inclusive_y;
         int clip_length_y;
         ALLEGRO_BITMAP* bitmap;

      public:
         BitmapGridMesh();
         ~BitmapGridMesh();

         void set_clip_inclusive_y(int clip_inclusive_y);
         void set_clip_length_y(int clip_length_y);
         void set_bitmap(ALLEGRO_BITMAP* bitmap);

         std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>>& get_grid();
         std::vector<ALLEGRO_VERTEX> get_vertexes();
         int get_num_columns();
         int get_num_rows();
         float get_cell_width();
         float get_cell_height();
         int get_clip_inclusive_y();
         int get_clip_length_y();
         ALLEGRO_BITMAP* get_bitmap();
         static std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> &get_dummy_grid_ref();
      void set_cell_uv(int x=0, int y=0, std::tuple<float, float, float, float> uv_coords={0.0f, 0.0f, 1.0f, 1.0f});
      void set_cell_color(int x=0, int y=0, ALLEGRO_COLOR color={0.0f, 0.0f, 0.0f, 0.0f});
      bool resize(int num_columns=0, int num_rows=0, float cell_width=0.0f, float cell_height=0.0f);
      void render();
      void render_only_select_cells(std::vector<std::pair<int, int>> cell_coordinates={});
      float calculate_width();
      float calculate_height();
      std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>* find_cell(int x=0, int y=0);
      };
   }
}



