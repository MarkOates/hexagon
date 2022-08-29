#pragma once


#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace BuildStages
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

         public:
            Base(std::string type="Base");
            virtual ~Base();

            void set_started_at(float started_at);
            void set_ended_at(float ended_at);
            void set_status(std::string status);
            std::string get_type() const;
            float get_started_at() const;
            float get_ended_at() const;
            std::string get_status() const;
            bool is_type(std::string possible_type="");
            virtual void execute_raw();
            void execute();
         };
      }
   }
}



