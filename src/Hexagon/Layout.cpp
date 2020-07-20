

#include <Hexagon/Layout.hpp>
#include <allegro_flare/useful_php.h>
#include <Hexagon/CodeEditor/Stage.hpp>


namespace Hexagon
{


std::vector<StageInterface *> Layout::dummy_stages = {};


Layout::Layout(std::string project_root, std::vector<std::tuple<std::string, float, float>> file, std::string daemus_command, int display_default_height, int code_editor_width, std::vector<StageInterface *>& stages)
   : project_root(project_root)
   , file(file)
   , daemus_command(daemus_command)
   , display_default_height(display_default_height)
   , code_editor_width(code_editor_width)
   , stages(stages)
{
}


Layout::~Layout()
{
}


void Layout::set_file(std::vector<std::tuple<std::string, float, float>> file)
{
   this->file = file;
}


void Layout::set_stages(std::vector<StageInterface *>& stages)
{
   this->stages = stages;
}


std::string Layout::get_project_root()
{
   return project_root;
}


std::vector<std::tuple<std::string, float, float>> Layout::get_file()
{
   return file;
}


std::string Layout::get_daemus_command()
{
   return daemus_command;
}


int Layout::get_display_default_height()
{
   return display_default_height;
}


int Layout::get_code_editor_width()
{
   return code_editor_width;
}


std::vector<StageInterface *>& Layout::get_stages()
{
   return stages;
}


std::vector<StageInterface *> &Layout::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool Layout::place_and_load_code_editor(std::vector<StageInterface *>* stages_ptr, std::string filename, std::string file_category, float x, float y)
{
float code_editor_height = get_display_default_height();
{
   std::string file_contents = php::file_get_contents(filename);

   Hexagon::CodeEditor::Stage *stage = new Hexagon::CodeEditor::Stage({filename, file_category});
   stage->get_code_editor_ref().set_initial_content(file_contents);

   placement3d place(x * code_editor_width, y * code_editor_height, 0);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   stage->set_place(place);

   stages.push_back(stage);
}
return true;

}
} // namespace Hexagon


