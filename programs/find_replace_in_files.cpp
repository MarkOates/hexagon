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
   if (argc != 4 && argc != 5)
   {
      std::stringstream error_message;
      error_message << "You must have 3 (or 4) args, [ file_find_pattern, search_pattern, replace_pattern ] or "
                    << "[ file_find_pattern, file_exclude_pattern, search_pattern, replace_pattern ]" << std::endl
                    << "Example: " << argv[0] << " *.txt foo baz" << std::endl
                    << "Note this program will not run the command, it will simply generate it for you to copy "
                    << "and run yourself." << std::endl;
      std::cout << error_message.str();
      return 1;
   }

   std::string file_find_pattern;
   std::string exclude_file_find_pattern;
   std::string search_pattern;
   std::string replace_pattern;

   if (argc == 4)
   {
      file_find_pattern = argv[1];
      search_pattern = argv[2];
      replace_pattern = argv[3];
   }
   if (argc == 5)
   {
      file_find_pattern = argv[1];
      exclude_file_find_pattern = argv[2];
      search_pattern = argv[3];
      replace_pattern = argv[4];
   }

   // sanitize the file_find_pattern
   // must escape " char
   file_find_pattern = replace_all(file_find_pattern, "\\", "\\\\");
   file_find_pattern = replace_all(file_find_pattern, "\"", "\\\"");

   // sanitize the exclude_file_find_pattern
   // must escape " char
   exclude_file_find_pattern = replace_all(exclude_file_find_pattern, "\\", "\\\\");
   exclude_file_find_pattern = replace_all(exclude_file_find_pattern, "\"", "\\\"");

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
   // currently in exclude_file_find_pattern
   // if blank, don't include it
   // -not -path "./directory/*"
   std::stringstream exclude_addition;
   if (!exclude_file_find_pattern.empty()) exclude_addition << " -not -path \"" << exclude_file_find_pattern << "\" ";

   std::stringstream dry_run_command;
   dry_run_command << "find . -type f -name \"" << file_find_pattern << "\"" << exclude_addition.str() << std::endl;

   std::stringstream command;
   command << "find . -type f -name \"" << file_find_pattern << "\"" << exclude_addition.str() << " -print0 | xargs -0 sed -i '' -e 's/"
           << search_pattern << "/" << replace_pattern << "/g'" << std::endl;

   std::cout << "====== DRY RUN =======" << std::endl;
   std::cout << dry_run_command.str();
   std::cout << "====== FULL COMMAND =======" << std::endl;
   std::cout << command.str();

   return 0;
}


