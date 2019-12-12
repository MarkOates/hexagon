

#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <NcursesArt/ProjectFilenameGenerator.hpp>
#include <sstream>
#include <vector>
#include <string>
#include <Hexagon/util.hpp>
#include <allegro_flare/placement3d.h>
#include <Hexagon/CodeEditor/Stage.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::dummy_stages = {};


AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection(std::string project_path, std::string last_component_navigator_selection, int display_default_width, int display_default_height, std::vector<StageInterface *>& stages)
   : ::Action("System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection", ActionData())
   , project_path(project_path)
   , last_component_navigator_selection(last_component_navigator_selection)
   , display_default_width(display_default_width)
   , display_default_height(display_default_height)
   , stages(stages)
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
std::string quintessence_filename = project_path + project_component_filename_generator.generate_quintessence_filename();
std::string test_src_filename = project_path + project_component_filename_generator.generate_test_src_filename();

std::string filename = quintessence_filename;
std::string test_filename = test_src_filename;

std::vector<std::string> missing_files = {};

if (!Blast::FileExistenceChecker(filename).exists()) missing_files.push_back(filename);
if (!Blast::FileExistenceChecker(test_filename).exists()) missing_files.push_back(test_filename);

//if (!missing_files.empty())
//{
   //std::stringstream error_message;
   //error_message << "The following files are missing and cannot be opened: [";
   //for (auto &missing_file : missing_files)
   //{
      //error_message << "\"" << missing_file << "\"";
   //}
   //error_message << "]";
   //throw std::runtime_error(error_message.str());
//}

std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;

std::vector<std::string> file_contents = {};
::read_file(file_contents, filename);

std::vector<std::string> test_file_contents = {};
::read_file(test_file_contents, test_filename);

float width_scale_of_halfwidth = 1.0; //0.6180339;

if (!test_file_contents.empty())
{
  float width = display_default_width/2 * width_scale_of_halfwidth;
  float horizontal_position = 0;

  placement3d place(horizontal_position, 0, 0);
  place.size = vec3d(width, display_default_height, 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
  place.align = vec3d(0.0, 0.5, 0.0);
  place.scale = vec3d(0.9, 0.9, 0.0);

  CodeEditor::Stage *test_file_stage = new CodeEditor::Stage(test_filename);

  test_file_stage->set_place(place);
  test_file_stage->set_initial_content(test_file_contents);
  stages.push_back(test_file_stage);
}

if (!file_contents.empty())
{
  float width = display_default_width/2 * width_scale_of_halfwidth;
  float horizontal_position = 0;

  placement3d place(horizontal_position, 0, 0);
  place.size = vec3d(width, display_default_height, 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
  place.align = vec3d(1.0, 0.5, 0.0);
  place.scale = vec3d(0.9, 0.9, 0.0);

  CodeEditor::Stage *quintessence_file_stage = new CodeEditor::Stage(filename);

  quintessence_file_stage->set_place(place);
  quintessence_file_stage->set_initial_content(file_contents);
  stages.push_back(quintessence_file_stage);
}

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


