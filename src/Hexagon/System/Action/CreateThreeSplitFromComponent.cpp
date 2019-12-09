

#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>
#include <allegro_flare/placement3d.h>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <allegro_flare/useful_php.h>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> CreateThreeSplitFromComponent::dummy_stages = {};


CreateThreeSplitFromComponent::CreateThreeSplitFromComponent(std::string project_path, Blast::Project::Component component, std::vector<StageInterface *>& stages, int display_default_width, int display_default_height)
   : ::Action("System::Action::CreateThreeSplitFromComponent", ActionData())
   , project_path(project_path)
   , component(component)
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


std::string CreateThreeSplitFromComponent::get_project_path()
{
   return project_path;
}


std::vector<StageInterface *>& CreateThreeSplitFromComponent::get_stages()
{
   return stages;
}


std::vector<StageInterface *> &CreateThreeSplitFromComponent::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool CreateThreeSplitFromComponent::place_stage(std::string filename, std::string file_contents, float x, float align_x)
{
if (file_contents.empty()) return false;

CodeEditor::Stage *file_stage = new CodeEditor::Stage(filename);

float width = display_default_width/3;

placement3d place(x, 0, 0);
place.size = vec3d(width, display_default_height, 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
place.align = vec3d(align_x, 0.5, 0.0);
place.scale = vec3d(0.9, 0.9, 0.0);

file_stage->set_place(place);
file_stage->set_initial_content(file_contents);
stages.push_back(file_stage);

return true;

}

std::string CreateThreeSplitFromComponent::generate_header_filename()
{
return project_path + Blast::ProjectComponentFilenameGenerator(component.get_name(), Blast::ProjectComponentFileTypes::HEADER_FILE).generate_filename();

}

std::string CreateThreeSplitFromComponent::generate_source_filename()
{
return project_path + Blast::ProjectComponentFilenameGenerator(component.get_name(), Blast::ProjectComponentFileTypes::SOURCE_FILE).generate_filename();

}

std::string CreateThreeSplitFromComponent::generate_test_filename()
{
return project_path + Blast::ProjectComponentFilenameGenerator(component.get_name(), Blast::ProjectComponentFileTypes::TEST_FILE).generate_filename();

}

bool CreateThreeSplitFromComponent::execute()
{
float left_anchor = -display_default_width / 3 / 2;
float right_anchor = display_default_width / 3 / 2;

std::string test_filename = generate_test_filename();
std::string header_filename = generate_header_filename();
std::string source_filename = generate_source_filename();

std::string header_file_contents = php::file_get_contents(generate_header_filename());
std::string source_file_contents = php::file_get_contents(generate_source_filename());
std::string test_file_contents = php::file_get_contents(generate_test_filename());

place_stage(test_filename, test_file_contents, right_anchor, 0.0);
place_stage(source_filename, source_file_contents, 0.5, 0.5);
place_stage(header_filename, header_file_contents, left_anchor, 1.0);

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


