

#include <Blast/Project/ComponentRelativeLister.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <sstream>
#include <algorithm>


namespace Blast
{
namespace Project
{


ComponentRelativeLister::ComponentRelativeLister(Blast::Project::Component* component)
   : component(component)
{
}


ComponentRelativeLister::~ComponentRelativeLister()
{
}


std::vector<std::string> ComponentRelativeLister::list_component_relative_names()
{
   if (!component)
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::ComponentRelativeLister error] "
                    << "cannot list_component_relative_names with a nullptr component";
      throw std::runtime_error(error_message.str());
   }

   if (!component->exists())
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::ComponentRelativeLister error] "
                    << "cannot list_component_relative_names; The component \""
                    << component->get_name() << "\" does not exist";
      throw std::runtime_error(error_message.str());
   }

   std::string component_name = component->get_name();

   std::string::size_type pos_of_last_slash = component_name.find_last_of("/");
   if (pos_of_last_slash == std::string::npos) { pos_of_last_slash = 0; }

   std::string component_name_without_last_fragment = component_name.substr(0, pos_of_last_slash+1);

   int num_of_component_slashes = std::count(component_name.begin(), component_name.end(), '/');

   Blast::Project::ComponentLister component_lister(component->get_project_root());
   std::vector<std::string> entire_project_tree_component_names = component_lister.components();

   std::vector<std::string> result = {};
   for (auto &component_name : entire_project_tree_component_names)
   {
      std::string this_component_name_without_last_fragment = component_name.substr(0, pos_of_last_slash+1);
      if (component_name_without_last_fragment != this_component_name_without_last_fragment) continue;

      int this_num_of_component_slashes = std::count(component_name.begin(), component_name.end(), '/');
      if (num_of_component_slashes != this_num_of_component_slashes) continue;

      result.push_back(component_name);
   }

   return result;
}
} // namespace Project
} // namespace Blast


