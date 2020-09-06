#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/System/Config.hpp>
#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>
#include <string>


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
   StageInterface* create();
   StageInterface* create_rerun_output_watcher();
   StageInterface* create_file_navigator(std::string directory="");
   StageInterface* create_missing_file(std::string filename="");
   StageInterface* create_regex_input_box_modal();
   StageInterface* create_git_commit_message_box();
   StageInterface* create_advanced_component_navigator();
   ALLEGRO_DISPLAY* get_current_display();
   placement3d build_component_navigator_initial_place();
   placement3d build_file_navigator_initial_place();
   placement3d build_git_commit_message_input_box_initial_place();
   placement3d build_regex_input_box_initial_place();
   };
}



