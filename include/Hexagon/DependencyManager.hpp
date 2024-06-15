#pragma once


#include <map>
#include <set>
#include <string>


namespace Hexagon
{
   class DependencyManager
   {
   public:
      static constexpr char* DEPS_FOLDER = (char*)".deps/";

   private:
      std::string project_folder;
      std::map<std::string, std::set<std::string>> dependencies;
      std::map<std::string, std::set<std::string>> dependents;
      bool loaded;
      bool dependencies_loaded;
      void load_dependencies();
      void build_dependents_from_dependencies();

   protected:


   public:
      DependencyManager(std::string project_folder="/Users/markoates/Hexagon/");
      ~DependencyManager();

      std::string get_project_folder() const;
      std::map<std::string, std::set<std::string>> get_dependencies() const;
      std::map<std::string, std::set<std::string>> get_dependents() const;
      bool get_loaded() const;
      bool get_dependencies_loaded() const;
      void set_project_folder(std::string project_folder="/Users/markoates/Hexagon/");
      void load_from_source_tree();
      void reload_dependency_file(std::string dependency_name="[unset-dependency_name]", std::string filename="[unset-filename]");
   };
}



