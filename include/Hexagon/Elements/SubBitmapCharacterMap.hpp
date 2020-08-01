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
         std::map<char, ALLEGRO_BITMAP*> cell_sub_bitmaps;

      public:
         SubBitmapCharacterMap(ALLEGRO_FONT* font=nullptr);
         ~SubBitmapCharacterMap();

         void set_font(ALLEGRO_FONT* font);

         int get_grid_width();
         int get_grid_height();
         std::map<char, ALLEGRO_BITMAP*> get_cell_sub_bitmaps();
      ALLEGRO_BITMAP* create();
      };
   }
}



