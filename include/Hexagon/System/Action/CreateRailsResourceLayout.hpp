#pragma once


#include <Hexagon/Action.hpp>
#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class CreateRailsResourceLayout : public ::Action
         {
         private:

         public:
            CreateRailsResourceLayout();
            ~CreateRailsResourceLayout();


         std::string run();
         };
      }
   }
}



