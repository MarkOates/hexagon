#pragma once


#include <AllegroFlare/Config.hpp>
#include <allegro5/allegro_color.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace System
   {
      class Config
      {
      private:
         static std::string INITIAL_DISPLAY_WIDTH_KEY;
         static std::string INITIAL_DISPLAY_HEIGHT_KEY;
         static std::string DEFAULT_NAVIGATOR_DIRECTORY_KEY;
         static std::string REGEX_TEMP_FILENAME_KEY;
         static std::string CLIPBOARD_TEMP_FILENAME_KEY;
         static std::string FILE_NAVIGATOR_SELECTION_FILENAME_KEY;
         static std::string MAKE_COMMAND_FILENAME_KEY;
         static std::string FOCUSED_COMPONENT_FILENAME_KEY;
         static std::string FONT_BIN_PATH_KEY;
         static std::string DARK_MODE_KEY;
         std::string config_filename;
         AllegroFlare::Config config;
         bool initialized;

      public:
         Config(std::string config_filename="/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg");
         ~Config();

         std::string get_config_filename();
         void validate_initialized(std::string function_name="[unnamed_function]");
         void initialize();
         int get_initial_display_width();
         int get_initial_display_height();
         std::string get_default_navigator_directory();
         std::string get_regex_temp_filename();
         std::string get_clipboard_temp_filename();
         std::string get_file_navigator_selection_filename();
         std::string get_make_command_filename();
         std::string get_focused_component_filename();
         std::string get_font_bin_path();
         int get_default_camera_stepback();
         bool is_dark_mode();
         ALLEGRO_COLOR get_backfill_color();
         ALLEGRO_COLOR get_base_text_color();
         float get_backfill_opacity();
         std::string resource_path(std::vector<std::string> components={}, std::string filename={});
      };
   }
}



