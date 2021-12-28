#pragma once


#include <string>


namespace Hexagon
{
   class PacketLogger
   {
   private:
      std::string PACKET_LOG_FOLDER_LOCATION;
      std::string project_name;
      std::string commit_message;
      int searches_count;
      int saves_count;
      int score;
      std::string datetime;

   public:
      PacketLogger(std::string project_name="[project-name-not-set]", std::string commit_message="[commit-message-not-set]", int searches_count=-1, int saves_count=-1, int score=-1);
      ~PacketLogger();

      void set_PACKET_LOG_FOLDER_LOCATION(std::string PACKET_LOG_FOLDER_LOCATION);
      void set_datetime(std::string datetime);
      std::string get_PACKET_LOG_FOLDER_LOCATION();
      std::string get_datetime();
      void write_log_file();
      std::string generate_log_filename();
      std::string generate_log_file_contents();
      static std::string generate_time_now_string();
   };
}



