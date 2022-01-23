#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ObjectivesLog/Objective.hpp>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace ObjectivesLog
   {
      class ObjectiveRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         Hexagon::ObjectivesLog::Objective* objective;
         float width;
         float height;

      public:
         ObjectiveRenderer(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::ObjectivesLog::Objective* objective=nullptr, float width=600, float height=200);
         ~ObjectiveRenderer();

         void render();
         ALLEGRO_FONT* obtain_primary_text_font();
      };
   }
}



