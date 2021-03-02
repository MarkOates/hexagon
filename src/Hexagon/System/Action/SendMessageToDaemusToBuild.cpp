

#include <Hexagon/System/Action/SendMessageToDaemusToBuild.hpp>
#include <string>
#include <Blast/FileCreator.hpp>


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
   std::string filename = "/Users/markoates/Repos/hexagon/tmp/daemus/build.txt";
   Blast::FileCreator file_creator(filename, "# some random irrelevant text");
   file_creator.create_or_overwrite();
   return true;
}
} // namespace Action
} // namespace System
} // namespace Hexagon


