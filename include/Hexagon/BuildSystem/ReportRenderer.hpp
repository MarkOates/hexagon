#pragma once


#include <Hexagon/BuildSystem/Builds/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      class ReportRenderer
      {
      private:
         Hexagon::BuildSystem::Builds::Base* report;

      public:
         ReportRenderer(Hexagon::BuildSystem::Builds::Base* report=nullptr);
         ~ReportRenderer();

         void set_report(Hexagon::BuildSystem::Builds::Base* report);
         Hexagon::BuildSystem::Builds::Base* get_report() const;
         std::string build_report();
      };
   }
}



