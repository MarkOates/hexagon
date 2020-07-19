#pragma once


#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace Elements
   {
      class DataTable
      {
      private:
         ALLEGRO_FONT* font;
         float width;
         float height;

      public:
         DataTable(ALLEGRO_FONT* font=nullptr, float width=1.0, float height=1.0);
         ~DataTable();


      void render();
      void render_text();
      };
   }
}



