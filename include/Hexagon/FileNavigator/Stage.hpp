#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace FileNavigator
   {
      class Stage : public StageInterface
      {
      private:
         static ALLEGRO_EVENT a_default_empty_event;
         ALLEGRO_COLOR circle_color;

      public:
         Stage();
         ~Stage();

         void set_circle_color(ALLEGRO_COLOR circle_color);

         ALLEGRO_COLOR get_circle_color();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      std::string run();
      void render(ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20);
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      bool save_file();
      void process_event(ALLEGRO_EVENT& action_data=get_a_default_empty_event_ref());
      };
   }
}



