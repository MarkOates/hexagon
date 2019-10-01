#pragma once


#include <string>


namespace NcursesArt
{
   class ProjectComponentBasenameExtractor
   {
   private:
      std::string filename;

   public:
      ProjectComponentBasenameExtractor(std::string filename="");
      ~ProjectComponentBasenameExtractor();


   std::string identify_file_type();
   bool is_identifiable_component();
   std::string identify_component_basename();
   std::pair<std::string, std::string> extract_component();
   };
}



