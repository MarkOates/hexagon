#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      class Stage : public StageInterface
      {
      private:
         std::string expected_filename;
         std::string text;
         static ALLEGRO_EVENT a_default_empty_event;

      public:
         Stage(std::string expected_filename="[Expected filename not set]");
         ~Stage();


         std::string get_expected_filename();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void render(bool is_focused=true, ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20);
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



