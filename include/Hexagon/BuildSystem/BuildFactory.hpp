#pragma once


#include <Hexagon/BuildSystem/BuildStageFactory.hpp>
#include <Hexagon/BuildSystem/Builds/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      class BuildFactory
      {
      private:
         Hexagon::BuildSystem::BuildStageFactory build_stage_factory;

      protected:


      public:
         BuildFactory();
         ~BuildFactory();

         Hexagon::BuildSystem::Builds::Base* create_placeholder_build();
         Hexagon::BuildSystem::Builds::Base* create_shell_command_build(std::string shell_command="echo \"Having a good day?\"");
      };
   }
}



