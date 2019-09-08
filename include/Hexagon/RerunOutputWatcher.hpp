#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   class RerunOutputWatcher : public StageInterface
   {
   private:
      std::string command;
      std::string watch_pattern;
      std::string output;

   public:
      RerunOutputWatcher();
      virtual ~RerunOutputWatcher();


      std::string get_command();
      std::string get_watch_pattern();
      std::string get_output();
   static ALLEGRO_EVENT& dummy_ALLEGRO_EVENT();
   bool append_to_output(std::string content_to_append="");
   virtual void render(ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=60, int cell_height=20) override;
   virtual void process_local_event(std::string event_name="", ActionData action_data={}) override;
   virtual void process_event(ALLEGRO_EVENT& event=RerunOutputWatcher::dummy_ALLEGRO_EVENT()) override;
   virtual bool save_file() override;
   };
}



