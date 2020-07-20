

#include <Hexagon/Layout.hpp>
#include <allegro_flare/useful_php.h>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


Layout::Layout(std::string project_root, std::vector<StageInterface *>* stages, std::vector<std::tuple<std::string, std::string, float, float>> files, std::string daemus_command, int code_editor_height, int code_editor_width)
   : project_root(project_root)
   , stages(stages)
   , files(files)
   , daemus_command(daemus_command)
   , code_editor_height(code_editor_height)
   , code_editor_width(code_editor_width)
{
}


Layout::~Layout()
{
}


void Layout::set_stages(std::vector<StageInterface *>* stages)
{
   this->stages = stages;
}


void Layout::set_files(std::vector<std::tuple<std::string, std::string, float, float>> files)
{
   this->files = files;
}


std::string Layout::get_project_root()
{
   return project_root;
}


std::vector<StageInterface *>* Layout::get_stages()
{
   return stages;
}


std::vector<std::tuple<std::string, std::string, float, float>> Layout::get_files()
{
   return files;
}


std::string Layout::get_daemus_command()
{
   return daemus_command;
}


int Layout::get_code_editor_height()
{
   return code_editor_height;
}


int Layout::get_code_editor_width()
{
   return code_editor_width;
}


bool Layout::place_and_load_code_editor(std::vector<StageInterface *>* stages_ptr, std::string filename, std::string file_category, float x, float y)
{
if (!(stages))
   {
      std::stringstream error_message;
      error_message << "Layout" << "::" << "place_and_load_code_editor" << ": error: " << "guard \"stages\" not met";
      throw std::runtime_error(error_message.str());
   }
//float code_editor_height = get_display_default_height();
{
   std::string file_contents = php::file_get_contents(filename);

   Hexagon::CodeEditor::Stage *stage = new Hexagon::CodeEditor::Stage({filename, file_category});
   stage->get_code_editor_ref().set_initial_content(file_contents);

   placement3d place(x * code_editor_width, y * code_editor_height, 0);
   place.size = vec3d(code_editor_width, code_editor_height, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   stage->set_place(place);

   stages->push_back(stage);
}
return true;

}

void Layout::create()
{
for (auto &file : files)
{
   std::string filename = std::get<0>(file);
   std::string file_type = std::get<1>(file);
   float x = std::get<2>(file);
   float y = std::get<3>(file);

   place_and_load_code_editor(stages, filename, file_type, x, y);
}
return;

}
} // namespace Hexagon


