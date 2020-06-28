

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


CreateRailsResourceLayout::CreateRailsResourceLayout(std::vector<StageInterface *>& stages, int display_default_height, int code_editor_width, std::string model_filename, std::string model_test_filename, std::string routes_filename, std::string controller_filename, std::string controller_test_filename, std::string view_filename)
   : ::Action("System::Action::CreateRailsResourceLayout.hpp", ActionData())
   , stages(stages)
   , display_default_height(display_default_height)
   , code_editor_width(code_editor_width)
   , model_filename(model_filename)
   , model_test_filename(model_test_filename)
   , routes_filename(routes_filename)
   , controller_filename(controller_filename)
   , controller_test_filename(controller_test_filename)
   , view_filename(view_filename)
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


bool CreateRailsResourceLayout::place_and_load_code_editor(std::vector<StageInterface *>* stages_ptr, std::string filename, float x, float y)
{
float code_editor_height = get_display_default_height();
{
   std::string file_contents = php::file_get_contents(filename);

   CodeEditor::CodeEditor *code_editor = new CodeEditor::CodeEditor(filename);
   code_editor->set_initial_content(file_contents);

   placement3d place(x * code_editor_width, y * code_editor_height, 0);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   code_editor->set_place(place);

   stages.push_back(code_editor);
}
return true;

}

bool CreateRailsResourceLayout::execute()
{
float code_editor_height = get_display_default_height();

place_and_load_code_editor(&stages, model_filename, 0, 0);
place_and_load_code_editor(&stages, model_test_filename, 1, 0);

place_and_load_code_editor(&stages, routes_filename, -1, -1);
//place_and_load_code_editor(&stages, view_filename, 0, -1); // should be plural
place_and_load_code_editor(&stages, controller_filename, 0, -1);
place_and_load_code_editor(&stages, controller_test_filename, 1, -1);

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


