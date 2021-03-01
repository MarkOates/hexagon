

#include <Hexagon/System/Action/SendMessageToDaemusToBuild.hpp>
#include <string>


namespace Hexagon
{
namespace System
{
namespace Action
{


SendMessageToDaemusToBuild::SendMessageToDaemusToBuild()
   : ::Action("Hexagon::System::Action::SendMessageToDaemusToBuild", ActionData())
{
}


SendMessageToDaemusToBuild::~SendMessageToDaemusToBuild()
{
}


bool SendMessageToDaemusToBuild::execute()
{
   std::string file_name = "/Users/markoates/Repos/hexagon/tmp/daemus/build.txt";
   return true;
}
} // namespace Action
} // namespace System
} // namespace Hexagon


