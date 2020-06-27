

#include <Hexagon/System/Action/CreateRailsResourceLayout.hpp>



namespace Hexagon
{
namespace System
{
namespace Action
{


CreateRailsResourceLayout::CreateRailsResourceLayout()
   : ::Action("System::Action::CreateRailsResourceLayout.hpp", ActionData())
{
}


CreateRailsResourceLayout::~CreateRailsResourceLayout()
{
}


bool CreateRailsResourceLayout::execute()
{
return true;

}

std::string CreateRailsResourceLayout::run()
{
return "Hello World!";
}
} // namespace Action
} // namespace System
} // namespace Hexagon


