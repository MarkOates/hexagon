

#include <Hexagon/ProjectFactory.hpp>



namespace Hexagon
{


ProjectFactory::ProjectFactory()
{
}


ProjectFactory::~ProjectFactory()
{
}


Hexagon::Project ProjectFactory::partner_performance_dashboard()
{
std::string project_name = "Partner Performance Dashboard";
std::string project_root = "/Users/markoates/Repos/hexagon/";
std::vector<std::tuple<std::string, Hexagon::Layout>> layouts = {};

return Hexagon::Project(project_name, project_root, layouts);

}
} // namespace Hexagon


