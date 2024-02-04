#pragma once


#include <AllegroFlare/Config.hpp>
#include <allegro5/allegro_color.h>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace System
   {
      class Config
      {
      public:
         static constexpr char* FULLSCREEN_KEY = (char*)"fullscreen";

      private:
         static std::string INITIAL_DISPLAY_WIDTH_KEY;
         static std::string INITIAL_DISPLAY_HEIGHT_KEY;
         static std::string DEFAULT_NAVIGATOR_DIRECTORY_KEY;
         static std::string DOMAIN_KEY;
         static std::string REGEX_TEMP_FILENAME_KEY;
         static std::string CLIPBOARD_TEMP_FILENAME_KEY;
         static std::string FILE_NAVIGATOR_SELECTION_FILENAME_KEY;
         static std::string MAKE_COMMAND_FILENAME_KEY;
         static std::string FOCUSED_COMPONENT_FILENAME_KEY;
         static std::string FONT_BIN_PATH_KEY;
         static std::string BITMAP_BIN_PATH_KEY;
         static std::string DARK_MODE_KEY;
         static std::string OBJECTIVE_KEY;
         static std::string HUD_SHOW_FOCUS_TIMER_BAR_KEY;
         static std::string INITIAL_BASELINE_CAMERA_STEPBACK_KEY;
         std::string config_filename;
         AllegroFlare::Config config;
         bool initialized;
         void validate_initialized(std::string function_name="[unnamed_function]");
         std::string resource_path(std::vector<std::string> components={}, std::string filename={});

      protected:


      public:
         Config(std::string config_filename="/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg");
         ~Config();

         std::string get_config_filename() const;
         void initialize();
         void reload();
         std::vector<std::tuple<std::string, std::string>> get_projects_list();
         int get_initial_display_width();
         int get_initial_display_height();
         std::string get_default_navigator_directory();
         std::string get_regex_temp_filename();
         std::string get_clipboard_temp_filename();
         std::string get_file_navigator_selection_filename();
         std::string get_make_command_filename();
         std::string get_focused_component_filename();
         std::string get_font_bin_path();
         std::string get_bitmap_bin_path();
         int get_initial_baseline_camera_stepback();
         bool is_dark_mode();
         std::string get_objective();
         std::string get_current_project_domain();
         bool is_fullscreen();
         bool get_hud_show_focus_timer_bar();
         ALLEGRO_COLOR get_backfill_color();
         ALLEGRO_COLOR get_base_text_color();
         float get_backfill_opacity();
      };
   }
}



