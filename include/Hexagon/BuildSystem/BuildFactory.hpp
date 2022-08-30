#pragma once


#include <Hexagon/BuildSystem/BuildStageFactory.hpp>
#include <Hexagon/BuildSystem/Builds/Base.hpp>


namespace Hexagon
{
   namespace BuildSystem
   {
      class BuildFactory
      {
      private:
         Hexagon::BuildSystem::BuildStageFactory build_stage_factory;

      public:
         BuildFactory();
         ~BuildFactory();

         Hexagon::BuildSystem::Builds::Base* create_placeholder_build();
      };
   }
}



