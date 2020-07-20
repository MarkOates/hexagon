#pragma once


#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   class Layout
   {
   private:
      std::string project_root;
      std::vector<std::tuple<std::string, float, float>> file;
      std::string daemus_command;

   public:
      Layout(std::string project_root="", std::vector<std::tuple<std::string, float, float>> file={}, std::string daemus_command="");
      ~Layout();

      void set_file(std::vector<std::tuple<std::string, float, float>> file);

      std::string get_project_root();
      std::vector<std::tuple<std::string, float, float>> get_file();
      std::string get_daemus_command();
   };
}



