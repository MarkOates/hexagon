

#include <Hexagon/DependencyManager.hpp>

#include <Hexagon/ComponentDependencyFileParser.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{


DependencyManager::DependencyManager(std::string project_folder)
   : project_folder(project_folder)
   , dependencies({})
   , dependents({})
   , loaded(false)
   , dependencies_loaded(false)
{
}


DependencyManager::~DependencyManager()
{
}


std::string DependencyManager::get_project_folder() const
{
   return project_folder;
}


std::map<std::string, std::set<std::string>> DependencyManager::get_dependencies() const
{
   return dependencies;
}


std::map<std::string, std::set<std::string>> DependencyManager::get_dependents() const
{
   return dependents;
}


bool DependencyManager::get_loaded() const
{
   return loaded;
}


bool DependencyManager::get_dependencies_loaded() const
{
   return dependencies_loaded;
}


void DependencyManager::set_project_folder(std::string project_folder)
{
   this->project_folder = project_folder;
   loaded = false;
   return;
}

void DependencyManager::load_from_source_tree()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[DependencyManager::load_from_source_tree]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DependencyManager::load_from_source_tree: error: guard \"(!loaded)\" not met");
   }
   load_dependencies();
   build_dependents_from_dependencies();
   loaded = true;
   return;
}

void DependencyManager::reload_dependency_file(std::string dependency_name, std::string filename)
{
   std::map<std::string, std::set<std::string>>::iterator dependencies_it = dependencies.find(dependency_name);
   std::set<std::string> dependencys_dependents;

   // kill the dependency with the key
   if (dependencies_it != dependencies.end())
   {
      dependencys_dependents = dependencies_it->second;
      dependencies.erase(dependencies_it);
   }

   // each dependency from within that key, remove the dependency from each's list
   for (auto &dependencys_dependent : dependencys_dependents)
   {
      std::map<std::string, std::set<std::string>>::iterator dependencys_dependent_it =
         dependents.find(dependencys_dependent);
      if (dependencys_dependent_it != dependents.end())
      {
         auto &dependencys_dependent_dependencies = dependencys_dependent_it->second;
         std::set<std::string>::iterator wah_it = dependencys_dependent_dependencies.find(dependency_name);
         if (wah_it != dependencys_dependent_dependencies.end())
         {
            dependencys_dependent_dependencies.erase(wah_it);
         }
      }
   }



   // update the dependencies

         std::string component_name = dependency_name;
         Hexagon::ComponentDependencyFileParser dependency_file_parser(filename);

         std::set<std::string> this_component_dependencies = dependency_file_parser.generate_dependencies();

         // filter the dependencies, keeping only ones inside "include/*"
         std::set<std::string> filtered_dependencies;
         std::string include_prefix = "include/";
         for (auto &this_component_dependency : this_component_dependencies)
         {
            // if the listed dependency is in the local "include/" folder, select it
            if (this_component_dependency.substr(0, include_prefix.length()) == include_prefix)
            {
               //std::cout << "SELECTED: " << this_component_dependency << std::endl;
               // filter out the "include/" part of the string, as well as the ".h", ".hpp", (or any other) extension
               std::string dependency_component_name = this_component_dependency.substr(include_prefix.length());
               std::size_t pos_of_dot = dependency_component_name.find_last_of('.');
               if (pos_of_dot != std::string::npos)
               {
                  dependency_component_name = dependency_component_name.substr(0, pos_of_dot);
               }

               if (dependency_component_name != component_name)
               {
                  filtered_dependencies.insert(dependency_component_name);
               }
            }
            else
            {
               //std::cout << "REJECTED: " << this_component_dependency << std::endl;
            }
         }

         dependencies[component_name] = filtered_dependencies;



   // update the dependents

      auto &dependency_dictionary_listing_dependencies = dependencies[component_name];
      std::string dependency_dictionary_listing_name = component_name;

      for (auto &dependency : dependency_dictionary_listing_dependencies)
      {
         dependents[dependency].insert(dependency_dictionary_listing_name);
      }

   return;
}

void DependencyManager::load_dependencies()
{
   std::string deps_folder_in_project = project_folder + DEPS_FOLDER;

   std::size_t prefix_length = deps_folder_in_project.size();
   for(const std::filesystem::directory_entry &p
      : std::filesystem::recursive_directory_iterator(deps_folder_in_project))
   {
      // convert the path to a string
      std::string filename = p.path().string();

      // remove the project_folder prefix
      std::string component_name = filename.substr(prefix_length);

      if (filename.size() > 2 && filename.substr(filename.length()-2) == ".d")
      {
         // remove the .d extension, leaving only "The/Component/Name" (hopefully)
         component_name = component_name.substr(0, component_name.length()-2);

         // filename
         Hexagon::ComponentDependencyFileParser dependency_file_parser(filename);

         std::set<std::string> this_component_dependencies = dependency_file_parser.generate_dependencies();

         // filter the dependencies, keeping only ones inside "include/*"
         std::set<std::string> filtered_dependencies;
         std::string include_prefix = "include/";
         for (auto &this_component_dependency : this_component_dependencies)
         {
            // if the listed dependency is in the local "include/" folder, select it
            if (this_component_dependency.substr(0, include_prefix.length()) == include_prefix)
            {
               //std::cout << "SELECTED: " << this_component_dependency << std::endl;
               // filter out the "include/" part of the string, as well as the ".h", ".hpp", (or any other) extension
               std::string dependency_component_name = this_component_dependency.substr(include_prefix.length());
               std::size_t pos_of_dot = dependency_component_name.find_last_of('.');
               if (pos_of_dot != std::string::npos)
               {
                  dependency_component_name = dependency_component_name.substr(0, pos_of_dot);
               }

               if (dependency_component_name != component_name)
               {
                  filtered_dependencies.insert(dependency_component_name);
               }
            }
            else
            {
               //std::cout << "REJECTED: " << this_component_dependency << std::endl;
            }
         }

         dependencies[component_name] = filtered_dependencies;
      }
   }

   dependencies_loaded = true;

   return;
}

void DependencyManager::build_dependents_from_dependencies()
{
   if (!(dependencies_loaded))
   {
      std::stringstream error_message;
      error_message << "[DependencyManager::build_dependents_from_dependencies]: error: guard \"dependencies_loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DependencyManager::build_dependents_from_dependencies: error: guard \"dependencies_loaded\" not met");
   }
   for (auto &dependency_dictionary_listing : dependencies)
   {
      std::string dependency_dictionary_listing_name = dependency_dictionary_listing.first;
      auto &dependency_dictionary_listing_dependencies = dependency_dictionary_listing.second;

      for (auto &dependency : dependency_dictionary_listing_dependencies)
      {
         dependents[dependency].insert(dependency_dictionary_listing_name);
      }
   }
   return;
}


} // namespace Hexagon


