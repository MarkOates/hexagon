

#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>
#include <NcursesArt/ProjectFilenameGenerator.hpp>
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


AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection(std::string last_component_navigator_selection, int display_default_width, int display_default_height, std::vector<StageInterface *>& stages)
   : ::Action("System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection", ActionData())
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
std::string quintessence_filename = std::string("/Users/markoates/Repos/hexagon/") + project_component_filename_generator.generate_quintessence_filename();
std::string test_src_filename = std::string("/Users/markoates/Repos/hexagon/") + project_component_filename_generator.generate_test_src_filename();


std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;
std::cout << "TEST_SRC" << test_src_filename << std::endl;

std::string filename = quintessence_filename;
std::string test_filename = test_src_filename;

std::vector<std::string> file_contents = {};
if (!::read_file(file_contents, filename)) throw std::runtime_error("Could not open the selected component quintessence file");

std::vector<std::string> test_file_contents = {};
if (!::read_file(test_file_contents, test_filename)) throw std::runtime_error("Could not open the selected component test file");

{
  float horizontal_position = -display_default_width/4;

  placement3d place(horizontal_position, 0, 0);
  place.size = vec3d(display_default_width/2, display_default_height, 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
  place.align = vec3d(0.5, 0.5, 0.0);
  place.scale = vec3d(0.9, 0.9, 0.0);

  CodeEditor::Stage *quintessence_file_stage = new CodeEditor::Stage(filename);

  quintessence_file_stage->set_place(place);
  quintessence_file_stage->set_content(file_contents);
  stages.push_back(quintessence_file_stage);
}

{
  float horizontal_position = display_default_width/4;

  placement3d place(horizontal_position, 0, 0);
  place.size = vec3d(display_default_width/2, display_default_height, 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
  place.align = vec3d(0.5, 0.5, 0.0);
  place.scale = vec3d(0.9, 0.9, 0.0);

  CodeEditor::Stage *test_file_stage = new CodeEditor::Stage(test_filename);

  test_file_stage->set_place(place);
  test_file_stage->set_content(test_file_contents);
  stages.push_back(test_file_stage);
}

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


