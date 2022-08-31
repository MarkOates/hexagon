#pragma once


#include <Hexagon/BuildSystem/BuildStages/ShellCommand.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      class BuildStageFactory
      {
      private:

      protected:


      public:
         BuildStageFactory();
         ~BuildStageFactory();

         Hexagon::BuildSystem::BuildStages::ShellCommand* create_shell_command_build_stage(std::string shell_command="echo \"Hi friend\"");
      };
   }
}



