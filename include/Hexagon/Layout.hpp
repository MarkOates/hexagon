#pragma once


#include <allegro_flare/placement3d.h>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   class Layout
   {
   private:
      std::string concept_name;
      std::vector<std::tuple<std::string, std::string, placement3d>> files;
      std::string daemus_command;

   public:
      Layout(std::string concept_name="", std::vector<std::tuple<std::string, std::string, placement3d>> files={}, std::string daemus_command="");
      ~Layout();

      void set_concept_name(std::string concept_name);
      void set_files(std::vector<std::tuple<std::string, std::string, placement3d>> files);
      std::string get_concept_name() const;
      std::vector<std::tuple<std::string, std::string, placement3d>> get_files() const;
      std::string get_daemus_command() const;
      std::vector<std::tuple<std::string, std::string, placement3d>> &get_files_ref();
   };
}



