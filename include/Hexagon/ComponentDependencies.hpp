#pragma once


#include <set>
#include <string>


namespace Hexagon
{
   class ComponentDependencies
   {
   private:
      std::string component_name;
      std::set<std::string> dependencies;

   protected:


   public:
      ComponentDependencies(std::string component_name="[unset-component_name]");
      ~ComponentDependencies();

      std::set<std::string> get_dependencies() const;
      std::string generate_dependency_filename();
   };
}



