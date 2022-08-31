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
         Hexagon::BuildSystem::Builds::Base* build;

      protected:


      public:
         ReportRenderer(Hexagon::BuildSystem::Builds::Base* build=nullptr);
         ~ReportRenderer();

         void set_build(Hexagon::BuildSystem::Builds::Base* build);
         Hexagon::BuildSystem::Builds::Base* get_build() const;
         std::string build_text_report();
      };
   }
}



