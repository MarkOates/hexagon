


#include <Hexagon/System/System.hpp>


#include <Hexagon/RailsMinitestTestResult.hpp>
#include <Hexagon/RailsMinitestTestResultToCodeMessagePointConverter.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/FullScreenOverlay/Stage.hpp>
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
#include <Hexagon/System/Action/CheckGitSyncAndUpdatePowerbar.hpp>
#include <Hexagon/System/Action/CheckGitLocalStatusAndUpdatePowerbar.hpp>
#include <Hexagon/System/EventController.hpp>
#include <Hexagon/Git/StageEverything.hpp>
#include <Hexagon/Git/CommitStagedWithMessage.hpp>
#include <Hexagon/Git/Pusher.hpp>
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
#include <Hexagon/StageCollectionHelper.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/Hud.hpp>
#include <Hexagon/FileSystemNode.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <Hexagon/ProjectComponentNavigator/Stage.hpp>
#include <Hexagon/LayoutPlacements.hpp>
#include <NcursesArt/ProjectComponentBasenameExtractor.hpp>
#include <NcursesArt/ProjectFilenameGenerator.hpp>
#include <Hexagon/BlastComponentLayoutGenerator.hpp>
#include <Hexagon/LayoutToStagesCreator.hpp>
#include <Hexagon/StageFactory.hpp>

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Blast/StringJoiner.hpp>



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



System::System(ALLEGRO_DISPLAY *display, Hexagon::System::Config &config, Motion &motion)
   : display(display)
   , config(config)
   , motion(motion)
   , save_count(0)
   , search_count(0)
   , files_changed(false)
   , files_committed(true)
   , in_sync_with_remote(true)
   , stages({})
   , camera(0, 0, 0)
   , last_file_navigator_selection("")
   , last_component_navigator_selection("")
   , global_font_resource_filename("Menlo-Regular.ttf")
   , target("")
   , global_font_size(-20)
   , command_mode(false)
   , focused_component_name("")
   , focused_component_name_relative_names()
   , packets()
   , font_bin()
   , hud(display, font_bin)
   , default_camera_stepback(70 + 60)
{
}

void System::initialize()
{
   config.initialize(); // is this redundant?  Should this be initialized before being passed in?

   std::string font_bin_path = config.get_font_bin_path();
   font_bin.set_full_path(font_bin_path);

   hud.set_backfill_color(config.get_backfill_color());
   hud.set_stages(&stages);
   hud.set_global_font_str(get_global_font_str());
   hud.set_draw_packets(true);
   hud.initialize();

   camera.stepback.z = get_default_camera_stepback();

   //process_local_event(EXECUTE_MAGIC_COMMAND);
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

std::string System::get_global_font_str()
{
   std::stringstream result;
   result << global_font_resource_filename << " " << global_font_size;
   return result.str();
}

// retrieval

StageInterface *System::get_frontmost_stage()
{
   Hexagon::StageCollectionHelper stage_collection_helper(&stages);
   return stage_collection_helper.get_frontmost_stage();
}


Hexagon::CodeEditor::Stage *System::get_frontmost_code_editor_stage()
{
   Hexagon::StageCollectionHelper stage_collection_helper(&stages);
   return stage_collection_helper.get_frontmost_code_editor_stage();
}


Hexagon::CodeEditor::Stage *System::get_frontmost_git_commit_message_input_box()
{
   Hexagon::StageCollectionHelper stage_collection_helper(&stages);
   return stage_collection_helper.get_frontmost_git_commit_message_input_box();
}


std::vector<Hexagon::CodeEditor::Stage *> System::get_all_code_editor_stages()
{
   Hexagon::StageCollectionHelper stage_collection_helper(&stages);
   return stage_collection_helper.get_all_code_editor_stages_as_code_editor_stages();
}


int System::get_number_of_code_editor_stages()
{
   Hexagon::StageCollectionHelper stage_collection_helper(&stages);
   return stage_collection_helper.count_code_editor_stages();
}


// inference


bool System::is_current_stage_in_edit_mode()
{
   Hexagon::CodeEditor::Stage *frontmost_stage = get_frontmost_code_editor_stage();
   if (!frontmost_stage) return false;
   return frontmost_stage->get_code_editor_ref().get_mode() == ::CodeEditor::CodeEditor::EDIT;
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
      std::cout << "Warning: attempting to infer if is_current_stage_a_regex_input_box() but no "
                << "frontmost stage exists" << std::endl;
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



bool System::set_frontmost_git_commit_message_input_box_to_submitted_and_pending_destruction()
{
   Hexagon::CodeEditor::Stage *stage = get_frontmost_git_commit_message_input_box();
   if (!stage) return false;
   stage->change_state_to_submitted_and_pending_destruction();
   return true;
}


bool System::write_focused_component_name_to_file()
{
   //std::string hard_coded_project_path = "/Users/markoates/Repos/hexagon/";
   //hard_coded_project_path + "bin/programs/data/tmp/focused_component.txt";
   std::string FOCUSED_COMPONENT_FILENAME = config.get_focused_component_filename();


   std::string focused_component_to_write = focused_component_name;

   bool success = php::file_put_contents(FOCUSED_COMPONENT_FILENAME, focused_component_to_write);
   if (!success)
   {
      std::stringstream error_message;
      error_message << "[System::write_focused_component_name_to_file()] error: could not file_put_contents()";
      throw std::runtime_error(error_message.str());
   }

   return true;
}


bool System::increment_save_count()
{
   save_count++;
   return true;
}


bool System::clear_save_count()
{
   save_count = 0;
   return true;
}


bool System::increment_search_count()
{
   search_count++;
   return true;
}


bool System::clear_search_count()
{
   search_count = 0;
   return true;
}


bool System::set_hud_title_to_focused_component_name()
{
   hud.set_title_text(focused_component_name);
   return true;
}


bool System::set_hud_save_count_to_save_count()
{
   hud.set_save_count(save_count);
   return true;
}


bool System::set_hud_search_count_to_search_count()
{
   hud.set_search_count(search_count);
   return true;
}


bool System::set_hud_packets_to_packets()
{
   hud.set_packets(packets);
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

   float camera_zoomed_out_position = get_default_camera_stepback() + 40;
   //camera.rotation.x = 0.035;
   //float camera_x_rotation_in_zoomed_out_position = 0.035;
   float camera_x_rotation_in_zoomed_out_position = 0.0;

   motion.canimate(&camera.rotation.x,
                   camera.rotation.x,
                   camera_x_rotation_in_zoomed_out_position,
                   al_get_time(),
                   al_get_time()+0.2,
                   interpolator::fast_in,
                   nullptr,
                   nullptr);
   motion.canimate(&camera.position.y,
                   camera.position.y,
                   0.0f,
                   al_get_time(),
                   al_get_time()+0.2,
                   interpolator::fast_in,
                   nullptr,
                   nullptr);
   motion.canimate(&camera.stepback.z,
                   camera.stepback.z,
                   camera_zoomed_out_position,
                   al_get_time(),
                   al_get_time()+0.2,
                   interpolator::fast_in,
                   nullptr,
                   nullptr);
   command_mode = true;
   return true;
}


bool System::reset_camera_to_center()
{
   if (!command_mode) return true;

   float camera_zoomed_in_position = get_default_camera_stepback();
   //camera.rotation.x = 0;

   motion.canimate(&camera.rotation.x,
                   camera.rotation.x,
                   0.0f,
                   al_get_time(),
                   al_get_time()+0.2,
                   interpolator::fast_in,
                   nullptr,
                   nullptr);
   motion.canimate(&camera.rotation.y,
                   camera.rotation.y,
                   0.0f,
                   al_get_time(),
                   al_get_time()+0.2,
                   interpolator::fast_in,
                   nullptr,
                   nullptr);
   motion.canimate(&camera.stepback.z,
                   camera.stepback.z,
                   camera_zoomed_in_position,
                   al_get_time(),
                   al_get_time()+0.2,
                   interpolator::fast_in,
                   nullptr,
                   nullptr);

   command_mode = false;
   return true;
}


bool System::toggle_command_mode_off()
{
   return reset_camera_to_center();
}


static bool unset_focused_state_on_topmost_stage_if_not_already_unfocused(System *system)
{
   if (!system) throw std::runtime_error("Fooobaboab");
   StageInterface *stage = system->get_frontmost_stage();
   if (!stage) return false;

   bool rendered_with_CodeEditor_Renderer = (stage->get_type()
         == StageInterface::CODE_EDITOR
         || stage->get_type() == StageInterface::ONE_LINE_INPUT_BOX
         || stage->get_type() == StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX
      );
   if (rendered_with_CodeEditor_Renderer)
   {
      Hexagon::CodeEditor::Stage *code_editor_stage = static_cast<Hexagon::CodeEditor::Stage *>(stage);
      if (code_editor_stage->get_is_focused()) code_editor_stage->set_is_focused(false);
   }
   if (stage->get_type() == StageInterface::COMPONENT_NAVIGATOR)
   {
      Hexagon::AdvancedComponentNavigator::Stage *advanced_component_navigator_stage =
         static_cast<Hexagon::AdvancedComponentNavigator::Stage *>(stage);
      if (advanced_component_navigator_stage->get_is_focused())
         advanced_component_navigator_stage->set_is_focused(false);
   }
   if (stage->get_type() == StageInterface::MISSING_FILE)
   {
      Hexagon::MissingFile::Stage* missing_file_stage = static_cast<Hexagon::MissingFile::Stage *>(stage);
      if (missing_file_stage->get_is_focused()) missing_file_stage->set_is_focused(false);
   }
   if (stage->get_type() == StageInterface::FILE_NAVIGATOR)
   {
      Hexagon::FileNavigator::Stage *file_navigator_stage = static_cast<Hexagon::FileNavigator::Stage *>(stage);
      if (file_navigator_stage->get_is_focused()) file_navigator_stage->set_is_focused(false);
   }

   return true;
}


static bool set_focused_state_on_topmost_stage_if_not_already_focused(System *system)
{
   if (!system) throw std::runtime_error("Foxxjixjxixxab");
   StageInterface *stage = system->get_frontmost_stage();
   if (!stage) return false;

   bool rendered_with_CodeEditor_Renderer = (stage->get_type()
         == StageInterface::CODE_EDITOR
         || stage->get_type() == StageInterface::ONE_LINE_INPUT_BOX
         || stage->get_type() == StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX
      );
   if (rendered_with_CodeEditor_Renderer)
   {
      Hexagon::CodeEditor::Stage *code_editor_stage = static_cast<Hexagon::CodeEditor::Stage *>(stage);
      if (!code_editor_stage->get_is_focused()) code_editor_stage->set_is_focused(true);
   }
   if (stage->get_type() == StageInterface::COMPONENT_NAVIGATOR)
   {
      Hexagon::AdvancedComponentNavigator::Stage *advanced_component_navigator_stage =
         static_cast<Hexagon::AdvancedComponentNavigator::Stage *>(stage);
      if (!advanced_component_navigator_stage->get_is_focused())
         advanced_component_navigator_stage->set_is_focused(true);
   }
   if (stage->get_type() == StageInterface::MISSING_FILE)
   {
      Hexagon::MissingFile::Stage* missing_file_stage = static_cast<Hexagon::MissingFile::Stage *>(stage);
      if (!missing_file_stage->get_is_focused()) missing_file_stage->set_is_focused(true);
   }
   if (stage->get_type() == StageInterface::FILE_NAVIGATOR)
   {
      Hexagon::FileNavigator::Stage *file_navigator_stage = static_cast<Hexagon::FileNavigator::Stage *>(stage);
      if (!file_navigator_stage->get_is_focused()) file_navigator_stage->set_is_focused(true);
   }

   return true;
}


bool System::rotate_stage_right_and_update_focused_state_on_changed_stages()
{
   if (stages.empty())
   {
      std::cout << "Warning: attempting to rotate_stage_right() but no frontmost stage exists" << std::endl;
      return false;
   }

   unset_focused_state_on_topmost_stage_if_not_already_unfocused(this);
   std::rotate(stages.begin(), stages.begin() + 1, stages.end());
   set_focused_state_on_topmost_stage_if_not_already_focused(this);
   return true;
}


bool System::rotate_stage_left_and_update_focused_state_on_changed_stages()
{
   if (stages.empty())
   {
      std::cout << "Warning: attempting to rotate_stage_right() but no frontmost stage exists" << std::endl;
      return false;
   }

   unset_focused_state_on_topmost_stage_if_not_already_unfocused(this);
   std::rotate(stages.rbegin(), stages.rbegin() + 1, stages.rend());
   set_focused_state_on_topmost_stage_if_not_already_focused(this);
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
      std::cout << "Warning: attempting to center_camera_on_frontmost_stage() but no frontmost stage exists"
                << std::endl;
      return false;
   }

   placement3d &place = frontmost_stage->get_place();
   vec3d target = place.position;
   //camera.position = target;

   motion.cmove_to(&camera.position.x, target.x, 0.2, interpolator::double_fast_in);
   motion.cmove_to(&camera.position.y, target.y, 0.2, interpolator::double_fast_in);
   motion.cmove_to(&camera.position.z, target.z, 0.2, interpolator::double_fast_in);

   motion.cmove_to(&camera.rotation.x, 0.0f, 0.2, interpolator::double_fast_in);
   motion.cmove_to(&camera.rotation.y, 0.0f, 0.2, interpolator::double_fast_in);
   motion.cmove_to(&camera.rotation.z, 0.0f, 0.2, interpolator::double_fast_in);

   return true;
}


bool System::run_project_tests()
{
   Hexagon::CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
   if (!stage) throw std::runtime_error("cannot run tests on current stage -- not a stage stage");

   std::string test_output = RailsMinitestTestRunner(stage->get_code_editor_ref().get_filename()).run();
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
   stage->get_code_editor_ref().clear_code_message_points();
   stage->get_code_editor_ref().set_code_message_points({ code_message_points });

   return true;
}


bool System::save_frontmost_code_editor_stage()
{
   Hexagon::CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
   if (!stage) throw std::runtime_error("Cannot save_frontmost_code_editor_stage; current stage is not a stage stage");

   stage->get_code_editor_ref().save_file_and_touch_if_symlink();
   stage->get_code_editor_ref().refresh_git_modified_line_numbers();
   process_local_event(REMOVE_FILE_IS_UNSAVED_NOTIFICATION);

   if (stage->get_type() == StageInterface::CODE_EDITOR)
   {
      increment_save_count();
      set_hud_save_count_to_save_count();
      check_git_local_status_and_update_powerbar();
   }

   return true;
}


bool System::increase_font_size()
{
   global_font_size -= 1;
   return true;
}


bool System::decrease_font_size()
{
   global_font_size += 1;
   return true;
}


bool System::refresh_regex_hilights_on_frontmost_stage()
{
   Hexagon::CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
   if (!stage)
   {
      std::stringstream error_message;
      error_message << "Cannot refresh_regex_hilights_on_frontmost_stage; there is no frontmost code editor stage";
      throw std::runtime_error(error_message.str());
   }
   stage->get_code_editor_ref().refresh_regex_message_points();
   return true;
}


bool System::refresh_regex_hilights_on_all_code_editor_stages()
{
   std::vector<Hexagon::CodeEditor::Stage *> all_code_editor_stages = get_all_code_editor_stages();
   for (auto &code_editor_stage : all_code_editor_stages)
   {
      code_editor_stage->get_code_editor_ref().refresh_regex_message_points();
   }
   increment_search_count();
   set_hud_search_count_to_search_count();
   return true;
}


bool System::refresh_git_modified_line_numbers_on_all_code_editor_stages()
{
   std::vector<Hexagon::CodeEditor::Stage *> all_code_editor_stages = get_all_code_editor_stages();
   for (auto &code_editor_stage : all_code_editor_stages)
   {
      code_editor_stage->get_code_editor_ref().refresh_git_modified_line_numbers();
   }
   return true;
}


bool System::set_regex_input_box_modal_to_insert_mode()
{
   // TODO: this function also handles git_commit_message modal, too
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return false;
   frontmost_stage->process_local_event(CodeEditor::EventController::SET_INSERT_MODE);
   return true;
}


bool System::spawn_regex_input_box_modal()
{
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *stage = stage_factory.create_regex_input_box_modal();

   stages.push_back(stage);

   motion.cmove_to(&camera.rotation.x, 0.08f, 0.5f, interpolator::tripple_fast_in);
   motion.cmove_to(&camera.position.y, -70.0f, 0.5f, interpolator::tripple_fast_in);

   return true;
}


bool System::spawn_git_commit_message_input_box_modal()
{
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *stage = stage_factory.create_git_commit_message_box();

   stages.push_back(stage);

   motion.cmove_to(&camera.rotation.x, -0.12f, 0.5f, interpolator::tripple_fast_in);
   motion.cmove_to(&camera.position.y, 140.0f, 0.5f, interpolator::tripple_fast_in);

   return true;
}


bool System::spawn_component_navigator()
{
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *stage = stage_factory.create_advanced_component_navigator();

   stages.push_back(stage);

   motion.cmove_to(&camera.rotation.y, 0.08f, 0.5f, interpolator::tripple_fast_in);
   //motion.cmove_to(&camera.rotation.x, -0.08f, 0.5f, interpolator::tripple_fast_in);
   motion.cmove_to(&camera.rotation.x, -0.12f, 0.5f, interpolator::tripple_fast_in);
   motion.cmove_to(&camera.position.y, 140.0f, 0.5f, interpolator::tripple_fast_in);

   return true;
}


bool System::spawn_red_overlay()
{
   Hexagon::FullScreenOverlay::Stage *red_overlay = new Hexagon::FullScreenOverlay::Stage;
   stages.push_back(red_overlay);
   return true;
}


bool System::spawn_file_navigator()
{
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *stage = stage_factory.create_file_navigator();

   stages.push_back(stage);

   return true;
}


bool System::spawn_file_navigator_from_last_file_navigator_folder_selection()
{
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   StageInterface *stage = stage_factory.create_file_navigator(last_file_navigator_selection);

   stages.push_back(stage);

   return true;
}


bool System::add_file_is_unsaved_notification()
{
   add_notification(NOTIFICATION_FILE_IS_UNSAVED);
   return true;
}


bool System::remove_file_is_unsaved_notification()
{
   remove_notification(NOTIFICATION_FILE_IS_UNSAVED);
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


#include <Blast/FileExistenceChecker.hpp>
#include <allegro_flare/useful.h>
bool System::execute_magic_command()
{
   focused_component_name = "- Untitled -";
   set_hud_title_to_focused_component_name();

   destroy_all_code_editor_stages();


   std::vector<std::string> filenames = {
      "/Users/markoates/Repos/hexagon/include/Hexagon/System/System.hpp",
      "/Users/markoates/Repos/hexagon/src/Hexagon/System/System.cpp",
   };


   Hexagon::StageFactory stage_factory(&config, &font_bin);
   float width = 1200;
   float display_default_height = 900;

   int i;
   for (i=0; i<filenames.size(); i++)
   {
      std::string filename = filenames[i];
      bool file_present = true;
      if (!Blast::FileExistenceChecker(filename).exists()) file_present = false;
      //if (!file_contents.empty())
      {
        placement3d place(0, 0, 0);
        place.size = vec3d(width, display_default_height, 0.0);

        place.position = vec3d(width*i, 0.0, 0.0);
        place.align = vec3d(0.5, 0.5, 0.0);
        place.scale = vec3d(0.45, 0.45, 0.0);

        StageInterface *stage = nullptr;

        if (file_present)
        {
           std::vector<std::string> file_contents = {};
           ::read_file(file_contents, filename);
           std::string single_line = Blast::StringJoiner(file_contents, "\n").join();
           stage = new Hexagon::AdvancedCodeEditor::Stage(&font_bin, 120, 70); //(::CodeEditor::CodeEditor{filename});
           Hexagon::AdvancedCodeEditor::Stage *ace_stage = static_cast<Hexagon::AdvancedCodeEditor::Stage*>(stage);
           ace_stage->initialize();
           ace_stage->set_content(single_line);

           //stage = ace_stage;
        }
        else
        {
            stage = stage_factory.create_missing_file();
        }

        stage->set_place(place);
        stages.push_back(stage);
      }
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


bool System::jump_to_next_or_nearest_code_point_on_stage()
{
   Hexagon::CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
   if (!stage) return false;
   stage->process_local_event(CodeEditor::EventController::JUMP_TO_NEXT_OR_NEAREST_CODE_POINT);
   return true;
}


bool System::clear_last_compiled_error_messages()
{
   ::clear_last_compiled_error_messages();
   return true;
}


bool System::enable_drawing_info_overlays_on_all_code_editor_stages()
{
   std::vector<Hexagon::CodeEditor::Stage *> code_editor_stages = System::get_all_code_editor_stages();
   for (auto &code_editor_stage : code_editor_stages)
   {
      code_editor_stage->get_code_editor_ref().enable_drawing_info_overlay();
   }
   return true;
}


bool System::disable_drawing_info_overlays_on_all_code_editor_stages()
{
   std::vector<Hexagon::CodeEditor::Stage *> code_editor_stages = System::get_all_code_editor_stages();
   for (auto &code_editor_stage : code_editor_stages)
   {
      code_editor_stage->get_code_editor_ref().disable_drawing_info_overlay();
   }
   return true;
}


bool System::check_git_sync_and_update_powerbar()
{
   std::string repo_name = "blast";
   std::string repos_directory = "~/Repos";
   Hexagon::Powerbar::Powerbar* powerbar = nullptr;
   Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar action(repo_name, repos_directory, powerbar);

   return action.execute();
}


bool System::check_git_local_status_and_update_powerbar()
{
   //std::string repo_name = "blast";
   //std::string repos_directory = "~/Repos";
   Hexagon::Powerbar::Powerbar* powerbar = &hud.get_powerbar_ref();
   std::string current_project_directory = get_default_navigator_directory();
   Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar action(current_project_directory, powerbar);
   return action.execute();
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
   Hexagon::AdvancedComponentNavigator::Stage *component_navigator =
      static_cast<Hexagon::AdvancedComponentNavigator::Stage *>(frontmost_stage_interface);

   std::string current_component_navigator_selection =
      component_navigator->get_component_ref().get_current_selection_label_or_empty_string();

   last_component_navigator_selection = current_component_navigator_selection;
   return true;
}


bool System::push_project_navigator_selection()
{
   StageInterface *frontmost_stage_interface = get_frontmost_stage();
   if (!frontmost_stage_interface || !(frontmost_stage_interface->get_type() == StageInterface::COMPONENT_NAVIGATOR))
   {
      std::stringstream error_message;
      std::string function_name = "push_project_navigator_selection";
      error_message << "Could not "
                    << function_name
                    << ": Either the frontmost_stage_interface is a nullptr OR is not "
                    << "of type StageInterface::COMPONENT_NAVIGATOR."
                    << std::endl;
      throw std::runtime_error(error_message.str().c_str());
   }
   Hexagon::ProjectComponentNavigator::Stage *project_navigator =
      static_cast<Hexagon::ProjectComponentNavigator::Stage *>(frontmost_stage_interface);

   std::string current_project_navigator_selection =
      project_navigator->get_component_ref().get_current_selection_label_or_empty_string();

   last_project_navigator_selection = current_project_navigator_selection;
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
   std::string filename = last_file_navigator_selection;

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
      ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 1.0f};
      ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};

      Hexagon::StageFactory stage_factory(&config, &font_bin);
      Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action(
         filename,
         get_display_default_width(),
         get_display_default_height(),
         get_default_code_editor_stage_width(),
         text_color,
         backfill_color,
         &stages,
         &stage_factory
         );

      action.execute();
   }

   return true;
}


bool System::destroy_all_code_editor_stages()
{
   Hexagon::System::Action::DestroyAllCodeEditorStages action(stages);
   return action.managed_execute();
}


bool System::create_stages_from_layout_of_last_component_navigator_selection()
{
   if (last_component_navigator_selection.empty())
   {
      std::stringstream error_message;
      error_message << "[" << typeid(*this).name() << "::" << __FUNCTION__ << " error:]"
                    << " guard not met: last_component_navigator_selection cannot be empty";
      throw std::runtime_error(error_message.str());
      return false;
   }

   std::string project_directory = get_default_navigator_directory();
   std::string component_name = last_component_navigator_selection;

   std::cout << " ---- CREATING project_dir:" << project_directory << std::endl;
   std::cout << "      CREATING component_naem:" << component_name << std::endl;

   Hexagon::BlastComponentLayoutGenerator component_layout_generator(project_directory, component_name);
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   Hexagon::Layout layout = component_layout_generator.generate();
   Hexagon::LayoutToStagesCreator layout_to_stages_creator(&stages, &stage_factory, &layout, &font_bin);
   layout_to_stages_creator.create();

   focused_component_name = last_component_navigator_selection;
   set_hud_title_to_focused_component_name();
   write_focused_component_name_to_file();

   return true;
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
      std::cout << "cannot create_two_or_three_split_layout_from_last_component_navigator_selection "
                << "because the component \"" << component.get_name() << "\" "
                << "neither has a header/source combo nor a quintessence or test file."
                << std::endl;
      return true;
   }
}


bool System::create_layout_from_last_project_navigator_selection()
{
   return true;
}


bool System::create_three_split_from_last_component_navigator_selection()
{
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   Blast::Project::Component component(last_component_navigator_selection, get_default_navigator_directory());
   Hexagon::System::Action::CreateThreeSplitFromComponent action(
      get_default_navigator_directory(),
      component,
      stages,
      &stage_factory,
      get_display_default_width(),
      get_display_default_height(),
      get_default_code_editor_stage_width(),
      config.get_base_text_color(),
      config.get_backfill_color()
   );
   return action.managed_execute();
}


bool System::attempt_to_create_stage_from_last_component_navigator_selection()
{
   Hexagon::StageFactory stage_factory(&config, &font_bin);
   Hexagon::System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection action(
         get_default_navigator_directory(),
         last_component_navigator_selection,
         get_display_default_width(),
         get_display_default_height(),
         stages,
         &stage_factory,
         get_default_code_editor_stage_width(),
         config.get_base_text_color(),
         config.get_backfill_color()
      );
   return action.managed_execute();
}


bool System::set_search_regex_expression_on_all_code_editor_stages_to_regex_temp_file_contents()
{
   // get regex expression input from file named REGEX_TEMP_FILENAME
   std::vector<std::string> regex_input_file_lines;
   if (!read_file(regex_input_file_lines, REGEX_TEMP_FILENAME) || regex_input_file_lines.size() == 0)
      throw std::runtime_error("cannot open expected REGEX_TEMP_FILENAME file for input, or is empty");

   std::string regex_expression = regex_input_file_lines[0];

   std::vector<Hexagon::CodeEditor::Stage *> stages = get_all_code_editor_stages();
   for (auto &stage : stages)
   {
      stage->get_code_editor_ref().set_search_regex_expression(regex_expression);
   }

   return true;
}


bool
System::commit_all_files_with_last_git_commit_message_from_regex_temp_file_contents_and_append_packet_and_clear_scores()
{
   // get regex expression input from file named REGEX_TEMP_FILENAME
   std::vector<std::string> regex_input_file_lines;
   if (!read_file(regex_input_file_lines, REGEX_TEMP_FILENAME) || regex_input_file_lines.size() == 0)
      throw std::runtime_error("cannot open expected REGEX_TEMP_FILENAME file for input, or is empty");

   std::string commit_message = regex_input_file_lines[0];
   std::string current_project_directory = get_default_navigator_directory();

   Hexagon::Git::StageEverything stage_everything(current_project_directory);
   stage_everything.stage_everything();

   Hexagon::Git::CommitStagedWithMessage commit_staged_with_message(current_project_directory, commit_message);
   commit_staged_with_message.commit();

   // append packet to packets
   Hexagon::Packet new_packet_to_append(search_count, save_count);
   packets.push_back(new_packet_to_append);

   // refresh hud packets
   set_hud_packets_to_packets();

   // clear scores
   clear_search_count();
   clear_save_count();

   // refresh the cleared scores on the hud
   set_hud_search_count_to_search_count();
   set_hud_save_count_to_save_count();
   check_git_local_status_and_update_powerbar();

   return true;
}


bool System::push_to_git_remote()
{
   std::string current_project_directory = get_default_navigator_directory();
   Hexagon::Git::Pusher git_pusher(current_project_directory);

   git_pusher.push();

   return true;
}


bool System::submit_current_modal()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return false;

   switch (frontmost_stage->get_type())
   {
   case StageInterface::ONE_LINE_INPUT_BOX:
      process_local_event(SAVE_FRONTMOST_CODE_EDITOR_STAGE);

      process_local_event(DESTROY_TOPMOST_STAGE);
      process_local_event(SET_SEARCH_REGEX_EXPRESSION_ON_ALL_CODE_EDITOR_STAGES_TO_REGEX_TEMP_FILE_CONTENTS);
      process_local_event(REFRESH_REGEX_HILIGHTS_ON_ALL_CODE_EDITOR_STAGES);
      //process_local_event(JUMP_TO_NEXT_OR_NEAREST_CODE_POINT_ON_STAGE);
      //process_local_event(OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE);
      break;
   case StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX:
      //process_local_event(SET_FRONTMOST_GIT_COMMIT_MESSAGE_INPUT_BOX_TO_SUBMITTED_AND_PENDING_DESTRUCTION);
      process_local_event(SAVE_FRONTMOST_CODE_EDITOR_STAGE);
      process_local_event(DESTROY_TOPMOST_STAGE);
      process_local_event(COMMIT_ALL_FILES_WITH_LAST_GIT_COMMIT_MESSAGE_FROM_REGEX_TEMP_FILE_CONTENTS_AND_APPEND_PACKET_AND_CLEAR_SCORES);
      process_local_event(PUSH_TO_GIT_REMOTE);
      process_local_event(REFRESH_GIT_MODIFIED_LINE_NUMBERS_ON_ALL_CODE_EDITOR_STAGES);
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
      //process_local_event(CREATE_STAGES_FROM_LAYOUT_OF_LAST_COMPONENT_NAVIGATOR_SELECTION);
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

   Hexagon::StageFactory stage_factory(&config, &font_bin);
   Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action(
      config_filename,
      al_get_display_width(display),
      al_get_display_height(display),
      get_default_code_editor_stage_width(),
      config.get_base_text_color(),
      config.get_backfill_color(),
      &stages,
      &stage_factory
      );

   return action.managed_execute();
}


void System::process_local_event(std::string event_name)
{
   Hexagon::System::EventController event_controller(this);
   event_controller.process_local_event(event_name);
   return;
}


void System::process_event(ALLEGRO_EVENT &event)
{
   Hexagon::System::EventController event_controller(this);
   event_controller.process_event(event);
   return;
}


const std::string System::SET_FRONTMOST_GIT_COMMIT_MESSAGE_INPUT_BOX_TO_SUBMITTED_AND_PENDING_DESTRUCTION =
   "SET_FRONTMOST_GIT_COMMIT_MESSAGE_INPUT_BOX_TO_SUBMITTED_AND_PENDING_DESTRUCTION";
const std::string System::OPEN_HEXAGON_CONFIG_FILE = "OPEN_HEXAGON_CONFIG_FILE";
const std::string System::WRITE_FOCUSED_COMPONENT_NAME_TO_FILE = "WRITE_FOCUSED_COMPONENT_NAME_TO_FILE";
const std::string System::ADD_FILE_IS_UNSAVED_NOTIFICATION = "ADD_FILE_IS_UNSAVED_NOTIFICATION";
const std::string System::REMOVE_FILE_IS_UNSAVED_NOTIFICATION = "REMOVE_FILE_IS_UNSAVED_NOTIFICATION";
const std::string System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION = "ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION";
const std::string System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION = "ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION = "SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION";
const std::string System::CREATE_THREE_SPLIT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION = "CREATE_THREE_SPLIT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::CREATE_STAGES_FROM_LAYOUT_OF_LAST_COMPONENT_NAVIGATOR_SELECTION =
   "CREATE_STAGES_FROM_LAYOUT_OF_LAST_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION = "CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION";
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
const std::string System::JUMP_TO_NEXT_OR_NEAREST_CODE_POINT_ON_STAGE = "JUMP_TO_NEXT_OR_NEAREST_CODE_POINT_ON_STAGE";
const std::string System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE = "OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE";
const std::string System::ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES =
   "ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES";
const std::string System::DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES =
   "DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES";
const std::string System::PUSH_FILE_NAVIGATOR_SELECTION = "PUSH_FILE_NAVIGATOR_SELECTION";
const std::string System::PUSH_COMPONENT_NAVIGATOR_SELECTION = "PUSH_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::REFRESH_REGEX_HILIGHTS_ON_FRONTMOST_STAGE = "REFRESH_REGEX_HILIGHTS_ON_FRONTMOST_STAGE";
const std::string System::REFRESH_REGEX_HILIGHTS_ON_ALL_CODE_EDITOR_STAGES =
   "REFRESH_REGEX_HILIGHTS_ON_ALL_CODE_EDITOR_STAGES";
const std::string System::REFRESH_GIT_MODIFIED_LINE_NUMBERS_ON_ALL_CODE_EDITOR_STAGES =
   "REFRESH_GIT_MODIFIED_LINE_NUMBERS_ON_ALL_CODE_EDITOR_STAGES";
const std::string System::SET_SEARCH_REGEX_EXPRESSION_ON_ALL_CODE_EDITOR_STAGES_TO_REGEX_TEMP_FILE_CONTENTS =
   "SET_SEARCH_REGEX_EXPRESSION_ON_ALL_CODE_EDITOR_STAGES_TO_REGEX_TEMP_FILE_CONTENTS";
const std::string System::TOGGLE_COMMAND_MODE_ON = "TOGGLE_COMMAND_MODE_ON";
const std::string System::TOGGLE_COMMAND_MODE_OFF = "TOGGLE_COMMAND_MODE_OFF";
const std::string System::RESET_CAMERA_TO_CENTER = "RESET_CAMERA_TO_CENTER";
const std::string System::ROTATE_STAGE_LEFT = "ROTATE_STAGE_LEFT";
const std::string System::ROTATE_STAGE_RIGHT = "ROTATE_STAGE_RIGHT";
const std::string System::ROTATE_RELATIVE_UP = "ROTATE_RELATIVE_UP";
const std::string System::ROTATE_RELATIVE_DOWN = "ROTATE_RELATIVE_DOWN";
const std::string System::RUN_MAKE = "RUN_MAKE";
const std::string System::CLEAR_LAST_COMPILED_ERROR_MESSAGES = "CLEAR_LAST_COMPILED_ERROR_MESSAGES";
const std::string System::RUN_PROJECT_TESTS = "RUN_PROJECT_TESTS";
const std::string System::SAVE_FRONTMOST_CODE_EDITOR_STAGE = "SAVE_FRONTMOST_CODE_EDITOR_STAGE";
const std::string System::SPAWN_COMPONENT_NAVIGATOR = "SPAWN_COMPONENT_NAVIGATOR";
const std::string System::EXECUTE_MAGIC_COMMAND = "EXECUTE_MAGIC_COMMAND";
const std::string System::SPAWN_FILE_NAVIGATOR = "SPAWN_FILE_NAVIGATOR";
const std::string System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL = "SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL";
const std::string System::SPAWN_GIT_COMMIT_MESSAGE_INPUT_BOX_MODAL = "SPAWN_GIT_COMMIT_MESSAGE_INPUT_BOX_MODAL";
const std::string System::SUBMIT_CURRENT_MODAL = "SUBMIT_CURRENT_MODAL";
const std::string System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE = "FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE";
const std::string System::CHECK_GIT_SYNC_AND_UPDATE_POWERBAR = "CHECK_GIT_SYNC_AND_UPDATE_POWERBAR";
const std::string System::COMMIT_ALL_FILES_WITH_LAST_GIT_COMMIT_MESSAGE_FROM_REGEX_TEMP_FILE_CONTENTS_AND_APPEND_PACKET_AND_CLEAR_SCORES =
   "COMMIT_ALL_FILES_WITH_LAST_GIT_COMMIT_MESSAGE_FROM_REGEX_TEMP_FILE_CONTENTS_AND_APPEND_PACKET_AND_CLEAR_SCORES";
const std::string System::PUSH_TO_GIT_REMOTE = "PUSH_TO_GIT_REMOTE";
const std::string System::CREATE_LAYOUT_FROM_LAST_PROJECT_NAVIGATOR_SELECTION =
   "CREATE_LAYOUT_FROM_LAST_PROJECT_NAVIGATOR_SELECTION";




Motion System::dummy_motion;
Hexagon::System::Config System::dummy_config;



