

#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>
#include <allegro_flare/placement3d.h>
#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <allegro_flare/useful_php.h>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> CreateThreeSplitFromComponent::dummy_stages = {};


CreateThreeSplitFromComponent::CreateThreeSplitFromComponent(std::string project_path, Blast::Project::Component component, std::vector<StageInterface *>& stages, int display_default_width, int display_default_height, int code_editor_width)
   : ::Action("System::Action::CreateThreeSplitFromComponent", ActionData())
   , project_path(project_path)
   , component(component)
   , stages(stages)
   , display_default_width(display_default_width)
   , display_default_height(display_default_height)
   , code_editor_width(code_editor_width)
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


int CreateThreeSplitFromComponent::get_code_editor_width()
{
   return code_editor_width;
}


std::vector<StageInterface *> &CreateThreeSplitFromComponent::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool CreateThreeSplitFromComponent::place_stage(std::string filename, std::string file_category, float x, float align_x)
{
bool file_exists = Blast::FileExistenceChecker(filename).exists();
float width = get_code_editor_width();
placement3d place(x, 0, 0);
place.size = vec3d(width, display_default_height, 0.0);
place.align = vec3d(align_x, 0.5, 0.0);
place.scale = vec3d(1.0, 1.0, 0.0);

StageInterface *stage = nullptr;

if (file_exists)
{
   std::string file_contents = php::file_get_contents(filename);
   CodeEditor::CodeEditor *file_stage = new CodeEditor::CodeEditor(filename, file_category);
   file_stage->set_initial_content(file_contents);
   stage = file_stage;
}
else
{
   stage = new Hexagon::MissingFile::Stage(filename);
}

stage->set_place(place);
stages.push_back(stage);

return true;

}

std::string CreateThreeSplitFromComponent::generate_header_filename()
{
Blast::ProjectComponentFilenameGenerator filename_generator(
        component.get_name(),
        Blast::ProjectComponentFileTypes::HEADER_FILE);
return project_path + filename_generator.generate_filename();

}

std::string CreateThreeSplitFromComponent::generate_source_filename()
{
auto generator = Blast::ProjectComponentFilenameGenerator(
   component.get_name(),
   Blast::ProjectComponentFileTypes::SOURCE_FILE
);
return project_path + generator.generate_filename();

}

std::string CreateThreeSplitFromComponent::generate_test_filename()
{
auto generator = Blast::ProjectComponentFilenameGenerator(
   component.get_name(),
   Blast::ProjectComponentFileTypes::TEST_FILE
);
return project_path + generator.generate_filename();

}

bool CreateThreeSplitFromComponent::execute()
{
float left_anchor = -get_code_editor_width();
float right_anchor = get_code_editor_width();

std::string test_filename = generate_test_filename();
std::string header_filename = generate_header_filename();
std::string source_filename = generate_source_filename();

place_stage(header_filename, "cpp_header", left_anchor, 0.5);
place_stage(source_filename, "cpp_source", 0, 0.5);
place_stage(test_filename, "blast_test", right_anchor, 0.5);

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


