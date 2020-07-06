#pragma once


#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedComponentNavigator/AdvancedComponentNavigator.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <map>
#include <string>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class Stage : public StageInterface
      {
      private:
         std::string project_root;
         Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator component;
         static ALLEGRO_EVENT a_default_empty_event;
         bool is_focused;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;

      public:
         Stage(std::string project_root="/Users/markoates/Repos/hexagon/");
         ~Stage();

         void set_project_root(std::string project_root);
         void set_is_focused(bool is_focused);
         void set_display(ALLEGRO_DISPLAY* display);
         void set_font(ALLEGRO_FONT* font);
         void set_cell_width(int cell_width);
         void set_cell_height(int cell_height);

         std::string get_project_root();
         bool get_is_focused();
         ALLEGRO_DISPLAY* get_display();
         ALLEGRO_FONT* get_font();
         int get_cell_width();
         int get_cell_height();
         Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &get_component_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      KeyboardCommandMapper build_keyboard_command_mapping();
      std::map<std::string, std::function<void(AdvancedComponentNavigator&)>> build_local_events_dictionary();
      void render(bool _is_focused=true, ALLEGRO_DISPLAY* _display=nullptr, ALLEGRO_FONT* _font=nullptr, int _cell_width=10, int _cell_height=20);
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      void process_char_event(int keycode=0, int unichar=0, bool is_repeat=false);
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      bool save_file();
      };
   }
}



