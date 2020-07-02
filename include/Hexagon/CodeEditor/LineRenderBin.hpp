#pragma once


#include <AllegroFlare/Bin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      class LineRenderBin : public AllegroFlare::Bin<std::string, ALLEGRO_BITMAP *>
      {
      private:

      public:
         LineRenderBin();
         ~LineRenderBin();


      std::string run();
      ALLEGRO_BITMAP* load_data(std::string identifier="") override;
      void destroy_data(ALLEGRO_BITMAP* resource=nullptr) override;
      };
   }
}



