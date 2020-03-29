#pragma once


#include <AllegroFlare/Config.hpp>
#include <string>


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
         std::string config_filename;
         AllegroFlare::Config config;
         bool initialized;

      public:
         Config(std::string config_filename="/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg");
         ~Config();


      void validate_initialized(std::string function_name="[unnamed_function]");
      void initialize();
      int get_initial_display_width();
      int get_initial_display_height();
      std::string get_default_navigator_directory();
      };
   }
}



