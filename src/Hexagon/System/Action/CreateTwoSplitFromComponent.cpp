

#include <Hexagon/System/Action/CreateTwoSplitFromComponent.hpp>

#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/util.hpp>
#include <NcursesArt/ProjectFilenameGenerator.hpp>
#include <allegro_flare/placement3d.h>
#include <sstream>
#include <string>
#include <vector>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> CreateTwoSplitFromComponent::dummy_stages = {};


CreateTwoSplitFromComponent::CreateTwoSplitFromComponent(std::string project_path, std::string component_name, int display_default_width, int display_default_height, std::vector<StageInterface *>& stages, Hexagon::StageFactory* stage_factory, int code_editor_width, int code_editor_height, ALLEGRO_COLOR text_color, ALLEGRO_COLOR backfill_color)
   : ::Action("System::Action::CreateTwoSplitFromComponent", ActionData())
   , project_path(project_path)
   , component_name(component_name)
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


CreateTwoSplitFromComponent::~CreateTwoSplitFromComponent()
{
}


void CreateTwoSplitFromComponent::set_stages(std::vector<StageInterface *>& stages)
{
   this->stages = stages;
}


void CreateTwoSplitFromComponent::set_create_as_advanced_code_editor(bool create_as_advanced_code_editor)
{
   this->create_as_advanced_code_editor = create_as_advanced_code_editor;
}


std::string CreateTwoSplitFromComponent::get_project_path() const
{
   return project_path;
}


std::vector<StageInterface *>& CreateTwoSplitFromComponent::get_stages() const
{
   return stages;
}


int CreateTwoSplitFromComponent::get_code_editor_width() const
{
   return code_editor_width;
}


int CreateTwoSplitFromComponent::get_code_editor_height() const
{
   return code_editor_height;
}


bool CreateTwoSplitFromComponent::get_create_as_advanced_code_editor() const
{
   return create_as_advanced_code_editor;
}


std::vector<StageInterface *> &CreateTwoSplitFromComponent::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool CreateTwoSplitFromComponent::execute()
{
   //std::string component_name = last_component_navigator_selection;

   NcursesArt::ProjectFilenameGenerator project_component_filename_generator(component_name, false);
   std::string quintessence_filename = project_path
      + project_component_filename_generator.generate_quintessence_filename();
   std::string test_filename = project_path + project_component_filename_generator.generate_test_src_filename();

   std::vector<std::string> missing_files = {};

   bool quintessence_file_present = true;
   bool test_file_present = true;
   if (!Blast::FileExistenceChecker(quintessence_filename).exists()) quintessence_file_present = false;
   if (!Blast::FileExistenceChecker(test_filename).exists()) test_file_present = false;

   float width_scale_of_halfwidth = 1.0; //0.6180339;
   float width = get_code_editor_width(); //display_default_width/2 * width_scale_of_halfwidth;
   float height = get_code_editor_height(); //display_default_width/2 * width_scale_of_halfwidth;

   bool using_fuller_fit_stages_for_smaller_display = false;
   //if (!test_file_contents.empty())
   {
     placement3d place(0, 0, 0);
     place.size = vec3d(width, height, 0.0);

     if (using_fuller_fit_stages_for_smaller_display)
     {
        place.position.x = width/2;
        place.align = vec3d(0.35, 0.5, 0.0);
        place.scale = vec3d(1.35, 1.35, 0.0);
     }
     else
     {
        place.align = vec3d(0.0, 0.5, 0.0);
        place.scale = vec3d(1.0, 1.0, 0.0);
     }

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

     if (using_fuller_fit_stages_for_smaller_display)
     {
        place.position.x = -width/2;
        place.size = vec3d(width, height, 0.0);
        place.align = vec3d(0.65, 0.5, 0.0);
        place.scale = vec3d(1.35, 1.35, 0.0);
     }
     else
     {
        place.align = vec3d(1.0, 0.5, 0.0);
        place.scale = vec3d(1.0, 1.0, 0.0);
     }

     StageInterface *stage = nullptr;

     if (quintessence_file_present)
     {
        std::vector<std::string> file_contents = {};
        ::read_file(file_contents, quintessence_filename);

        if (get_create_as_advanced_code_editor())
        {
           stage = stage_factory->create_advanced_code_editor(quintessence_filename);
        }
        else
        {
           stage = stage_factory->create_code_editor(quintessence_filename, "blast_quintessence");

           static_cast<CodeEditor::Stage *>(stage)->get_code_editor_ref().set_initial_content(file_contents);
           static_cast<CodeEditor::Stage *>(stage)->set_base_font_color(text_color);
           static_cast<CodeEditor::Stage *>(stage)->set_backfill_color(backfill_color);
        }
     }
     else
     {
         stage = stage_factory->create_missing_file(quintessence_filename);
     }

     stage->set_place(place);
     stages.push_back(stage);
   }

   return true;
}


} // namespace Action
} // namespace System
} // namespace Hexagon


