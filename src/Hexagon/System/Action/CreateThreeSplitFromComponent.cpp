

#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> CreateThreeSplitFromComponent::dummy_stages = {};


CreateThreeSplitFromComponent::CreateThreeSplitFromComponent(std::vector<StageInterface *>& stages, int display_default_width, int display_default_height)
   : ::Action("System::Action::CreateThreeSplitFromComponent", ActionData())
   , component()
   , stages(stages)
   , display_default_width(display_default_width)
   , display_default_height(display_default_height)
{
}


CreateThreeSplitFromComponent::~CreateThreeSplitFromComponent()
{
}


void CreateThreeSplitFromComponent::set_stages(std::vector<StageInterface *>& stages)
{
   this->stages = stages;
}


std::vector<StageInterface *>& CreateThreeSplitFromComponent::get_stages()
{
   return stages;
}


std::vector<StageInterface *> &CreateThreeSplitFromComponent::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool CreateThreeSplitFromComponent::place_stage(std::string filename, std::string file_contents, placement3d place)
{
CodeEditor::Stage *file_stage = new CodeEditor::Stage(filename);
file_stage->set_place(place);
file_stage->set_content(file_contents);
stages.push_back(file_stage);

return true;

}

bool CreateThreeSplitFromComponent::execute()
{
float left_anchor = -display_default_width / 3;
float right_anchor = display_default_width / 3;

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


