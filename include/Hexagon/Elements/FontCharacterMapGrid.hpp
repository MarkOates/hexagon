#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace Elements
   {
      class FontCharacterMapGrid
      {
      private:
         ALLEGRO_FONT* font;
         int grid_width;
         int grid_height;

      public:
         FontCharacterMapGrid(ALLEGRO_FONT* font=nullptr);
         ~FontCharacterMapGrid();


         int get_grid_width();
         int get_grid_height();
      ALLEGRO_BITMAP* create();
      };
   }
}



