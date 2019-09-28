#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace ComponentNavigator
   {
      class Stage : public StageInterface
      {
      private:
         static ALLEGRO_EVENT a_default_empty_event;

      public:
         Stage();
         ~Stage();


         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void render(ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20);
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      bool save_file();
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



