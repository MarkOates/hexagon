#pragma once


#include <chrono>
#include <mutex>
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
            static constexpr char* STATUS_WAITING_TO_START = "waiting_to_start";
            static constexpr char* STATUS_RUNNING = "running";
            static constexpr char* STATUS_SUCCEEDED = "succeeded";
            static constexpr char* STATUS_ERROR = "error";
            static constexpr char* STATUS_FAILED = "failed";

         private:
            std::string type;
            std::chrono::system_clock::time_point started_at;
            std::mutex mutex_for_started_at;
            std::chrono::system_clock::time_point ended_at;
            std::mutex mutex_for_ended_at;
            std::string status;
            std::mutex mutex_for_status;

         protected:


         public:
            Base(std::string type=TYPE);
            virtual ~Base();

            std::string get_type() const;
            std::string get_status();
            void set_status(std::string status="[unset-status]");
            std::chrono::system_clock::time_point get_started_at();
            void set_started_at(std::chrono::system_clock::time_point started_at);
            std::chrono::system_clock::time_point get_ended_at();
            void set_ended_at(std::chrono::system_clock::time_point ended_at);
            bool is_type(std::string possible_type="");
            virtual bool execute();
            double calc_duration_seconds();
         };
      }
   }
}



