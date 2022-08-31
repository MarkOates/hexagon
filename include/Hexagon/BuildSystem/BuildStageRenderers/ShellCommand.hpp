#pragma once


#include <Hexagon/BuildSystem/BuildStageRenderers/Base.hpp>
#include <Hexagon/BuildSystem/BuildStages/ShellCommand.hpp>
#include <string>


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

         protected:


         public:
            ShellCommand(Hexagon::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage=nullptr);
            virtual ~ShellCommand();

            void set_shell_command_build_stage(Hexagon::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage);
            virtual std::string render_text() override;
         };
      }
   }
}



