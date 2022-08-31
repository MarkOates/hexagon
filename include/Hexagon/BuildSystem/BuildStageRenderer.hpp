#pragma once


#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      class BuildStageRenderer
      {
      private:
         Hexagon::BuildSystem::BuildStages::Base* build_stage;

      protected:


      public:
         BuildStageRenderer(Hexagon::BuildSystem::BuildStages::Base* build_stage=nullptr);
         ~BuildStageRenderer();

         void set_build_stage(Hexagon::BuildSystem::BuildStages::Base* build_stage);
         Hexagon::BuildSystem::BuildStages::Base* get_build_stage() const;
         std::string build_text_report();
      };
   }
}



