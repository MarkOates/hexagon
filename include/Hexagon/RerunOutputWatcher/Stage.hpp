#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace RerunOutputWatcher
   {
      class Stage : public StageInterface
      {
      private:
         std::string command;
         std::string watch_pattern;
         std::string output;

      public:
         Stage(std::string command="make", std::string watch_pattern="**.*.q.yml");
         virtual ~Stage();

         void set_command(std::string command);
         void set_watch_pattern(std::string watch_pattern);

         std::string get_command();
         std::string get_watch_pattern();
         std::string get_output();
      void clear();
      static ALLEGRO_EVENT& dummy_ALLEGRO_EVENT();
      void append_to_output(std::string content_to_append="");
      void refresh();
      virtual void render(ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=60, int cell_height=20) override;
      virtual void process_local_event(std::string event_name="", ActionData action_data={}) override;
      virtual void process_event(ALLEGRO_EVENT& event=Stage::dummy_ALLEGRO_EVENT()) override;
      };
   }
}



