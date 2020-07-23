

#include <Hexagon/Project.hpp>



namespace Hexagon
{


Project::Project(std::string project_name, std::string project_root, std::vector<std::tuple<std::string, Hexagon::Layout>> layouts)
   : project_name(project_name)
   , project_root(project_root)
   , layouts(layouts)
{
}


Project::~Project()
{
}


void Project::set_project_name(std::string project_name)
{
   this->project_name = project_name;
}


void Project::set_project_root(std::string project_root)
{
   this->project_root = project_root;
}


void Project::set_layouts(std::vector<std::tuple<std::string, Hexagon::Layout>> layouts)
{
   this->layouts = layouts;
}


std::string Project::get_project_name()
{
   return project_name;
}


std::string Project::get_project_root()
{
   return project_root;
}


std::vector<std::tuple<std::string, Hexagon::Layout>> Project::get_layouts()
{
   return layouts;
}


} // namespace Hexagon


