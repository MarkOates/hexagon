#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/System/Config.hpp>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class OpenConfigFile : public ::Action
         {
         private:
            Hexagon::System::Config* config;

         public:
            OpenConfigFile();
            ~OpenConfigFile();


         bool execute();
         };
      }
   }
}



