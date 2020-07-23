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
      Project();
      ~Project();


   std::string run();
   };
}



