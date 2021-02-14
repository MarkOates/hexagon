#pragma once


#include <Hexagon/Project.hpp>
#include <string>


namespace Hexagon
{
   class ProjectFromYAML
   {
   private:
      std::string name;
      std::string source_yaml;

   public:
      ProjectFromYAML(std::string name="Untitled", std::string source_yaml="# empty");
      ~ProjectFromYAML();

      Hexagon::Project load();
   };
}



