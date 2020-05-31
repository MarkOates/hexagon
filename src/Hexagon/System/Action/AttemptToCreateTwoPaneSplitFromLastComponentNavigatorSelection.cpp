

#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <NcursesArt/ProjectFilenameGenerator.hpp>
#include <sstream>
#include <vector>
#include <string>
#include <Hexagon/util.hpp>
#include <allegro_flare/placement3d.h>
#include <Hexagon/CodeEditor/CodeEditor.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::dummy_stages = {};


AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection(std::string project_path, std::string last_component_navigator_selection, int display_default_width, int display_default_height, std::vector<StageInterface *>& stages, int code_editor_width)
   : ::Action("System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection", ActionData())
   , project_path(project_path)
   , last_component_navigator_selection(last_component_navigator_selection)
   , display_default_width(display_default_width)
   , display_default_height(display_default_height)
   , stages(stages)
   , code_editor_width(code_editor_width)
{
}


AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::~AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection()
{
}


void AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::set_stages(std::vector<StageInterface *>& stages)
{
   this->stages = stages;
}


std::string AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::get_project_path()
{
   return project_path;
}


std::vector<StageInterface *>& AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::get_stages()
{
   return stages;
}


int AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::get_code_editor_width()
{
   return code_editor_width;
}


std::vector<StageInterface *> &AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::get_dummy_stages_ref()
{
   return dummy_stages;
}


std::string AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::run()
{
return "Hello World!";
}

bool AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::execute()
{
std::string component_name = last_component_navigator_selection;

NcursesArt::ProjectFilenameGenerator project_component_filename_generator(component_name, false);
std::string quintessence_filename = project_path
   + project_component_filename_generator.generate_quintessence_filename();
std::string test_src_filename = project_path + project_component_filename_generator.generate_test_src_filename();

std::string filename = quintessence_filename;
std::string test_filename = test_src_filename;

std::vector<std::string> missing_files = {};

bool quintessence_file_present = true;
bool test_file_present = true;
if (!Blast::FileExistenceChecker(filename).exists()) quintessence_file_present = false;
if (!Blast::FileExistenceChecker(test_filename).exists()) test_file_present = false;

float width_scale_of_halfwidth = 1.0; //0.6180339;
float width = get_code_editor_width(); //display_default_width/2 * width_scale_of_halfwidth;

//if (!test_file_contents.empty())
{
  placement3d place(0, 0, 0);
  place.size = vec3d(width, display_default_height, 0.0);
  place.align = vec3d(0.0, 0.5, 0.0);
  place.scale = vec3d(1.0, 1.0, 0.0);

  StageInterface *stage = nullptr;

  if (test_file_present)
  {
     std::vector<std::string> file_contents = {};
     ::read_file(file_contents, test_filename);
     stage = new CodeEditor::Stage(test_filename);
     static_cast<CodeEditor::Stage*>(stage)->set_initial_content(file_contents);
  }
  else
  {
      stage = new Hexagon::MissingFile::Stage(test_filename);
  }

  stage->set_place(place);
  stages.push_back(stage);
}

//if (!file_contents.empty())
{
  placement3d place(0, 0, 0);
  place.size = vec3d(width, display_default_height, 0.0);
  place.align = vec3d(1.0, 0.5, 0.0);
  place.scale = vec3d(1.0, 1.0, 0.0);

  StageInterface *stage = nullptr;

  if (quintessence_file_present)
  {
     std::vector<std::string> file_contents = {};
     ::read_file(file_contents, filename);
     stage = new CodeEditor::Stage(filename);
     static_cast<CodeEditor::Stage*>(stage)->set_initial_content(file_contents);
  }
  else
  {
      stage = new Hexagon::MissingFile::Stage(filename);
  }

  stage->set_place(place);
  stages.push_back(stage);
}

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


