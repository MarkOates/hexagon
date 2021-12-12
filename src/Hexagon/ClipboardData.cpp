


#include <Hexagon/ClipboardData.hpp>

#include <Hexagon/util.hpp>
#include <Hexagon/shared_globals.hpp>
#include <Hexagon/PasteboardData.hpp>
#include <Blast/StringJoiner.hpp>
#include <Blast/StringSplitter.hpp>



bool ClipboardData::store(std::string line)
{
   std::vector<std::string> as_list = {line};
   return ClipboardData::store(as_list);
}



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
      std::string clipboard_content = Hexagon::PasteboardData::retrieve();
      std::vector<std::string> multi_line_content = Blast::StringSplitter(clipboard_content, '\n').split();
      result = multi_line_content;
   }
   else
   {
      ::read_file(result, CLIPBOARD_TEMP_FILENAME);
   }
   return result;
}



