#pragma once


#include <string>


namespace NcursesArt
{
   class ProjectFilenameGenerator
   {
   private:
      std::string basename;
      bool underscores;

   protected:


   public:
      ProjectFilenameGenerator(std::string basename="", bool underscores="");
      ~ProjectFilenameGenerator();

      std::string get_basename() const;
      std::string generate_quintessence_filename();
      std::string generate_source_filename();
      std::string generate_header_filename();
      std::string generate_test_src_filename();
      std::string generate_example_src_filename();
      std::string generate_obj_binary();
      std::string generate_test_binary();
      std::string generate_example_binary();
   };
}



