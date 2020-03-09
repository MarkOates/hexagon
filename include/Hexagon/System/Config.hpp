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
         static std::string DEFAULT_NAVIGATOR_DIRECTORY_KEY;
         std::string config_filename;
         AllegroFlare::Config config;

      public:
         Config(std::string config_filename="/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg");
         ~Config();


      void initialize();
      std::string get_default_navigator_directory();
      };
   }
}



