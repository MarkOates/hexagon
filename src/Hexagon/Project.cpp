

#include <Hexagon/Project.hpp>



namespace Hexagon
{


Project::Project()
   : project_name("")
   , project_root("")
   , layouts({})
{
}


Project::~Project()
{
}


std::string Project::run()
{
return "Hello World!";
}
} // namespace Hexagon


