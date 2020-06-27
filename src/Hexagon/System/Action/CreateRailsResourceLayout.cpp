

#include <Hexagon/System/Action/CreateRailsResourceLayout.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <allegro_flare/useful_php.h>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> CreateRailsResourceLayout::dummy_stages = {};


CreateRailsResourceLayout::CreateRailsResourceLayout(std::vector<StageInterface *>& stages, int display_default_height, int code_editor_width)
   : ::Action("System::Action::CreateRailsResourceLayout.hpp", ActionData())
   , stages(stages)
   , display_default_height(display_default_height)
   , code_editor_width(code_editor_width)
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


int CreateRailsResourceLayout::get_display_default_height()
{
   return display_default_height;
}


int CreateRailsResourceLayout::get_code_editor_width()
{
   return code_editor_width;
}


std::vector<StageInterface *> &CreateRailsResourceLayout::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool CreateRailsResourceLayout::execute()
{
std::string base_directory = "/Users/markoates/Repos/disclife/";

std::string model_filename = base_directory + "app/models/disc.rb";
std::string model_test_filename = base_directory + "test/models/disc_test.rb";
std::string routes_filename = base_directory + "config/routes.rb";
std::string controller_filename = base_directory + "app/controllers/discs_controller.rb";
std::string controller_test_filename = base_directory + "test/controllers/discs_controller_test.rb";
std::string view_filename = base_directory + "app/views/discs/index.html.erb";

float code_editor_height = get_display_default_height();

// model
{
   std::string file_contents = php::file_get_contents(model_filename);

   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(model_filename);
   model_code_editor->set_initial_content(file_contents);

   placement3d place(0, 0, 0);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
}
// model test
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(model_test_filename);

   placement3d place(code_editor_width, 0, 0);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
}
// routes
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(routes_filename);

   placement3d place(-code_editor_width, -code_editor_height, 0);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
 }
// controller
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(controller_filename);

   placement3d place(0, -code_editor_height, 0);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
 }
// controller test
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(controller_test_filename);

   placement3d place(code_editor_width, -code_editor_height, 0);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
 }
// view
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(view_filename);

   placement3d place(0, -code_editor_height, 100);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
 }
 return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


