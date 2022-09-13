#include <allegro5/allegro.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>


std::string replace_all(std::string str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}


int main(int argc, char **argv)
{
   if (argc != 4)
   {
      std::stringstream error_message;
      error_message << "You must have 3 args, file_find_pattern, search_pattern, replace_pattern" << std::endl
                    << "Example: " << argv[0] << " *.txt foo baz" << std::endl
                    << "Note this program will not run the command, it will simply generate it for you to copy "
                    << "and run yourself." << std::endl;
      std::cout << error_message.str();
      return 1;
   }

   std::string file_find_pattern = argv[1];
   std::string search_pattern = argv[2];
   std::string replace_pattern = argv[3];

   // sanitize the file_find_pattern
   // must escape " char
   file_find_pattern = replace_all(file_find_pattern, "\\", "\\\\");
   file_find_pattern = replace_all(file_find_pattern, "\"", "\\\"");

   // sanitize the search_pattern
   // must escape \, ', and / char
   search_pattern = replace_all(search_pattern, "\\", "\\\\");
   search_pattern = replace_all(search_pattern, "'", "\\'");
   search_pattern = replace_all(search_pattern, "/", "\\/");

   // sanitize the replace_pattern
   // must escape \, ', and / char
   replace_pattern = replace_all(replace_pattern, "\\", "\\\\");
   replace_pattern = replace_all(replace_pattern, "'", "\\'");
   replace_pattern = replace_all(replace_pattern, "/", "\\/");

   // https://superuser.com/questions/428493/how-can-i-do-a-recursive-find-and-replace-from-the-command-line
   // find . -type f -name "*.txt" -print0 | xargs -0 sed -i '' -e 's/foo/bar/g'

   // TODO
   // -not -path "./directory/*"

   std::stringstream dry_run_command;
   dry_run_command << "find . -type f -name \"" << file_find_pattern << "\"" << std::endl;

   std::stringstream command;
   command << "find . -type f -name \"" << file_find_pattern << "\" -print0 | xargs -0 sed -i '' -e 's/"
           << search_pattern << "/" << replace_pattern << "/g'" << std::endl;

   std::cout << "====== DRY RUN =======" << std::endl;
   std::cout << dry_run_command.str();
   std::cout << "====== DRY RUN =======" << std::endl;
   std::cout << command.str();
   std::cout << "====== DRY RUN =======" << std::endl;

   return 0;
}


