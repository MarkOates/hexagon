#pragma once


#include <Hexagon/Action.hpp>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class OpenConfigFile : public ::Action
         {
         private:

         public:
            OpenConfigFile();
            ~OpenConfigFile();


         bool execute();
         };
      }
   }
}



