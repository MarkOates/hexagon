#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/Elements/ListMenu.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace UI
   {
      class LittleMenu : public StageInterface
      {
      private:
         AllegroFlare::FontBin* font_bin;
         static ALLEGRO_EVENT a_default_empty_event;
         Hexagon::Elements::ListMenu menu;

      public:
         LittleMenu(AllegroFlare::FontBin* font_bin=nullptr);
         ~LittleMenu();


         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void render() override;
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      void emit_submission();
      };
   }
}



