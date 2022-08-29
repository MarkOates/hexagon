#pragma once


#include <Hexagon/BuildSystem/Builds/Focused.hpp>


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

         Hexagon::BuildSystem::Builds::Focused* create_focused_build();
      };
   }
}



