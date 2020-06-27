

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
std::string model_filename = "app/models/truck.rb";
std::string model_test_filename = "test/models/truck_test.rb";
std::string routes_filename = "config/routes.rb";
std::string controller_filename = "app/controllers/trucks_controller.rb";
std::string controller_test_filename = "test/controllers/trucks_controller_test.rb";
std::string view_filename = "app/views/trucks/index.html.erb";
// model
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(model_filename);

   placement3d place(0, 0, 0);
   place.size = vec3d(400, 650, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
}
// model test
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(model_test_filename);

   placement3d place(100, 0, 0);
   place.size = vec3d(400, 650, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
}
// routes
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(routes_filename);

   placement3d place(-100, -100, 0);
   place.size = vec3d(400, 650, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
 }
// controller
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(controller_filename);

   placement3d place(0, -100, 0);
   place.size = vec3d(400, 650, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
 }
// controller test
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(controller_test_filename);

   placement3d place(100, -100, 0);
   place.size = vec3d(400, 650, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
 }
// view
{
   CodeEditor::CodeEditor *model_code_editor = new CodeEditor::CodeEditor(view_filename);

   placement3d place(0, -100, 100);
   place.size = vec3d(400, 650, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   model_code_editor->set_place(place);

   stages.push_back(model_code_editor);
 }
 return true;

}

std::string CreateRailsResourceLayout::run()
{
return "Hello World!";
}
} // namespace Action
} // namespace System
} // namespace Hexagon


