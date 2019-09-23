#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace FileNavigator
   {
      class Stage : public StageInterface
      {
      private:
         static ALLEGRO_EVENT a_default_empty_event;
         ALLEGRO_COLOR circle_color;
         std::vector<std::string> nodes;
         int cursor_position;
         std::string node_root;

      public:
         Stage();
         ~Stage();

         void set_circle_color(ALLEGRO_COLOR circle_color);
         void set_nodes(std::vector<std::string> nodes);
         void set_node_root(std::string node_root);

         ALLEGRO_COLOR get_circle_color();
         std::vector<std::string> get_nodes();
         int get_cursor_position();
         std::string get_node_root();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void move_cursor_down();
      std::string run();
      void refresh_nodes();
      void render(ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20);
      void change_to_yellow();
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      bool save_file();
      void process_event(ALLEGRO_EVENT& action_data=get_a_default_empty_event_ref());
      };
   }
}



