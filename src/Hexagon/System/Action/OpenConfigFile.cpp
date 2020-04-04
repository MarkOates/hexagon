

#include <Hexagon/System/Action/OpenConfigFile.hpp>
#include <Hexagon/System/Action/AttemptToCraeteCodeEditorStageFromFilename.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


OpenConfigFile::OpenConfigFile()
   : ::Action("System::Action::OpenConfigFile", ActionData())
   , config(nullptr)
{
}


OpenConfigFile::~OpenConfigFile()
{
}


bool OpenConfigFile::execute()
{
Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action;
return action.execute();

}
} // namespace Action
} // namespace System
} // namespace Hexagon


