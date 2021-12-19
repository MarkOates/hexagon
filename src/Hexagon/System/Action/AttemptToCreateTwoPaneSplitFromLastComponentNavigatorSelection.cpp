

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


AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection(std::string project_path, std::string last_component_navigator_selection, int display_default_width, int display_default_height, std::vector<StageInterface *>& stages, Hexagon::StageFactory* stage_factory, int code_editor_width, int code_editor_height, ALLEGRO_COLOR text_color, ALLEGRO_COLOR backfill_color)
   : ::Action("System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection", ActionData())
   , project_path(project_path)
   , last_component_navigator_selection(last_component_navigator_selection)
   , display_default_width(display_default_width)
   , display_default_height(display_default_height)
   , stages(stages)
   , stage_factory(stage_factory)
   , code_editor_width(code_editor_width)
   , code_editor_height(code_editor_height)
   , text_color(text_color)
   , backfill_color(backfill_color)
   , create_as_advanced_code_editor(false)
{
}


AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::~AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection()
{
}


void AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::set_stages(std::vector<StageInterface *>& stages)
{
   this->stages = stages;
}


void AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::set_create_as_advanced_code_editor(bool create_as_advanced_code_editor)
{
   this->create_as_advanced_code_editor = create_as_advanced_code_editor;
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


int AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::get_code_editor_height()
{
   return code_editor_height;
}


bool AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::get_create_as_advanced_code_editor()
{
   return create_as_advanced_code_editor;
}


std::vector<StageInterface *> &AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection::get_dummy_stages_ref()
{
   return dummy_stages;
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
   float height = get_code_editor_height(); //display_default_width/2 * width_scale_of_halfwidth;

   //if (!test_file_contents.empty())
   {
     placement3d place(0, 0, 0);
     place.size = vec3d(width, height, 0.0);
     place.align = vec3d(0.0, 0.5, 0.0);
     place.scale = vec3d(1.0, 1.0, 0.0);

     StageInterface *stage = nullptr;

     if (test_file_present)
     {
        std::vector<std::string> file_contents = {};
        ::read_file(file_contents, test_filename);

        if (get_create_as_advanced_code_editor())
        {
           stage = stage_factory->create_advanced_code_editor(test_filename);
        }
        else
        {
           stage = stage_factory->create_code_editor(test_filename, "blast_test");
           static_cast<CodeEditor::Stage *>(stage)->get_code_editor_ref().set_initial_content(file_contents);
                                                                       // ^^ feels a tad hacky
                                                                       // not sure code should be filled here
           static_cast<CodeEditor::Stage *>(stage)->set_base_font_color(text_color);
           static_cast<CodeEditor::Stage *>(stage)->set_backfill_color(backfill_color);
           //file_stage->set_base_font_color(text_color);
           //file_stage->set_backfill_color(backfill_color);
        }
     }
     else
     {
         stage = stage_factory->create_missing_file(test_filename);
     }

     stage->set_place(place);
     stages.push_back(stage);
   }

   //if (!file_contents.empty())
   {
     placement3d place(0, 0, 0);
     place.size = vec3d(width, height, 0.0);
     place.align = vec3d(1.0, 0.5, 0.0);
     place.scale = vec3d(1.0, 1.0, 0.0);

     StageInterface *stage = nullptr;

     if (quintessence_file_present)
     {
        std::vector<std::string> file_contents = {};
        ::read_file(file_contents, filename);

        if (get_create_as_advanced_code_editor())
        {
           stage = stage_factory->create_advanced_code_editor(filename);
        }
        else
        {
           stage = stage_factory->create_code_editor(filename, "blast_quintessence");

           static_cast<CodeEditor::Stage *>(stage)->get_code_editor_ref().set_initial_content(file_contents);
           static_cast<CodeEditor::Stage *>(stage)->set_base_font_color(text_color);
           static_cast<CodeEditor::Stage *>(stage)->set_backfill_color(backfill_color);
        }
     }
     else
     {
         stage = stage_factory->create_missing_file(filename);
     }

     stage->set_place(place);
     stages.push_back(stage);
   }

   return true;
}
} // namespace Action
} // namespace System
} // namespace Hexagon


