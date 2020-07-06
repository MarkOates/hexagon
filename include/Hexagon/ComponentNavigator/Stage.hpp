#pragma once


#include <Blast/Project/Component.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace ComponentNavigator
   {
      class Stage : public StageInterface
      {
      private:
         int cursor_position;
         bool cursor_position_static;
         ALLEGRO_COLOR selector_color;
         std::string project_root;
         static ALLEGRO_EVENT a_default_empty_event;
         std::vector<Blast::Project::Component> nodes;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;

      public:
         Stage(std::string project_root="/Users/markoates/Repos/hexagon");
         ~Stage();

         void set_cursor_position_static(bool cursor_position_static);
         void set_selector_color(ALLEGRO_COLOR selector_color);
         void set_project_root(std::string project_root);
         void set_nodes(std::vector<Blast::Project::Component> nodes);
         void set_font(ALLEGRO_FONT* font);
         void set_cell_width(int cell_width);
         void set_cell_height(int cell_height);

         int get_cursor_position();
         ALLEGRO_COLOR get_selector_color();
         std::string get_project_root();
         std::vector<Blast::Project::Component> get_nodes();
         ALLEGRO_FONT* get_font();
         int get_cell_width();
         int get_cell_height();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void move_cursor_up();
      void move_cursor_down();
      void move_cursor_to_top();
      bool current_selection_is_valid();
      std::string get_current_selection_label_or_empty_string();
      void refresh_list();
      void render(bool _is_focused=true, ALLEGRO_DISPLAY* _display=nullptr, ALLEGRO_FONT* _font=nullptr, int _cell_width=10, int _cell_height=20);
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      bool save_file();
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



