#pragma once


#include <Hexagon/Elements/BitmapGridMesh.hpp>
#include <Hexagon/Elements/FontCharacterMapGrid.hpp>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace Elements
   {
      class TextMesh
      {
      private:
         ALLEGRO_FONT* font;
         Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;
         Hexagon::Elements::BitmapGridMesh bitmap_grid_mesh;
         bool initialized;

      public:
         TextMesh(ALLEGRO_FONT* font=nullptr);
         ~TextMesh();


      void initialize();
      };
   }
}



