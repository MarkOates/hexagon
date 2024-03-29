#pragma once


#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/ProjectComponentNavigator/ProjectComponentNavigator.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <map>
#include <string>


namespace Hexagon
{
   namespace ProjectComponentNavigator
   {
      class Stage : public StageInterface
      {
      private:
         std::string project_root;
         Hexagon::ProjectComponentNavigator::ProjectComponentNavigator component;
         static ALLEGRO_EVENT a_default_empty_event;
         bool is_focused;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;
         ALLEGRO_COLOR base_text_color;
         ALLEGRO_COLOR base_backfill_color;

      protected:


      public:
         Stage(std::string project_root="/Users/markoates/Repos/hexagon/", ALLEGRO_COLOR base_text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR base_backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
         virtual ~Stage();

         void set_project_root(std::string project_root);
         void set_is_focused(bool is_focused);
         void set_display(ALLEGRO_DISPLAY* display);
         void set_font(ALLEGRO_FONT* font);
         void set_cell_width(int cell_width);
         void set_cell_height(int cell_height);
         void set_base_text_color(ALLEGRO_COLOR base_text_color);
         void set_base_backfill_color(ALLEGRO_COLOR base_backfill_color);
         std::string get_project_root() const;
         bool get_is_focused() const;
         ALLEGRO_DISPLAY* get_display() const;
         ALLEGRO_FONT* get_font() const;
         int get_cell_width() const;
         int get_cell_height() const;
         ALLEGRO_COLOR get_base_text_color() const;
         ALLEGRO_COLOR get_base_backfill_color() const;
         Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &get_component_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         AllegroFlare::KeyboardCommandMapper build_keyboard_command_mapping();
         std::map<std::string, std::function<void(Hexagon::ProjectComponentNavigator::ProjectComponentNavigator&)>> build_local_events_dictionary();
         virtual void render() override;
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         void process_char_event(int keycode=0, int unichar=0, bool is_repeat=false);
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
         bool save_file();
      };
   }
}



