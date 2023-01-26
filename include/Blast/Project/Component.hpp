#pragma once


#include <Blast/ProjectComponentFileTypes.hpp>
#include <ctime>
#include <string>
#include <utility>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class Component
      {
      private:
         std::string name;
         std::string project_root;
         bool check_file_existence(Blast::ProjectComponentFileTypes::project_file_type_t type=Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE);

      protected:


      public:
         Component(std::string name="Unnamed/Component", std::string project_root="");
         ~Component();

         std::string get_name() const;
         std::string get_project_root() const;
         std::string generate_full_path_test_binary_filename();
         std::vector<std::string> list_existing_component_files();
         std::time_t last_write_time();
         static std::time_t check_fragment_file_last_write_time(std::string project_root="[unset-project_root]", std::string name="[unset-name]", Blast::ProjectComponentFileTypes::project_file_type_t fragment_type=Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE);
         bool exists();
         bool has_quintessence();
         bool has_only_source_and_header();
         bool has_test();
         bool has_documentation();
         std::vector<std::pair<std::string, std::string>> read_symlinks();
      };
   }
}



