

#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>
#include <allegro_flare/placement3d.h>
#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <allegro_flare/useful_php.h>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> CreateThreeSplitFromComponent::dummy_stages = {};


CreateThreeSplitFromComponent::CreateThreeSplitFromComponent(std::string project_path, Blast::Project::Component component, std::vector<StageInterface *>& stages, Hexagon::StageFactory* stage_factory, int display_default_width, int display_default_height, int code_editor_width, ALLEGRO_COLOR text_color, ALLEGRO_COLOR backfill_color)
   : ::Action("System::Action::CreateThreeSplitFromComponent", ActionData())
   , project_path(project_path)
   , component(component)
   , stages(stages)
   , stage_factory(stage_factory)
   , display_default_width(display_default_width)
   , display_default_height(display_default_height)
   , code_editor_width(code_editor_width)
   , text_color(text_color)
   , backfill_color(backfill_color)
   , create_as_advanced_code_editor(false)
{
}


CreateThreeSplitFromComponent::~CreateThreeSplitFromComponent()
{
}


void CreateThreeSplitFromComponent::set_stages(std::vector<StageInterface *>& stages)
{
   this->stages = stages;
}


void CreateThreeSplitFromComponent::set_create_as_advanced_code_editor(bool create_as_advanced_code_editor)
{
   this->create_as_advanced_code_editor = create_as_advanced_code_editor;
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


bool CreateThreeSplitFromComponent::get_create_as_advanced_code_editor()
{
   return create_as_advanced_code_editor;
}


std::vector<StageInterface *> &CreateThreeSplitFromComponent::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool CreateThreeSplitFromComponent::place_stage(std::string filename, std::string file_category, float x, float align_x)
{
if (!(stage_factory))
   {
      std::stringstream error_message;
      error_message << "CreateThreeSplitFromComponent" << "::" << "place_stage" << ": error: " << "guard \"stage_factory\" not met";
      throw std::runtime_error(error_message.str());
   }
bool file_exists = Blast::FileExistenceChecker(filename).exists();
float width = get_code_editor_width();
placement3d place(x, 0, 0);
place.size = vec3d(width, display_default_height, 0.0);
place.align = vec3d(align_x, 0.5, 0.0);
place.scale = vec3d(1.0, 1.0, 0.0);

StageInterface *stage = nullptr;

if (file_exists)
{
   if (create_as_advanced_code_editor)
   {
      StageInterface* created_stage = stage_factory->create_advanced_code_editor(filename);
      Hexagon::AdvancedCodeEditor::Stage *advanced_code_editor_stage =
         static_cast<Hexagon::AdvancedCodeEditor::Stage*>(created_stage);
      stage = advanced_code_editor_stage;
   }
   else
   {
      std::string file_contents = php::file_get_contents(filename);
      Hexagon::CodeEditor::Stage *file_stage =
         static_cast<Hexagon::CodeEditor::Stage*>(stage_factory->create_code_editor(filename, file_category));
      file_stage->get_code_editor_ref().set_initial_content(file_contents);
      file_stage->set_base_font_color(text_color);
      file_stage->set_backfill_color(backfill_color);
      stage = file_stage;
   }
}
else
{
   stage = stage_factory->create_missing_file(filename);
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


