#pragma once


#include <Hexagon/BuildSystem/BuildStageRenderers/Base.hpp>
#include <Hexagon/BuildSystem/BuildStages/ShellCommand.hpp>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace BuildStageRenderers
      {
         class ShellCommand : public Hexagon::BuildSystem::BuildStageRenderers::Base
         {
         public:
            static constexpr char* TYPE = "ShellCommand";

         private:
            Hexagon::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage;

         public:
            ShellCommand(Hexagon::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage=nullptr);
            ~ShellCommand();

         };
      }
   }
}



