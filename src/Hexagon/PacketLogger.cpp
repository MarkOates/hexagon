

#include <Hexagon/PacketLogger.hpp>
#include <allegro_flare/useful_php.h>
#include <sstream>
#include <chrono>
#include <ctime>
#include <Blast/String/Trimmer.hpp>


namespace Hexagon
{


PacketLogger::PacketLogger(std::string project_name, std::string commit_message, int searches_count, int saves_count, int score, std::string currently_posted_objective)
   : PACKET_LOG_FOLDER_LOCATION("/Users/markoates/Repos/me/programming_logs")
   , project_name(project_name)
   , commit_message(commit_message)
   , searches_count(searches_count)
   , saves_count(saves_count)
   , score(score)
   , currently_posted_objective(currently_posted_objective)
   , datetime(generate_time_now_string())
{
}


PacketLogger::~PacketLogger()
{
}


void PacketLogger::set_PACKET_LOG_FOLDER_LOCATION(std::string PACKET_LOG_FOLDER_LOCATION)
{
   this->PACKET_LOG_FOLDER_LOCATION = PACKET_LOG_FOLDER_LOCATION;
}


void PacketLogger::set_datetime(std::string datetime)
{
   this->datetime = datetime;
}


std::string PacketLogger::get_PACKET_LOG_FOLDER_LOCATION()
{
   return PACKET_LOG_FOLDER_LOCATION;
}


std::string PacketLogger::get_datetime()
{
   return datetime;
}


void PacketLogger::write_log_file()
{
   std::string filename = generate_log_filename();
   std::string file_contents = generate_log_file_contents();
   php::file_put_contents(filename, file_contents);
   return;
}

std::string PacketLogger::generate_log_filename()
{
   std::string result = PACKET_LOG_FOLDER_LOCATION + "/" + datetime;
   result += ".log.txt";
   return result;
}

std::string PacketLogger::generate_log_file_contents()
{
   std::stringstream result;

   result << "project: " << project_name << std::endl;
   result << "commit_message: " << commit_message << std::endl;
   result << "datetime: " << datetime << std::endl;
   result << "searches: " << searches_count << std::endl;
   result << "saves: " << saves_count << std::endl;
   result << "score: " << score << std::endl;
   result << "currently_posted_objective: " << currently_posted_objective << std::endl;
   result << "time_posted: " << generate_time_now_string() << std::endl;

   return result.str();
}

std::string PacketLogger::generate_time_now_string()
{
   auto end = std::chrono::system_clock::now();
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);

   std::stringstream time_message;
   time_message << std::ctime(&end_time);
   std::string trimmed_time_message = Blast::String::Trimmer(time_message.str()).trim();

   return trimmed_time_message;
}
} // namespace Hexagon


