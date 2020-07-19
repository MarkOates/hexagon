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
         float column_width;
         float row_height;

      public:
         DataTable(ALLEGRO_FONT* font=nullptr, float column_width=1.0, float row_height=1.0);
         ~DataTable();


      void render();
      void render_text();
      };
   }
}



