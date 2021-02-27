#pragma once


#include <Hexagon/BuildSystem/Build.hpp>
#include <vector>


namespace Hexagon
{
   namespace BuildSystem
   {
      class BuildRepository
      {
      private:
         std::vector<Hexagon::BuildSystem::Build> builds;

      public:
         BuildRepository();
         ~BuildRepository();

         Hexagon::BuildSystem::Build* get_latest_if_exists();
      };
   }
}



