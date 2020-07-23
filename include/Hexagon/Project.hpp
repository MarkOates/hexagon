#pragma once


#include <Hexagon/Layout.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   class Project
   {
   private:
      std::string project_name;
      std::string project_root;
      std::vector<std::tuple<std::string, Hexagon::Layout>> layouts;

   public:
      Project(std::string project_name="- Untitled -", std::string project_root="/Users/markoates/Repos/hexagon/", std::vector<std::tuple<std::string, Hexagon::Layout>> layouts={});
      ~Project();

      void set_project_name(std::string project_name);
      void set_project_root(std::string project_root);
      void set_layouts(std::vector<std::tuple<std::string, Hexagon::Layout>> layouts);

      std::string get_project_name();
      std::string get_project_root();
      std::vector<std::tuple<std::string, Hexagon::Layout>> get_layouts();
   };
}



