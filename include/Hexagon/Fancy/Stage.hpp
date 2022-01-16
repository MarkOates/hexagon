#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace Fancy
   {
      class Stage : public StageInterface
      {
      private:
         AllegroFlare::FontBin* font_bin;
         static ALLEGRO_EVENT a_default_empty_event;

      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr);
         virtual ~Stage();

         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         std::string run();
         void render() override;
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
         ALLEGRO_FONT* obtain_title_font();
      };
   }
}



