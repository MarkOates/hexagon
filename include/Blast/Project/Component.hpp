#pragma once


#include <Blast/ProjectComponentFileTypes.hpp>
#include <string>


namespace Blast
{
   namespace Project
   {
      class Component
      {
      private:
         std::string name;

      public:
         Component(std::string name="Unnamed/Component");
         ~Component();


         std::string get_name();
      bool check_file_existence(Blast::ProjectComponentFileTypes::project_file_type_t type=Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE);
      bool exists();
      bool has_quintessence();
      bool has_only_source_and_header();
      bool has_test();
      };
   }
}



