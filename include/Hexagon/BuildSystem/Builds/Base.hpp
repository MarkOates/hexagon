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
            static constexpr char* TYPE = "Base";
            static constexpr char* STATUS_NOT_STARTED = "not_started";
            static constexpr char* STATUS_RUNNING = "running";
            static constexpr char* STATUS_FINISHED = "finished";
            static constexpr char* STATUS_ERROR = "error";

         private:
            std::string type;
            std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages;
            float started_at;
            float ended_at;
            std::string status;

         public:
            Base(std::string type=TYPE, std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages={});
            ~Base();

            void set_build_stages(std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages);
            void set_started_at(float started_at);
            void set_ended_at(float ended_at);
            void set_status(std::string status);
            std::string get_type() const;
            std::vector<Hexagon::BuildSystem::BuildStages::Base*> get_build_stages() const;
            float get_started_at() const;
            float get_ended_at() const;
            std::string get_status() const;
            bool is_type(std::string possible_type="");
            void run();
         };
      }
   }
}



