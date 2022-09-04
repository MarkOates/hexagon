#pragma once


#include <chrono>
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
            static constexpr char* TYPE = "Base";
            static constexpr char* STATUS_NOT_STARTED = "not_started";
            static constexpr char* STATUS_RUNNING = "running";
            static constexpr char* STATUS_FINISHED = "finished";
            static constexpr char* STATUS_ERROR = "error";
            static constexpr char* STATUS_FAILED = "failed";

         private:
            std::string type;
            std::chrono::system_clock::time_point started_at;
            std::chrono::system_clock::time_point ended_at;
            std::string status;

         protected:


         public:
            Base(std::string type=TYPE);
            virtual ~Base();

            void set_started_at(std::chrono::system_clock::time_point started_at);
            void set_ended_at(std::chrono::system_clock::time_point ended_at);
            void set_status(std::string status);
            std::string get_type() const;
            std::chrono::system_clock::time_point get_started_at() const;
            std::chrono::system_clock::time_point get_ended_at() const;
            std::string get_status() const;
            bool is_type(std::string possible_type="");
            virtual void execute();
         };
      }
   }
}



