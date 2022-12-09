#pragma once


#include <Hexagon/BuildSystem/Builds/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace ReportRenderers
      {
         class Base
         {
         public:
            static constexpr char* TYPE = "Base";

         private:
            std::string type;
            Hexagon::BuildSystem::Builds::Base* build;

         protected:


         public:
            Base(std::string type=TYPE);
            virtual ~Base();

            void set_build(Hexagon::BuildSystem::Builds::Base* build);
            std::string get_type() const;
            Hexagon::BuildSystem::Builds::Base* get_build() const;
            bool is_type(std::string possible_type="");
            virtual std::string render_text();
            std::string colorize_status(std::string status="[unset-status]");
         };
      }
   }
}



