

#include <Hexagon/Daemus/Builds/ExtrapolateQuintessence.hpp>
#include <allegro_flare/useful_php.h>
#include <sstream>
#include <Blast/String/Trimmer.hpp>
#include <chrono>
#include <ctime>


namespace Hexagon
{
namespace Daemus
{
namespace Builds
{


ExtrapolateQuintessence::ExtrapolateQuintessence()
   : Hexagon::Daemus::Builds::Base("ExtrapolateQuintessence")
   , BUILDS_PENDING_FOLDER_LOCATION("/Users/markoates/Repos/hexagon/bin/programs/data/builds/pending")
{
}


ExtrapolateQuintessence::~ExtrapolateQuintessence()
{
}


void ExtrapolateQuintessence::set_BUILDS_PENDING_FOLDER_LOCATION(std::string BUILDS_PENDING_FOLDER_LOCATION)
{
   this->BUILDS_PENDING_FOLDER_LOCATION = BUILDS_PENDING_FOLDER_LOCATION;
}


std::string ExtrapolateQuintessence::get_BUILDS_PENDING_FOLDER_LOCATION()
{
   return BUILDS_PENDING_FOLDER_LOCATION;
}


void ExtrapolateQuintessence::initiate()
{
   // TODO: write a bulid_file (or otherwise send whatever message) that the rerun terminal daemus is watching for
   return;
}

void ExtrapolateQuintessence::write_build_file()
{
   std::string filename = generate_build_filename();
   std::string file_contents = generate_build_file_contents();
   php::file_put_contents(filename, file_contents);
   return;
}

void ExtrapolateQuintessence::poll_for_progress()
{
   // TODO
   return;
}

std::string ExtrapolateQuintessence::generate_build_file_contents()
{
   return "build_contents";
}

std::string ExtrapolateQuintessence::generate_build_filename()
{
   std::string datetime = generate_time_now_string();
   std::string result = BUILDS_PENDING_FOLDER_LOCATION + "/" + datetime;
   result += ".build.txt";
   return result;
}

std::string ExtrapolateQuintessence::generate_time_now_string()
{
   auto end = std::chrono::system_clock::now();
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);

   std::stringstream time_message;
   time_message << std::ctime(&end_time);
   std::string trimmed_time_message = Blast::String::Trimmer(time_message.str()).trim();

   return trimmed_time_message;
}
} // namespace Builds
} // namespace Daemus
} // namespace Hexagon


