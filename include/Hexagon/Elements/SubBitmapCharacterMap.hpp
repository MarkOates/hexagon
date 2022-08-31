#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <map>


namespace Hexagon
{
   namespace Elements
   {
      class SubBitmapCharacterMap
      {
      private:
         ALLEGRO_FONT* font;
         int grid_width;
         int grid_height;
         static int NUM_ROWS;
         static int NUM_COLUMNS;
         ALLEGRO_BITMAP* surface;
         std::map<char, ALLEGRO_BITMAP*> cell_sub_bitmaps;

      protected:


      public:
         SubBitmapCharacterMap(ALLEGRO_FONT* font=nullptr);
         ~SubBitmapCharacterMap();

         void set_font(ALLEGRO_FONT* font);
         int get_grid_width() const;
         int get_grid_height() const;
         ALLEGRO_BITMAP* get_surface() const;
         std::map<char, ALLEGRO_BITMAP*> get_cell_sub_bitmaps() const;
         void initialize();
         ALLEGRO_BITMAP* find_sub_bitmap(char character=0);
         void destroy();
      };
   }
}



