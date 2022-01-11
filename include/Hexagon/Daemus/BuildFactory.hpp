#pragma once


#include <string>


namespace Hexagon
{
   namespace Daemus
   {
      class BuildFactory
      {
      private:

      public:
         BuildFactory();
         ~BuildFactory();

         std::string run();
      };
   }
}



