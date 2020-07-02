#pragma once


#include <AllegroFlare/Bin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      class LineRenderBin : public AllegroFlare::Bin<std::string, ALLEGRO_BITMAP *>
      {
      private:
         ALLEGRO_FONT* font;

      public:
         LineRenderBin(ALLEGRO_FONT* font=nullptr);
         ~LineRenderBin();


      ALLEGRO_BITMAP* load_data(std::string identifier="") override;
      void destroy_data(ALLEGRO_BITMAP* resource=nullptr) override;
      };
   }
}



