#pragma once


#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      class Build
      {
      private:
         std::string status;
         static std::string STATUS_UNDEFINED;

      public:
         Build();
         ~Build();

         std::string get_status();
         std::string start();
      };
   }
}



