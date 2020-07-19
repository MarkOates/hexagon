#pragma once


#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


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
         std::vector<std::vector<std::string>> data2d;

      public:
         DataTable(ALLEGRO_FONT* font=nullptr, float column_width=1.0, float row_height=1.0, std::vector<std::vector<std::string>> data2d={});
         ~DataTable();


      void render();
      };
   }
}



