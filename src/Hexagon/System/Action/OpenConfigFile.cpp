

#include <Hexagon/System/Action/OpenConfigFile.hpp>
#include <Hexagon/System/Action/AttemptToCraeteCodeEditorStageFromFilename.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


OpenConfigFile::OpenConfigFile(std::string config_filename)
   : ::Action("System::Action::OpenConfigFile", ActionData())
   , config_filename(config_filename)
{
}


OpenConfigFile::~OpenConfigFile()
{
}


std::string OpenConfigFile::get_config_filename()
{
   return config_filename;
}


bool OpenConfigFile::execute()
{
Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action(config_filename);
return action.execute();

}
} // namespace Action
} // namespace System
} // namespace Hexagon


