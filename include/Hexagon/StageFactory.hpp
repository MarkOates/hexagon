#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/System/Config.hpp>
#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   class StageFactory
   {
   private:
      Hexagon::System::Config* config;
      AllegroFlare::FontBin* font_bin;

   public:
      StageFactory(Hexagon::System::Config* config=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
      ~StageFactory();

      std::string obtain_default_navigator_directory();
      ALLEGRO_COLOR obtain_base_text_color();
      std::string obtain_regex_temp_filename();
      ALLEGRO_COLOR obtain_base_backfill_color();
      ALLEGRO_FONT* obtain_component_navigator_font();
      ALLEGRO_FONT* obtain_file_navigator_font();
      ALLEGRO_FONT* obtain_global_font();
      ALLEGRO_FONT* obtain_git_commit_message_box_font();
      int obtain_display_default_width();
      int obtain_display_default_height();
      StageInterface* create_notification(std::string body_text="");
      StageInterface* create_file_navigator(std::string directory="");
      StageInterface* create_little_menu();
      StageInterface* create_class_brief_menu(std::string title="Untitled Menu", std::vector<std::tuple<std::string, std::string>> items={{"Foo", "foo"}, {"Bar", "bar"}, {"Baz", "baz"}});
      StageInterface* create_drawing_box();
      StageInterface* create_missing_file(std::string filename="");
      StageInterface* create_advanced_code_editor(std::string filename="untitled.txt", int num_columns=123, int num_rows=70);
      StageInterface* create_code_editor(std::string filename="", std::string file_category="undefined");
      StageInterface* create_regex_input_box_modal();
      StageInterface* create_git_commit_message_box();
      StageInterface* create_advanced_component_navigator();
      ALLEGRO_DISPLAY* get_current_display();
      placement3d build_centered_on_hud_initial_place(float width=0, float height=0);
      placement3d build_component_navigator_initial_place();
      placement3d build_file_navigator_initial_place();
      placement3d build_git_commit_message_input_box_initial_place();
      placement3d build_regex_input_box_initial_place();
   };
}



