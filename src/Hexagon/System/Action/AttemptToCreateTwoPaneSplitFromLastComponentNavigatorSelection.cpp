

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

NcursesArt::ProjectFilenameGenerator project_component_filename_generator(component_name);
std::string quintessence_filename = std::string("/Users/markoates/Repos/hexagon/") + project_component_filename_generator.generate_quintessence_filename();
std::string test_src_filename = std::string("/Users/markoates/Repos/hexagon/") + project_component_filename_generator.generate_test_src_filename();

std::string filename = quintessence_filename;
std::string test_filename = test_src_filename;

std::vector<std::string> file_contents = {};
if (!::read_file(file_contents, filename)) throw std::runtime_error("Could not open the selected file");

float one_third_screen_width = display_default_width / 3;
int number_of_files = 0;

placement3d place(one_third_screen_width*number_of_files, 0, 0);
place.size = vec3d(display_default_width/2, display_default_height, 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
place.align = vec3d(0.5, 0.5, 0.0);
place.scale = vec3d(0.9, 0.9, 0.0);

CodeEditor::Stage *quintessence_file_stage = new CodeEditor::Stage(filename);

quintessence_file_stage->set_place(place);
quintessence_file_stage->set_content(file_contents);
stages.push_back(quintessence_file_stage);

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


