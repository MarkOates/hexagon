#pragma once


#include <Hexagon/Action.hpp>
#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class OpenConfigFile : public ::Action
         {
         private:
            std::string config_filename;

         public:
            OpenConfigFile(std::string config_filename="/Users/markoates/Repos/hexagon/bin/programs/data/config/hexagon.boot.cfg");
            ~OpenConfigFile();


            std::string get_config_filename();
         bool execute();
         };
      }
   }
}



