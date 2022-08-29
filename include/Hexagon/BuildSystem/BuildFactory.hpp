#pragma once


#include <string>


namespace Hexagon
{
   namespace BuildSystem
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



