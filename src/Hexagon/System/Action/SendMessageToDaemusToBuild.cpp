

#include <Hexagon/System/Action/SendMessageToDaemusToBuild.hpp>



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
   return true;
}
} // namespace Action
} // namespace System
} // namespace Hexagon


