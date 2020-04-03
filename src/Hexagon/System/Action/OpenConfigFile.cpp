

#include <Hexagon/System/Action/OpenConfigFile.hpp>



namespace Hexagon
{
namespace System
{
namespace Action
{


OpenConfigFile::OpenConfigFile()
   : ::Action("System::Action::OpenConfigFile", ActionData())
{
}


OpenConfigFile::~OpenConfigFile()
{
}


bool OpenConfigFile::execute()
{
return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


