#pragma once


#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace Builds
      {
         class Base
         {
         public:
            static constexpr char* STATUS_NOT_STARTED = "not_started";
            static constexpr char* STATUS_RUNNING = "running";
            static constexpr char* STATUS_FINISHED = "finished";
            static constexpr char* STATUS_FAILED = "failed";

         private:
            std::string type;
            float started_at;
            float ended_at;
            std::string status;
            std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages;

         public:
            Base(std::string type="Base");
            ~Base();

            void set_started_at(float started_at);
            void set_ended_at(float ended_at);
            void set_status(std::string status);
            void set_build_stages(std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages);
            std::string get_type() const;
            float get_started_at() const;
            float get_ended_at() const;
            std::string get_status() const;
            std::vector<Hexagon::BuildSystem::BuildStages::Base*> get_build_stages() const;
            bool is_type(std::string possible_type="");
            void start();
         };
      }
   }
}



