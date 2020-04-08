


#include <Hexagon/System/System.hpp>


#include <Hexagon/RailsMinitestTestResult.hpp>
#include <Hexagon/RailsMinitestTestResultToCodeMessagePointConverter.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/ComponentNavigator/Stage.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/FullScreenOverlay/Stage.hpp>
#include <Hexagon/RerunOutputWatcher/Stage.hpp>
#include <allegro5/allegro.h>
#include <Hexagon/shared_globals.hpp>




#include <iostream>
#include <sstream>
#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement2d.h>
#include <allegro_flare/placement3d.h>
#include <allegro_flare/useful_php.h>
#include <allegro_flare/render_cache.h>
#include <Blast/Project/ComponentRelativeLister.hpp>
#include <Blast/StringSplitter.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>
#include <lib/camera.h>
#include <AllegroFlare/Config.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/System/Action/DestroyAllCodeEditorStages.hpp>
#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>
#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>
#include <Hexagon/System/Action/AttemptToCraeteCodeEditorStageFromFilename.hpp>
#include <Hexagon/System/Action/OpenConfigFile.hpp>
#include <Hexagon/Logo.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/shared_globals.hpp>
#include <Hexagon/util.hpp>
#include <Hexagon/ClipboardData.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/Action.hpp>
#include <Hexagon/ActionQueueRecording.hpp>
#include <Hexagon/CodePoint.hpp>
#include <Hexagon/CodeRange.hpp>
#include <Hexagon/RailsMinitestTestResult.hpp>
#include <Hexagon/RailsTestOutputParser.hpp>
#include <Hexagon/RailsMinitestTestRunner.hpp>
#include <Hexagon/CppCompiler/CompileRunner.hpp>
#include <Hexagon/FullScreenOverlay/Stage.hpp>
#include <Hexagon/CodeRangeExtractor.hpp>
#include <Hexagon/CodeMessagePoint.hpp>
#include <Hexagon/CodeMessagePointsOverlay.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/KeyboardInputsModal/Stage.hpp>
#include <Hexagon/EventControllerInterface.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/Hud.hpp>
#include <Hexagon/FileSystemNode.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/ComponentNavigator/Stage.hpp>
#include <Hexagon/RerunOutputWatcher/Stage.hpp>
#include <Hexagon/LayoutPlacements.hpp>
#include <NcursesArt/ProjectComponentBasenameExtractor.hpp>
#include <NcursesArt/ProjectFilenameGenerator.hpp>



static const std::string sonnet = R"END(Is it thy will thy image should keep open
My heavy eyelids to the weary night?
Dost thou desire my slumbers should be broken,
While shadows like to thee do mock my sight?
Is it thy spirit that thou send'st from thee
So far from home into my deeds to pry,
To find out shames and idle hours in me,
The scope and tenor of thy jealousy?
O, no! thy love, though much, is not so great:
It is my love that keeps mine eye awake;
Mine own true love that doth my rest defeat,
To play the watchman ever for thy sake:
For thee watch I whilst thou dost wake elsewhere,
From me far off, with others all too near.

- William Shakespere)END";



//RerunOutputWatcher *rerun_output_watcher;

System::System(ALLEGRO_DISPLAY *display, Hexagon::System::Config &config, Motion &motion)
   : display(display)
   , config(config)
   , motion(motion)
   , files_changed(false)
   , files_committed(true)
   , in_sync_with_remote(true)
   , stages({})
   //, file_navigator(al_get_current_directory())
   , camera(0, 0, 0)
   , last_file_navigator_selection("")
   , last_component_navigator_selection("")
   , global_font_resource_filename("Menlo-Regular.ttf")
   //, global_font_resource_filename("consolas.ttf")
   , global_font_size(-20)
   , command_mode(false)
   , focused_component_name("")
   , focused_component_name_relative_names()
   , font_bin()
   , hud(display, font_bin)
   , default_camera_stepback(70)
{
}

bool System::initialize()
{
   config.initialize();

   font_bin.set_path("data/fonts");

   hud.initialize();

   camera.stepback.z = get_default_camera_stepback();

   //process_local_event(EXECUTE_MAGIC_COMMAND);

   //camera.stepback = 10;
   //camera.zoom_pos -= 3.1;
   //camera.position.x += 20;
   //camera.position.y -= 10;
   //camera.set45_isometric();
   //ALLEGRO_FS_ENTRY *current_directory_fs_entry = al_create_fs_entry(al_get_current_directory());
   //file_navigator.set_file_system_entries(get_directory_listing_recursive(al_get_current_directory()));
   //process_local_event(SPAWN_RERUN_OUTPUT_WATCHER);
   //process_local_event(SPAWN_COMPONENT_NAVIGATOR);
   //process_local_event(REFRESH_RERUN_OUTPUT_WATCHERS);
}

std::string System::get_default_navigator_directory()
{
   return config.get_default_navigator_directory();
}

int System::get_display_default_width()
{
   return config.get_initial_display_width();
}

int System::get_display_default_height()
{
   return config.get_initial_display_height();
}

float System::get_default_camera_stepback()
{
   return default_camera_stepback;
}

float System::get_default_code_editor_stage_width()
{
   return 2430/2 + 20;
}

placement3d System::build_component_navigator_initial_place()
{
   placement3d result;
   result.position = camera.position;
   result.size = vec3d(800, 700, 30);
   result.align = vec3d(0.5, 0.5, 0.5);
   result.scale = vec3d(0.8, 0.8, 1.0);
   result.rotation = vec3d(0.0, 0.0, 0.0);
   return result;
}

placement3d System::build_file_navigator_initial_place()
{
   placement3d result;
   result.position = camera.position;
   result.size = vec3d(500, 600, 30);
   result.align = vec3d(0.5, 0.5, 0.5);
   result.scale = vec3d(0.8, 0.8, 1.0);
   result.rotation = vec3d(0.0, 0.0, 0.0);
   return result;
}

std::string System::get_global_font_str()
{
   std::stringstream result;
   result << global_font_resource_filename << " " << global_font_size;
   return result.str();
}

// util
std::vector<std::string> System::get_directory_listing_recursive(std::string directory)
{
   if (!al_is_system_installed()) al_init();

   std::vector<std::string> results;
   ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(directory.c_str());

   if(al_open_directory(dir))
   {
      ALLEGRO_FS_ENTRY* file;
      while((file=al_read_directory(dir)))
      {
         results.push_back(al_get_fs_entry_name(file));
         al_destroy_fs_entry(file);
      }
   }
   else
   {
      std::cout << "could not open directory \"" << directory << "\"" << std::endl;
   }

   al_destroy_fs_entry(dir);

   return results;
}


// retrieval

StageInterface *System::get_frontmost_stage()
{
   if (stages.size() == 0) return nullptr;
   return stages.back();
}

CodeEditor::Stage *System::get_frontmost_code_editor_stage()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return nullptr;

   StageInterface::type_t type = frontmost_stage->get_type();
   if (type == CodeEditor::Stage::ONE_LINE_INPUT_BOX || type == CodeEditor::Stage::CODE_EDITOR)
   {
      return static_cast<CodeEditor::Stage *>(get_frontmost_stage());
   }
   return nullptr;
}

std::vector<CodeEditor::Stage *> System::get_all_code_editor_stages()
{
   std::vector<CodeEditor::Stage *> result;

   for (auto &stage : stages)
   {
      StageInterface::type_t type = stage->get_type();
      if (type == CodeEditor::Stage::CODE_EDITOR)
      {
         result.push_back(static_cast<CodeEditor::Stage *>(stage));
      }
   }

   return result;
}

int System::get_number_of_code_editor_stages()
{
   int result = 0;
   for (auto &stage : stages)
   {
      if (stage->get_type() == CodeEditor::Stage::CODE_EDITOR) result++;
   }
   return result;
}

// inference

bool System::is_current_stage_in_edit_mode()
{
   CodeEditor::Stage *frontmost_stage = get_frontmost_code_editor_stage();
   if (!frontmost_stage) return false;
   return frontmost_stage->get_mode() == CodeEditor::Stage::EDIT;
}

bool System::is_current_stage_a_modal()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return false;
   return frontmost_stage->infer_is_modal();
}

bool System::is_current_stage_a_regex_input_box()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage)
   {
      std::cout << "Warning: attempting to infer if is_current_stage_a_regex_input_box() but no frontmost stage exists" << std::endl;
      return false;
   }
   return frontmost_stage && (frontmost_stage->get_type() == StageInterface::ONE_LINE_INPUT_BOX);
}

// internal messages
void System::acknowledge_display_resize(ALLEGRO_DISPLAY *display)
{
   hud.reinitialize();
}

void System::acknowledge_display_switch_out(ALLEGRO_DISPLAY *display)
{
   hud.set_show_disabled_screen(true);
}

void System::acknowledge_display_switch_in(ALLEGRO_DISPLAY *display)
{
   hud.set_show_disabled_screen(false);
}

// actions

bool System::mark_as_files_changed()
{
   this->files_changed = true;
   return true;
}

bool System::mark_as_files_committed()
{
   this->files_committed = true;
   return true;
}

bool System::mark_as_in_sync_with_remote()
{
   this->in_sync_with_remote = true;
   return true;
}

bool System::mark_as_files_unchanged()
{
   this->files_changed = false;
   return true;
}

bool System::mark_as_files_uncommitted()
{
   this->files_committed = false;
   return true;
}

bool System::mark_as_not_in_sync_with_remote()
{
   this->in_sync_with_remote = false;
   return true;
}

bool System::write_focused_component_name_to_file()
{
   std::string hard_coded_project_path = "/Users/markoates/Repos/hexagon/";
   std::string FOCUSED_COMPONENT_FILENAME = hard_coded_project_path + "bin/programs/data/tmp/focused_component.txt";
   std::string focused_component_to_write = focused_component_name;

   bool success = php::file_put_contents(FOCUSED_COMPONENT_FILENAME, focused_component_to_write);
   if (!success) throw std::runtime_error("[System::write_focused_component_name_to_file()] error: could not file_put_contents()");

   return true;
}

bool System::set_hud_title_to_focused_component_name()
{
   hud.set_title_text(focused_component_name);
   return true;
}

bool System::set_focused_component_name_relative_names_from_focused_component_name()
{
   //get_default_navigator_directory(),
   Blast::Project::Component component(focused_component_name, get_default_navigator_directory());
   Blast::Project::ComponentRelativeLister lister(&component);
   this->focused_component_name_relative_names  = lister.list_component_relative_names();
   return true;
}

bool System::set_focused_component_name_to_topmost_relative()
{
   if (this->focused_component_name_relative_names.empty())
   {
      std::cout << "Warning: attempting to set_focused_component_name_to_topmost_relative() "
                << "but no focused_component_name_relative_names exists"
                << std::endl;
      return false;
   }

   focused_component_name = focused_component_name_relative_names.front();

   return true;
}

bool System::fx__play_focus_animation_on_frontmost_stage()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage)
   {
      std::cout << "Warning: attempting to infer if is_current_stage_a_regex_input_box() "
                << "but no frontmost stage exists" << std::endl;
      return false;
   }

   for (auto &stage : stages)
   {
      placement3d &stage_place = stage->get_place();
      float unfocused_zoom = 0.0f;
      float focused_zoom = 0.0f;
      float duration = 0.3f;

      if (stage == frontmost_stage)
      {
         motion.cmove_to(&stage_place.position.z,
                         focused_zoom,
                         duration,
                         interpolator::double_fast_in,
                         nullptr,
                         nullptr);
      }
      else
      {
         motion.cmove_to(&stage_place.position.z,
                         unfocused_zoom,
                         duration,
                         interpolator::double_fast_in,
                         nullptr,
                         nullptr);
      }
   }

   return true;
}

bool System::toggle_command_mode_on()
{
   if (command_mode) return true;

   float camera_zoomed_out_position = get_default_camera_stepback() + 10;
   float camera_zoomed_in_position = get_default_camera_stepback();
   motion.canimate(&camera.stepback.z,
                   camera.stepback.z,
                   camera_zoomed_out_position,
                   al_get_time(),
                   al_get_time()+0.2,
                   interpolator::fast_in,
                   nullptr,
                   nullptr);
   command_mode = true;
   //camera.rotation
   //std::rotate(stages.begin(), stages.begin() + 1, stages.end());
   return true;
}

bool System::toggle_command_mode_off()
{
   if (!command_mode) return true;

   float camera_zoomed_out_position = get_default_camera_stepback() + 10;
   float camera_zoomed_in_position = get_default_camera_stepback();
   motion.canimate(&camera.stepback.z,
                   camera.stepback.z,
                   camera_zoomed_in_position,
                   al_get_time(),
                   al_get_time()+0.2,
                   interpolator::fast_in,
                   nullptr,
                   nullptr);
   command_mode = false;
   //std::rotate(stages.begin(), stages.begin() + 1, stages.end());
   return true;
}

bool System::rotate_stage_right()
{
   if (stages.empty())
   {
      std::cout << "Warning: attempting to rotate_stage_right() but no frontmost stage exists" << std::endl;
      return false;
   }

   std::rotate(stages.begin(), stages.begin() + 1, stages.end());
   return true;
}

bool System::rotate_stage_left()
{
   if (stages.empty())
   {
      std::cout << "Warning: attempting to rotate_stage_right() but no frontmost stage exists" << std::endl;
      return false;
   }

   std::rotate(stages.rbegin(), stages.rbegin() + 1, stages.rend());
   return true;
}

bool System::rotate_relative_up()
{
   if (focused_component_name_relative_names.empty())
   {
      std::cout << "Warning: attempting to " << __FUNCTION__ << " but no frontmost stage exists" << std::endl;
      return false;
   }

   std::rotate(
      focused_component_name_relative_names.rbegin(),
      focused_component_name_relative_names.rbegin() + 1,
      focused_component_name_relative_names.rend());

   return true;
}

bool System::rotate_relative_down()
{
   if (focused_component_name_relative_names.empty())
   {
      std::cout << "Warning: attempting to " << __FUNCTION__ << " but no frontmost stage exists" << std::endl;
      return false;
   }

   std::rotate(
      focused_component_name_relative_names.begin(),
      focused_component_name_relative_names.begin() + 1,
      focused_component_name_relative_names.end());
   return true;
}

bool System::center_camera_on_frontmost_stage()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage)
   {
      std::cout << "Warning: attempting to center_camera_on_frontmost_stage() but no frontmost stage exists" << std::endl;
      return false;
   }

   placement3d &place = frontmost_stage->get_place();
   vec3d target = place.position;
   //camera.position = target;
   motion.cmove_to(&camera.position.x, target.x, 0.2, interpolator::double_fast_in);
   motion.cmove_to(&camera.position.y, target.y, 0.2, interpolator::double_fast_in);
   motion.cmove_to(&camera.position.z, target.z, 0.2, interpolator::double_fast_in);

   return true;
}

bool System::run_project_tests()
{
   CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
   if (!stage) throw std::runtime_error("cannot run tests on current stage -- not a stage stage");

   std::string test_output = RailsMinitestTestRunner(stage->get_filename()).run();
   Hexagon::RailsTestOutputParser rails_test_output_parser(test_output);
   //for (auto &test_result_line : rails_test_output_parser.get_test_result_lines())
   //{
      //std::cout << test_result_line << std::endl;
      //std::cout << "=============================" << std::endl;
   //}

   std::vector<CodeMessagePoint> code_message_points;
   for (auto &minitest_test_result : rails_test_output_parser.get_test_result_lines())
   {
      switch(minitest_test_result.get_test_state())
      {
         case RailsMinitestTestResult::ERROR:
         case RailsMinitestTestResult::FAILURE:
         {
            Hexagon::RailsMinitestTestResultToCodeMessagePointConverter converter(minitest_test_result);
            code_message_points.push_back(converter.convert());
            break;
         }
         default: break;
      }

   }
   stage->clear_code_message_points();
   stage->set_code_message_points({ code_message_points });

   return true;
}

bool System::save_current_stage()
{
   CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
   if (!stage) throw std::runtime_error("Cannot save_current_stage; current stage is not a stage stage");

   get_frontmost_code_editor_stage()->save_file();
   process_local_event(REMOVE_FILE_IS_UNSAVED_NOTIFICATION);

   return true;
}

bool System::increase_font_size()
{
   global_font_size -= 1;
}

bool System::decrease_font_size()
{
   global_font_size += 1;
}

bool System::refresh_regex_hilights_on_stage()
{
   CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
   if (!stage) throw std::runtime_error("Cannot refresh_regex_hilights_on_stage; current stage is not a stage stage");
   stage->refresh_regex_message_points();
   return true;
}

bool System::set_regex_input_box_modal_to_insert_mode()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return false;
   frontmost_stage->process_local_event(CodeEditor::EventController::SET_INSERT_MODE);
   return true;
}

bool System::spawn_regex_input_box_modal()
{
   //TODO: this placement should be relative to the camera, or, the window should be placed on a non-transforming render surface
   // for now, I'm going to have it spawn at the position of the camera
   placement3d place(0.0, 0.0, 0.0);
   place.position = camera.position;
   place.size = vec3d(300, 25, 0.0);
   place.scale = vec3d(1.4, 1.4, 1.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);

   CodeEditor::Stage *stage = new CodeEditor::Stage(REGEX_TEMP_FILENAME, "input_box", CodeEditor::Stage::EDIT, CodeEditor::Stage::ONE_LINE_INPUT_BOX); // TODO: extract this one line input box from CodeEditor
   stage->set_place(place);
   stages.push_back(stage);

   placement3d& stage_place = stage->get_place();
   stage_place.scale.x = 1.5;
   stage_place.scale.y = 1.5;
   //motion.canimate(&stage_place.scale.x, 1.7, 1.5, al_get_time(), al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);
   //motion.canimate(&stage_place.scale.y, 1.7, 1.5, al_get_time(), al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);

   std::vector<std::string> file_contents;

   stage->set_initial_content(std::vector<std::string>{"", ""});

   return true;
}

bool System::spawn_component_navigator()
{
   //placement3d component_navigator_initial_place = component_navigator_initial_place;
  
   Hexagon::ComponentNavigator::Stage *component_navigator =
      new Hexagon::ComponentNavigator::Stage(get_default_navigator_directory());
   component_navigator->process_local_event("refresh_list");
   component_navigator->set_place(build_component_navigator_initial_place());
   stages.push_back(component_navigator);

   motion.cmove_to(&camera.rotation.y, camera.rotation.y, camera.rotation.y+0.02, interpolator::tripple_fast_in);

   placement3d& stage_place = component_navigator->get_place();
   motion.cmove_to(&stage_place.rotation.y, 0.0, 0.3, interpolator::tripple_fast_in);
   motion.cmove_to(&stage_place.position.z, 30.0, 0.3, interpolator::tripple_fast_in);
   return true;
}

bool System::spawn_red_overlay()
{
   Hexagon::FullScreenOverlay::Stage *red_overlay = new Hexagon::FullScreenOverlay::Stage;
   stages.push_back(red_overlay);
}

bool System::spawn_file_navigator()
{
   Hexagon::FileNavigator::Stage *file_navigator = new Hexagon::FileNavigator::Stage(get_default_navigator_directory());
   file_navigator->process_local_event("refresh_list");
   file_navigator->set_place(build_file_navigator_initial_place());
   stages.push_back(file_navigator);
   return true;
}

bool System::spawn_file_navigator_from_last_file_navigator_folder_selection()
{
   //TODO: this function does not guard against a "last_file_navigator_selection" that could potentially not be a folder 

   Hexagon::FileNavigator::Stage *file_navigator = new Hexagon::FileNavigator::Stage(last_file_navigator_selection);
   file_navigator->process_local_event("refresh_list");
   file_navigator->set_place(build_file_navigator_initial_place());

   stages.push_back(file_navigator);

   placement3d& stage_place = file_navigator->get_place();
   return true;
}

bool System::spawn_rerun_output_watcher()
{
   float golden_ratio = 0.61803f;
   float x_pos = golden_ratio * get_display_default_width() - get_display_default_width()/2;
   placement3d place(x_pos, -get_display_default_height()/2 + 30, 0);
   place.size = vec3d(0, 0, 0.0);
   place.align = vec3d(0, 0, 0);
   place.scale = vec3d(0.7, 0.7, 0.0);

   Hexagon::RerunOutputWatcher::Stage *rerun_output_watcher = new Hexagon::RerunOutputWatcher::Stage();
   rerun_output_watcher->set_place(place);
   stages.push_back(rerun_output_watcher);
   return true;
}

void System::add_file_is_unsaved_notification()
{
   add_notification(NOTIFICATION_FILE_IS_UNSAVED);
}

void System::remove_file_is_unsaved_notification()
{
   remove_notification(NOTIFICATION_FILE_IS_UNSAVED);
}

void System::clear_rerun_output_watchers()
{
   for (auto &stage : stages)
   {
      if (stage->get_type() == StageInterface::RERUN_OUTPUT_WATCHER)
      {
         Hexagon::RerunOutputWatcher::Stage *watcher = static_cast<Hexagon::RerunOutputWatcher::Stage *>(stage);
         watcher->clear();
      }
   }
}

bool System::refresh_rerun_output_watchers()
{
   for (auto &stage : stages)
   {
      if (stage->get_type() == StageInterface::RERUN_OUTPUT_WATCHER)
      {
         Hexagon::RerunOutputWatcher::Stage *watcher = static_cast<Hexagon::RerunOutputWatcher::Stage *>(stage);

         std::vector<std::string> file_contents = {};
         if (!::read_file(file_contents, MAKE_COMMAND_FILENAME)) throw std::runtime_error("Could not open the make command file");

         watcher->set_command(file_contents[0]);
         watcher->refresh();
      }
   }
   return true;
}

bool System::destroy_topmost_stage()
{
   if (stages.size() >= 1)
   {
      delete stages.back();
      stages.pop_back();
      return true;
   }
   else
   {
      throw std::runtime_error("attempted to destroy_topmost_stage(), but no stages are present");
   }
}


static std::vector<std::string> __list_of_files_in_file_list()
{
   std::string hard_coded_project_path = "/Users/markoates/Repos/hexagon/";
   static std::string FILE_LIST_FILENAME = hard_coded_project_path + "bin/programs/data/config/files_to_open_at_startup.txt";

   std::vector<std::string> lines;
   ::read_file(lines, FILE_LIST_FILENAME);

   return lines;
}


#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <allegro_flare/useful.h>
bool System::execute_magic_command()
{
   float display_default_width = get_display_default_width();
   float display_default_height = get_display_default_height();
   std::string component_name = last_component_navigator_selection;
   float width_scale_of_halfwidth = 1.0; //0.6180339;

   ///

   std::string project_path;
   std::vector<std::string> filenames = {};

   //project_path = "/Users/markoates/dev_repos/partners/";
   //filenames = {
   //   project_path + "app/models/external_job.rb",
   //   project_path + "spec/models/external_job_spec.rb",
   //   project_path + "spec/factories/external_job_factory.rb",
   //};
   //project_path = "/Users/markoates/Repos/hexagon/";
   //filenames = {
   //   project_path + "quintessence/System/System.cpp",
   //   project_path + "include/Hexagon/System/System.hpp",
   //   project_path + "src/Hexagon/System/System.hpp",
   //};
   project_path = "/Users/markoates/Repos/hexagon/";
   filenames = {
      project_path + "src/Hexagon/System/System.cpp",
   };
   focused_component_name = "Hexagon/System/System";
   set_hud_title_to_focused_component_name();
   write_focused_component_name_to_file();
   set_focused_component_name_relative_names_from_focused_component_name();

   filenames = __list_of_files_in_file_list();

   ///


   float width = get_default_code_editor_stage_width();
   std::string filename = "";
   bool file_present = false;
   int i=0;

   destroy_all_code_editor_stages();

   ///

   for (i=0; i<filenames.size(); i++)
   {
      filename = filenames[i];
      file_present = true;
      if (!Blast::FileExistenceChecker(filename).exists()) file_present = false;
      //if (!file_contents.empty())
      {
        placement3d place(0, 0, 0);
        place.size = vec3d(width, display_default_height, 0.0);

        place.position = vec3d(width*i, 0.0, 0.0);
        place.align = vec3d(0.5, 0.5, 0.0);
        place.scale = vec3d(1.0, 1.0, 0.0);

        StageInterface *stage = nullptr;

        if (file_present)
        {
           std::vector<std::string> file_contents = {};
           ::read_file(file_contents, filename);
           stage = new CodeEditor::Stage(filename);
           static_cast<CodeEditor::Stage*>(stage)->set_initial_content(file_contents);
        }
        else
        {
            stage = new Hexagon::MissingFile::Stage;
        }

        stage->set_place(place);
        stages.push_back(stage);
      }
   }

   //

   bool show_rerun_output_watcher = false;
   if (show_rerun_output_watcher)
   {
      float golden_ratio = 0.61803f;
      float x_pos = golden_ratio * get_display_default_width() - get_display_default_width()/2;
      placement3d place(0, 0, 0);

      place.position = vec3d(width*i, 0.0, 0.0);
      place.size = vec3d(width, display_default_height, 0.0);
      place.align = vec3d(0.5, 0.5, 0);
      place.scale = vec3d(0.9, 0.9, 0.0);

      Hexagon::RerunOutputWatcher::Stage *rerun_output_watcher = new Hexagon::RerunOutputWatcher::Stage();
      rerun_output_watcher->set_place(place);
      stages.push_back(rerun_output_watcher);
   }

   //

   process_local_event(ROTATE_STAGE_RIGHT);
   process_local_event(CENTER_CAMERA_ON_FRONTMOST_STAGE);

   return true;
}

bool System::jump_to_next_code_point_on_stage()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return false;
   frontmost_stage->process_local_event(CodeEditor::EventController::JUMP_TO_NEXT_CODE_POINT);
   return true;
}

bool System::clear_last_compiled_error_messages()
{
   ::clear_last_compiled_error_messages();
   return true;
}

bool System::enable_drawing_info_overlays_on_all_code_editor_stages()
{
}

bool System::disble_drawing_info_overlays_on_all_code_editor_stages()
{
}

bool System::run_make()
{
   CppCompiler::CompileRunner compile_runner(
     get_default_navigator_directory(),
     "foobar");
   std::string compile_output = compile_runner.run();
   std::cout << compile_output << std::endl;
   set_last_compiled_error_messages(compile_output);
   //CppCompiler::CompileOutputToCodeMessagePointSetter(compile_output, this);
   return true;
}

bool System::offset_first_line_to_vertically_center_cursor_on_stage()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return false;
   frontmost_stage->process_local_event(CodeEditor::EventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR);
   return true;
}

bool System::push_component_navigator_selection()
{
   StageInterface *frontmost_stage_interface = get_frontmost_stage();
   if (!frontmost_stage_interface || !(frontmost_stage_interface->get_type() == StageInterface::COMPONENT_NAVIGATOR))
   {
      std::stringstream error_message;
      std::string function_name = "push_component_navigator_selection";
      error_message << "Could not " << function_name << ": Either the frontmost_stage_interface is a nullptr OR is not of type StageInterface::COMPONENT_NAVIGATOR." << std::endl;
      throw std::runtime_error(error_message.str().c_str());
   }
   Hexagon::ComponentNavigator::Stage *component_navigator = static_cast<Hexagon::ComponentNavigator::Stage *>(frontmost_stage_interface);

   std::string current_component_navigator_selection = component_navigator->get_current_selection_label_or_empty_string();

   last_component_navigator_selection = current_component_navigator_selection;
   return true;
}

bool System::push_file_navigator_selection()
{
   StageInterface *frontmost_stage_interface = get_frontmost_stage();
   if (!frontmost_stage_interface || !(frontmost_stage_interface->get_type() == StageInterface::FILE_NAVIGATOR))
   {
      std::stringstream error_message;
      std::string function_name = "push_file_navigator_selection";
      error_message << "Could not " << function_name << ": Either the frontmost_stage_interface is a nullptr OR is not of type StageInterface::FILE_NAVIGATOR." << std::endl;
      throw std::runtime_error(error_message.str().c_str());
   }

   Hexagon::FileNavigator::Stage *file_navigator = static_cast<Hexagon::FileNavigator::Stage *>(frontmost_stage_interface);
   std::string current_file_navigator_selection = file_navigator->get_current_selection();

   last_file_navigator_selection = current_file_navigator_selection;
   return true;
}

bool System::attempt_to_create_stage_from_last_file_navigator_selection()
{
   //throw std::runtime_error("attempt_to_open_file_navigator_file not yet implemented");

   std::string filename = last_file_navigator_selection;

   ///

   float stage_width = get_default_code_editor_stage_width();

   // validate the selected path is a valid file
   ALLEGRO_FS_ENTRY *fs_entry = al_create_fs_entry(filename.c_str());
   if (!fs_entry)
   {
      std::stringstream error_message;
      error_message << "Could not attempt_to_create_stage_from_last_file_navigator_selection: "
                    << "fs_entry could not be created. al_get_errno() returned with "
                    << al_get_errno() << std::endl;
      throw std::runtime_error(error_message.str().c_str());
   }
   FileSystemNode file_system_node(fs_entry);
   if (file_system_node.infer_is_directory()) // is a valid folder
   {
      //TODO: some sloppy behavior here.  This method should be better encapsulated in the file navigator component
      process_local_event(SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION);
   }
   else // is a valid file
   {
      Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action(
         filename,
         get_display_default_width(),
         get_display_default_height(),
         get_default_code_editor_stage_width(),
         &stages);

      action.execute();

      //std::vector<std::string> file_contents = {};
      //if (!::read_file(file_contents, filename)) throw std::runtime_error("Could not open the selected file");

      //int number_of_files = get_number_of_code_editor_stages();
      //float one_third_screen_width = get_display_default_width() / 3;

      //placement3d place(one_third_screen_width*number_of_files, 0, 0);
      //place.size = vec3d(stage_width, get_display_default_height(), 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
      //place.align = vec3d(0.5, 0.5, 0.0);
      //place.scale = vec3d(0.9, 0.9, 0.0);

      //CodeEditor::Stage *stage = new CodeEditor::Stage(filename);// place);

      //stage->set_place(place);
      //stage->set_content(file_contents);
      //stages.push_back(stage);

      ////throw std::runtime_error("attempt_to_open_file_navigator_file not yet implemented to open a file");
   }

   return true;
}

bool System::destroy_all_code_editor_stages()
{
   Hexagon::System::Action::DestroyAllCodeEditorStages action(stages);
   return action.managed_execute();
}

bool System::create_two_or_three_split_layout_from_last_component_navigator_selection()
{
   if (last_component_navigator_selection.empty())
   {
      std::stringstream error_message;
      error_message << "[" << typeid(*this).name() << "::" << __FUNCTION__ << " error:]"
                    << " guard not met: last_component_navigator_selection cannot be empty";
      throw std::runtime_error(error_message.str());
      return false;
   }

   Blast::Project::Component component(last_component_navigator_selection, get_default_navigator_directory());

   if (component.has_only_source_and_header())
   {
      focused_component_name = last_component_navigator_selection;

      set_hud_title_to_focused_component_name();
      write_focused_component_name_to_file();
      set_focused_component_name_relative_names_from_focused_component_name();
      return create_three_split_from_last_component_navigator_selection();
   }
   else if (component.has_quintessence() || component.has_test())
   {
      focused_component_name = last_component_navigator_selection;

      set_hud_title_to_focused_component_name();
      write_focused_component_name_to_file();
      set_focused_component_name_relative_names_from_focused_component_name();
      return attempt_to_create_stage_from_last_component_navigator_selection();
   }
   else
   {
      std::cout << "cannot create_two_or_three_split_layout_from_last_component_navigator_selection because the component \"" << component.get_name() << "\" " \
         "neither has a header/source combo nor a quintessence or test file." << std::endl;
      return true;
   }
}

bool System::create_three_split_from_last_component_navigator_selection()
{
   Blast::Project::Component component(last_component_navigator_selection, get_default_navigator_directory());
   Hexagon::System::Action::CreateThreeSplitFromComponent action(
      get_default_navigator_directory(),
      component,
      stages,
      get_display_default_width(),
      get_display_default_height(),
      get_default_code_editor_stage_width()
   );
   return action.managed_execute();
}

bool System::attempt_to_create_stage_from_last_component_navigator_selection()
{
   Hexagon::System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection action(
         get_default_navigator_directory(),
         last_component_navigator_selection,
         get_display_default_width(),
         get_display_default_height(),
         stages,
         get_default_code_editor_stage_width());
   return action.managed_execute();
}

bool System::submit_current_modal()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return false;

   switch (frontmost_stage->get_type())
   {
   case StageInterface::ONE_LINE_INPUT_BOX:
      process_local_event(SAVE_CURRENT_STAGE);
      process_local_event(DESTROY_TOPMOST_STAGE);
      process_local_event(REFRESH_REGEX_HILIGHTS_ON_STAGE);
      process_local_event(JUMP_TO_NEXT_CODE_POINT_ON_STAGE);
      process_local_event(OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE);
      break;
   case StageInterface::FILE_NAVIGATOR:
      process_local_event(PUSH_FILE_NAVIGATOR_SELECTION);
      process_local_event(DESTROY_TOPMOST_STAGE);  // destroys the modal
      process_local_event(ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION);
      break;
   case StageInterface::COMPONENT_NAVIGATOR:
      process_local_event(PUSH_COMPONENT_NAVIGATOR_SELECTION);
      process_local_event(DESTROY_TOPMOST_STAGE);
      process_local_event(DESTROY_ALL_CODE_EDITOR_STAGES);
      process_local_event(CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION);
      process_local_event(ROTATE_STAGE_LEFT);
      process_local_event(CENTER_CAMERA_ON_FRONTMOST_STAGE);
      break;
   default:
      throw std::runtime_error("submit_current_modal(): invalid modal type");
      break;
   }
   return true;
}

bool System::escape_current_modal()
{
   process_local_event(DESTROY_TOPMOST_STAGE);
   return true;
}

bool System::open_hexagon_config_file()
{
   std::string config_filename = config.get_config_filename();
   if (!display) throw std::runtime_error("fooob arrra");

   Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action(
      config_filename,
      al_get_display_width(display),
      al_get_display_height(display),
      get_default_code_editor_stage_width(),
      &stages
      );

   return action.managed_execute();
}

//bool System::spawn_keyboard_inputs_modal()
//{
//   KeyboardInputsModal::Stage *keyboard_input_modal = new KeyboardInputsModal::Stage(nullptr);
//   stages.push_back(keyboard_input_modal);
//   return true;
//}

void System::process_local_event(std::string event_name) // this function is 1:1 execute the action.  It does no calling of other actions before or after
{
   std::cout << "System::" << event_name << std::endl;

   try
   {
      bool executed = false;

      if (event_name == ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION) { attempt_to_create_stage_from_last_file_navigator_selection(); executed = true; }
      else if (event_name == ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION) { attempt_to_create_stage_from_last_component_navigator_selection(); executed = true; }
      else if (event_name == SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION) { spawn_file_navigator_from_last_file_navigator_folder_selection(); executed = true; }
      else if (event_name == CREATE_THREE_SPLIT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION) { create_three_split_from_last_component_navigator_selection(); executed = true; }
      else if (event_name == CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION) { create_two_or_three_split_layout_from_last_component_navigator_selection(); executed = true; }
      else if (event_name == CLEAR_RERUN_OUTPUT_WATCHERS) { clear_rerun_output_watchers(); executed = true; }
      else if (event_name == CENTER_CAMERA_ON_FRONTMOST_STAGE) { center_camera_on_frontmost_stage(); executed = true; }
      else if (event_name == DESTROY_TOPMOST_STAGE) { destroy_topmost_stage(); executed = true; }
      else if (event_name == OPEN_HEXAGON_CONFIG_FILE) { open_hexagon_config_file(); executed = true; }
      else if (event_name == DESTROY_ALL_CODE_EDITOR_STAGES) { destroy_all_code_editor_stages(); executed = true; }
      else if (event_name == ESCAPE_CURRENT_MODAL) { escape_current_modal(); executed = true; }
      else if (event_name == JUMP_TO_NEXT_CODE_POINT_ON_STAGE) { jump_to_next_code_point_on_stage(); executed = true; }
      else if (event_name == OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE) { offset_first_line_to_vertically_center_cursor_on_stage(); executed = true; }
      else if (event_name == PUSH_FILE_NAVIGATOR_SELECTION) { push_file_navigator_selection(); executed = true; }
      else if (event_name == PUSH_COMPONENT_NAVIGATOR_SELECTION) { push_component_navigator_selection(); executed = true; }
      else if (event_name == REFRESH_REGEX_HILIGHTS_ON_STAGE) { refresh_regex_hilights_on_stage(); executed = true; }
      else if (event_name == REFRESH_RERUN_OUTPUT_WATCHERS) { refresh_rerun_output_watchers(); executed = true; }
      else if (event_name == INCREASE_FONT_SIZE) { increase_font_size(); executed = true; }
      else if (event_name == DECREASE_FONT_SIZE) { decrease_font_size(); executed = true; }
      else if (event_name == ADD_FILE_IS_UNSAVED_NOTIFICATION) { add_file_is_unsaved_notification(); executed = true; }
      else if (event_name == WRITE_FOCUSED_COMPONENT_NAME_TO_FILE) { write_focused_component_name_to_file(); executed = true; }
      else if (event_name == REMOVE_FILE_IS_UNSAVED_NOTIFICATION) { remove_file_is_unsaved_notification(); executed = true; }
      else if (event_name == TOGGLE_COMMAND_MODE_ON) { toggle_command_mode_on(); executed = true; }
      else if (event_name == TOGGLE_COMMAND_MODE_OFF) { toggle_command_mode_off(); executed = true; }
      else if (event_name == ROTATE_STAGE_LEFT) { rotate_stage_left(); executed = true; }
      else if (event_name == ROTATE_STAGE_RIGHT) { rotate_stage_right(); executed = true; }
      else if (event_name == ROTATE_RELATIVE_UP) { rotate_relative_up(); executed = true; }
      else if (event_name == ROTATE_RELATIVE_DOWN) { rotate_relative_down(); executed = true; }
      else if (event_name == RUN_MAKE) { run_make(); executed = true; }
      else if (event_name == CLEAR_LAST_COMPILED_ERROR_MESSAGES) { clear_last_compiled_error_messages(); executed = true; }
      else if (event_name == RUN_PROJECT_TESTS) { run_project_tests(); executed = true; }
      else if (event_name == SAVE_CURRENT_STAGE) { save_current_stage(); executed = true; }
      else if (event_name == SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE) { set_regex_input_box_modal_to_insert_mode(); executed = true; }
      else if (event_name == SET_FOCUSED_COMPONENT_NAME_TO_TOPMOST_RELATIVE) { set_focused_component_name_to_topmost_relative(); executed = true; }
      else if (event_name == SPAWN_COMPONENT_NAVIGATOR) { spawn_component_navigator(); executed = true; }
      else if (event_name == EXECUTE_MAGIC_COMMAND) { execute_magic_command(); executed = true; }
      else if (event_name == SPAWN_FILE_NAVIGATOR) { spawn_file_navigator(); executed = true; }
      //else if (event_name == SPAWN_KEYBOARD_INPUTS_MODAL) { spawn_keyboard_inputs_modal(); executed = true; }
      else if (event_name == SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL) { spawn_regex_input_box_modal(); executed = true; }
      else if (event_name == SPAWN_RERUN_OUTPUT_WATCHER) { spawn_rerun_output_watcher(); executed = true; }
      else if (event_name == SUBMIT_CURRENT_MODAL) { submit_current_modal(); executed = true; }
      else if (event_name == FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE) { fx__play_focus_animation_on_frontmost_stage(); executed = true; }

      if (!executed) std::cout << "???? cannot execute \"" << event_name << "\".  It does not exist." << std::endl;
   }
   catch (const std::exception &exception)
   {
      std::cout << ">BOOM< cannot execute \"" << event_name << "\".  The following exception occurred: " << exception.what() << std::endl;
      // add the thing right here
      std::stringstream error_message;
      error_message << "An exception was thrown: \"" << exception.what() << "\"";
      add_notification(error_message.str());
   }
}

void System::process_event(ALLEGRO_EVENT &event)
{
   KeyboardCommandMapper keyboard_key_up_mapper;
   KeyboardCommandMapper keyboard_key_down_mapper;
   KeyboardCommandMapper keyboard_command_mapper;

   keyboard_key_down_mapper.set_mapping(ALLEGRO_KEY_COMMAND, false, false, false, false, { TOGGLE_COMMAND_MODE_ON });
   keyboard_key_up_mapper.set_mapping(ALLEGRO_KEY_COMMAND, false, false, false, false, { TOGGLE_COMMAND_MODE_OFF });


   //                      set_mapping(al_keycode,         shift, ctrl,  alt,   command, std::vector<std::string> command_identifiers
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, { DESTROY_TOPMOST_STAGE });

   if (is_current_stage_a_modal())
   {
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, false, { SUBMIT_CURRENT_MODAL });
   }
   else
   {
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_PAD_PLUS, false, false, false, false, { INCREASE_FONT_SIZE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_PAD_MINUS, false, false, false, false, { DECREASE_FONT_SIZE });
      //keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, true,  false, false, false, { SPAWN_KEYBOARD_INPUTS_MODAL });

      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, false, false, true, { ROTATE_STAGE_LEFT, CENTER_CAMERA_ON_FRONTMOST_STAGE, FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_CLOSEBRACE, false, false, false, true, { ROTATE_STAGE_RIGHT, CENTER_CAMERA_ON_FRONTMOST_STAGE, FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKQUOTE, false, false, false, false, {
          OPEN_HEXAGON_CONFIG_FILE,
          CENTER_CAMERA_ON_FRONTMOST_STAGE,
          });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, true, false, false, true, {
          ROTATE_RELATIVE_UP,
          CENTER_CAMERA_ON_FRONTMOST_STAGE,
          FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_CLOSEBRACE, true, false, false, true, {
          DESTROY_ALL_CODE_EDITOR_STAGES,
          ROTATE_RELATIVE_DOWN,
          CENTER_CAMERA_ON_FRONTMOST_STAGE,
          FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_T, false, false, true, false, {
          SAVE_CURRENT_STAGE,
          RUN_PROJECT_TESTS });
      //keyboard_command_mapper.set_mapping(ALLEGRO_KEY_M, false, false, false, true, {
      //    SAVE_CURRENT_STAGE,
      //    CLEAR_RERUN_OUTPUT_WATCHERS,
      //    REFRESH_RERUN_OUTPUT_WATCHERS });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_M, false, false, false, true, {
          SAVE_CURRENT_STAGE,
          CLEAR_LAST_COMPILED_ERROR_MESSAGES,
          RUN_MAKE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, true, false, false, false, { SPAWN_FILE_NAVIGATOR });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, false, false, false, false, { SPAWN_COMPONENT_NAVIGATOR });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_8, true, true, false, false, { EXECUTE_MAGIC_COMMAND });

      if (is_current_stage_in_edit_mode())
      {
         keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, false, { SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL,
               SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE });
      }
   }


   bool event_caught = false;

   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_UP:
      {
         bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
         bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         //bool ctrl_or_command = ctrl || command;
         std::vector<std::string> mapped_events =
           keyboard_key_up_mapper.get_mapping(
             event.keyboard.keycode, shift, ctrl, alt, command);
         if (!mapped_events.empty()) event_caught = true;
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
      }
      break;
   case ALLEGRO_EVENT_KEY_DOWN:
      {
         bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
         bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         //bool ctrl_or_command = ctrl || command;
         std::vector<std::string> mapped_events =
           keyboard_key_down_mapper.get_mapping(
             event.keyboard.keycode, shift, ctrl, alt, command);
         if (!mapped_events.empty()) event_caught = true;
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
      }
      break;
   case ALLEGRO_EVENT_KEY_CHAR:
      {
         bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
         bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         //bool ctrl_or_command = ctrl || command;
         std::vector<std::string> mapped_events =
           keyboard_command_mapper.get_mapping(
             event.keyboard.keycode, shift, ctrl, alt, command);
         if (!mapped_events.empty()) event_caught = true;
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
      }
      break;
   }

   if (!event_caught)
   {
      //if (file_navigator.get_visible_and_active()) file_navigator.process_event(event);
      StageInterface *frontmost_stage = get_frontmost_stage();
      if (frontmost_stage) frontmost_stage->process_event(event);
   }
}

std::string System::get_action_description(std::string action_identifier)
{
   // std::map<identifier, description>
   static std::map<std::string, std::string> dictionary = {
      { System::DESTROY_FILE_NAVIGATOR, "" },
      { System::DESTROY_TOPMOST_STAGE, "" },
      { System::DESTROY_ALL_CODE_EDITOR_STAGES, "" },
      { System::ESCAPE_CURRENT_MODAL, "" },
      { System::HIDE_FILE_NAVIGATOR, "" },
      { System::INCREASE_FONT_SIZE, "" },
      { System::DECREASE_FONT_SIZE, "" },
      { System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE, "" },
      { System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE, "" },
      { System::REFRESH_REGEX_HILIGHTS_ON_STAGE, "" },
      { System::WRITE_FOCUSED_COMPONENT_NAME_TO_FILE, "" },
      { System::ADD_FILE_IS_UNSAVED_NOTIFICATION, "" },
      { System::OPEN_HEXAGON_CONFIG_FILE, "" },
      { System::REMOVE_FILE_IS_UNSAVED_NOTIFICATION, "" },
      { System::TOGGLE_COMMAND_MODE_ON, "" },
      { System::TOGGLE_COMMAND_MODE_OFF, "" },
      { System::ROTATE_STAGE_LEFT, "" },
      { System::ROTATE_STAGE_RIGHT, "" },
      { System::ROTATE_RELATIVE_UP, "" },
      { System::ROTATE_RELATIVE_DOWN, "" },
      { System::RUN_MAKE, "" },
      { System::CLEAR_LAST_COMPILED_ERROR_MESSAGES, "" },
      { System::SET_FOCUSED_COMPONENT_NAME_TO_TOPMOST_RELATIVE, "" },
      { System::RUN_PROJECT_TESTS, "" },
      { System::SAVE_CURRENT_STAGE, "" },
      { System::SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE, "" },
      { System::SPAWN_COMPONENT_NAVIGATOR, "" },
      { System::EXECUTE_MAGIC_COMMAND, "" },
      { System::SPAWN_FILE_NAVIGATOR, "" },
      //{ System::SPAWN_KEYBOARD_INPUTS_MODAL, "" },
      { System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL, "" },
      { System::SPAWN_RERUN_OUTPUT_WATCHER, "" },
      { System::SUBMIT_CURRENT_MODAL, "" },
      { System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE, "" },
   };

   for (std::map<std::string, std::string>::iterator it=dictionary.begin(); it!=dictionary.end(); ++it)
   {
      it->second = it->first;
   }

   std::map<std::string, std::string>::iterator it = dictionary.find(action_identifier);
   if (it == dictionary.end())
   {
      std::stringstream error_message;
      error_message << "🛑 Error: stuff stuff stuff stuff" << std::endl;
      throw std::runtime_error(error_message.str());
   }

   return dictionary[action_identifier];
}


const std::string System::OPEN_HEXAGON_CONFIG_FILE = "OPEN_HEXAGON_CONFIG_FILE";
const std::string System::WRITE_FOCUSED_COMPONENT_NAME_TO_FILE = "WRITE_FOCUSED_COMPONENT_NAME_TO_FILE";
const std::string System::ADD_FILE_IS_UNSAVED_NOTIFICATION = "ADD_FILE_IS_UNSAVED_NOTIFICATION";
const std::string System::REMOVE_FILE_IS_UNSAVED_NOTIFICATION = "REMOVE_FILE_IS_UNSAVED_NOTIFICATION";
const std::string System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION = "ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION";
const std::string System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION = "ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION = "SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION";
const std::string System::CREATE_THREE_SPLIT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION = "CREATE_THREE_SPLIT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION = "CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::CLEAR_RERUN_OUTPUT_WATCHERS = "CLEAR_RERUN_OUTPUT_WATCHERS";
const std::string System::SET_FOCUSED_COMPONENT_NAME_TO_TOPMOST_RELATIVE = "SET_FOCUSED_COMPONENT_NAME_TO_TOPMOST_RELATIVE";
const std::string System::CENTER_CAMERA_ON_FRONTMOST_STAGE = "CENTER_CAMERA_ON_FRONTMOST_STAGE";
const std::string System::DESTROY_FILE_NAVIGATOR = "DESTROY_FILE_NAVIGATOR";
const std::string System::DESTROY_TOPMOST_STAGE = "DESTROY_TOPMOST_STAGE";
const std::string System::DESTROY_ALL_CODE_EDITOR_STAGES = "DESTROY_ALL_CODE_EDITOR_STAGES";
const std::string System::ESCAPE_CURRENT_MODAL = "ESCAPE_CURRENT_MODAL";
const std::string System::HIDE_FILE_NAVIGATOR = "HIDE_FILE_NAVIGATOR";
const std::string System::INCREASE_FONT_SIZE = "INCREASE_FONT_SIZE";
const std::string System::DECREASE_FONT_SIZE = "DECREASE_FONT_SIZE";
const std::string System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE = "JUMP_TO_NEXT_CODE_POINT_ON_STAGE";
const std::string System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE = "OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE";
const std::string System::PUSH_FILE_NAVIGATOR_SELECTION = "PUSH_FILE_NAVIGATOR_SELECTION";
const std::string System::PUSH_COMPONENT_NAVIGATOR_SELECTION = "PUSH_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::REFRESH_REGEX_HILIGHTS_ON_STAGE = "REFRESH_REGEX_HILIGHTS_ON_STAGE";
const std::string System::REFRESH_RERUN_OUTPUT_WATCHERS = "REFRESH_RERUN_OUTPUT_WATCHERS";
const std::string System::TOGGLE_COMMAND_MODE_ON = "TOGGLE_COMMAND_MODE_ON";
const std::string System::TOGGLE_COMMAND_MODE_OFF = "TOGGLE_COMMAND_MODE_OFF";
const std::string System::ROTATE_STAGE_LEFT = "ROTATE_STAGE_LEFT";
const std::string System::ROTATE_STAGE_RIGHT = "ROTATE_STAGE_RIGHT";
const std::string System::ROTATE_RELATIVE_UP = "ROTATE_RELATIVE_UP";
const std::string System::ROTATE_RELATIVE_DOWN = "ROTATE_RELATIVE_DOWN";
const std::string System::RUN_MAKE = "RUN_MAKE";
const std::string System::CLEAR_LAST_COMPILED_ERROR_MESSAGES = "CLEAR_LAST_COMPILED_ERROR_MESSAGES";
const std::string System::RUN_PROJECT_TESTS = "RUN_PROJECT_TESTS";
const std::string System::SAVE_CURRENT_STAGE = "SAVE_CURRENT_STAGE";
const std::string System::SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE = "SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE";
const std::string System::SPAWN_COMPONENT_NAVIGATOR = "SPAWN_COMPONENT_NAVIGATOR";
const std::string System::EXECUTE_MAGIC_COMMAND = "EXECUTE_MAGIC_COMMAND";
const std::string System::SPAWN_FILE_NAVIGATOR = "SPAWN_FILE_NAVIGATOR";
//const std::string System::SPAWN_KEYBOARD_INPUTS_MODAL = "SPAWN_KEYBOARD_INPUTS_MODAL";
const std::string System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL = "SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL";
const std::string System::SPAWN_RERUN_OUTPUT_WATCHER = "SPAWN_RERUN_OUTPUT_WATCHER";
const std::string System::SUBMIT_CURRENT_MODAL = "SUBMIT_CURRENT_MODAL";
const std::string System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE = "FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE";



Motion System::dummy_motion;
Hexagon::System::Config System::dummy_config;



