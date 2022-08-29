#pragma once


#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace Builds
      {
         class Base
         {
         private:
            std::string type;
            float started_at;
            float ended_at;
            std::string status;
            std::vector<Hexagon::BuildSystem::BuildStages::Base*> stages;

         public:
            Base(std::string type="Base");
            ~Base();

            std::string get_type() const;
            float get_started_at() const;
            float get_ended_at() const;
            std::string get_status() const;
            bool is_type(std::string possible_type="");
         };
      }
   }
}



