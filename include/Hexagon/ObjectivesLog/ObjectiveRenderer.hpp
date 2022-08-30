#pragma once


#include <ALLEGRO_FONT.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ObjectivesLog/Objective.hpp>


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
         bool is_activated;

      public:
         ObjectiveRenderer(AllegroFlare::FontBin* font_bin=nullptr, Hexagon::ObjectivesLog::Objective* objective=nullptr, float width=600, float height=100);
         ~ObjectiveRenderer();

         void set_is_activated(bool is_activated);
         bool get_is_activated() const;
         void render();
         ALLEGRO_FONT* obtain_primary_text_font();
      };
   }
}



