


#include <Hexagon/ClipboardData.hpp>

#include <Hexagon/util.hpp>
#include <Hexagon/shared_globals.hpp>



bool ClipboardData::store(std::vector<std::string> &lines)
{
   ::save_file(lines, CLIPBOARD_TEMP_FILENAME);
   return true;
}



std::vector<std::string> ClipboardData::retrieve()
{
   std::vector<std::string> results;
   ::read_file(results, CLIPBOARD_TEMP_FILENAME);
   return results;
}



