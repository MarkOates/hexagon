


#include <Hexagon/ClipboardData.hpp>

#include <Hexagon/util.hpp>
#include <Hexagon/shared_globals.hpp>
#include <Hexagon/PasteboardData.hpp>
#include <Blast/StringJoiner.hpp>



bool ClipboardData::store(std::vector<std::string> &lines)
{
   bool using_pasteboard = true;
   if (using_pasteboard)
   {
      std::string single_line_content = Blast::StringJoiner(lines, "\n").join();
      Hexagon::PasteboardData::store(single_line_content);
   }
   else
   {
     ::save_file(lines, CLIPBOARD_TEMP_FILENAME);
   }
   return true;
}



std::vector<std::string> ClipboardData::retrieve()
{
   std::vector<std::string> result;
   bool using_pasteboard = true;

   if (using_pasteboard)
   {
      result = { Hexagon::PasteboardData::retrieve() };
   }
   else
   {
      ::read_file(result, CLIPBOARD_TEMP_FILENAME);
   }
   return result;
}



