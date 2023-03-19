#pragma once


#include <set>
#include <string>


namespace Hexagon
{
   class ComponentDependencyFileParser
   {
   private:
      std::string dependency_filename;

   protected:


   public:
      ComponentDependencyFileParser(std::string dependency_filename="[unset-component_name]");
      ~ComponentDependencyFileParser();

      std::set<std::string> generate_dependencies();
   };
}



