

#include <Hexagon/System/Action/CreateRailsResourceLayout.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> CreateRailsResourceLayout::dummy_stages = {};


CreateRailsResourceLayout::CreateRailsResourceLayout(std::vector<StageInterface *>& stages)
   : ::Action("System::Action::CreateRailsResourceLayout.hpp", ActionData())
   , stages(stages)
{
}


CreateRailsResourceLayout::~CreateRailsResourceLayout()
{
}


void CreateRailsResourceLayout::set_stages(std::vector<StageInterface *>& stages)
{
   this->stages = stages;
}


std::vector<StageInterface *>& CreateRailsResourceLayout::get_stages()
{
   return stages;
}


std::vector<StageInterface *> &CreateRailsResourceLayout::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool CreateRailsResourceLayout::execute()
{
CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor();
stages.push_back(model_code_editor);
return true;

}

std::string CreateRailsResourceLayout::run()
{
return "Hello World!";
}
} // namespace Action
} // namespace System
} // namespace Hexagon


