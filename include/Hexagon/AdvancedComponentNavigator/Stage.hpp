#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedComponentNavigator/AdvancedComponentNavigator.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
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
      public:
         static constexpr char* YANK_SELECTED_TEXT_AS_STATIC_CASTED_AS = (char*)"yank_selected_text_as_static_casted_as";

      private:
         AllegroFlare::FontBin* font_bin;
         std::string project_root;
         Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator component;
         static ALLEGRO_EVENT a_default_empty_event;
         bool is_focused;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;
         ALLEGRO_COLOR base_text_color;
         ALLEGRO_COLOR base_backfill_color;
         bool represents_symlink;
         std::string MOVE_CURSOR_UP;
         std::string MOVE_CURSOR_DOWN;
         std::string YANK_SELECTED_TEXT_LABEL;
         std::string YANK_SELECTED_TEXT_AS_COMPONENT_NAME;
         std::string YANK_SELECTED_TEXT_AS_INCLUDE_DIRECTIVE;
         std::string YANK_SELECTED_TEXT_AS_ERROR_MESSAGE_TEMPLATE;
         std::string YANK_SELECTED_TEXT_AS_QUINTESSENCE_DEPENDENCY_LINES;
         std::string YANK_SELECTED_TEXT_AS_PUBLIC_PARENT_CLASS_LINES;
         std::string YANK_SELECTED_TEXT_AS_INJECTED_DEPENDENCY_PROPERTY;

      protected:


      public:
         Stage(std::string project_root="/Users/markoates/Repos/hexagon/", ALLEGRO_COLOR base_text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR base_backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f}, bool represents_symlink=false);
         virtual ~Stage();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_project_root(std::string project_root);
         void set_is_focused(bool is_focused);
         void set_display(ALLEGRO_DISPLAY* display);
         void set_font(ALLEGRO_FONT* font);
         void set_cell_width(int cell_width);
         void set_cell_height(int cell_height);
         void set_base_text_color(ALLEGRO_COLOR base_text_color);
         void set_base_backfill_color(ALLEGRO_COLOR base_backfill_color);
         AllegroFlare::FontBin* get_font_bin() const;
         std::string get_project_root() const;
         bool get_is_focused() const;
         ALLEGRO_DISPLAY* get_display() const;
         ALLEGRO_FONT* get_font() const;
         int get_cell_width() const;
         int get_cell_height() const;
         ALLEGRO_COLOR get_base_text_color() const;
         ALLEGRO_COLOR get_base_backfill_color() const;
         bool get_represents_symlink() const;
         Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &get_component_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         AllegroFlare::KeyboardCommandMapper build_keyboard_command_mapping();
         std::map<std::string, std::function<void(Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator&)>> build_local_events_dictionary();
         virtual void render() override;
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         void process_char_event(int keycode=0, int unichar=0, bool is_repeat=false);
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
         bool save_file();
      };
   }
}



