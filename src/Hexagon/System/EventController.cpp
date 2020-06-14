

#include <Hexagon/System/EventController.hpp>
#include <Hexagon/shared_globals.hpp>
#include <map>
#include <string>
#include <functional>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace System
{


EventController::EventController(::System* system)
   : system(system)
{
}


EventController::~EventController()
{
}


void EventController::process_local_event(std::string event_name)
{
if (!(system))
   {
      std::stringstream error_message;
      error_message << "EventController" << "::" << "process_local_event" << ": error: " << "guard \"system\" not met";
      throw std::runtime_error(error_message.str());
   }
std::map<std::string, std::function<bool(::System&)>> event_function_mapping = {
   {
      ::System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION,
      &::System::attempt_to_create_stage_from_last_file_navigator_selection,
   }
};

try
{
   bool executed = false;

   if (event_name == ::System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION)
   {
      system->attempt_to_create_stage_from_last_file_navigator_selection();
      executed = true;
   }
   else if (event_name == ::System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION)
   {
      system->attempt_to_create_stage_from_last_component_navigator_selection();
      executed = true;
   }
   else if (event_name == ::System::SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION)
   {
      system->spawn_file_navigator_from_last_file_navigator_folder_selection();
      executed = true;
   }
   else if (event_name == ::System::CREATE_THREE_SPLIT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION)
   {
      system->create_three_split_from_last_component_navigator_selection();
      executed = true;
   }
   else if (event_name == ::System::CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION) { system->create_two_or_three_split_layout_from_last_component_navigator_selection(); executed = true; }
   else if (event_name == ::System::CLEAR_RERUN_OUTPUT_WATCHERS) { system->clear_rerun_output_watchers(); executed = true; }
   else if (event_name == ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE) { system->center_camera_on_frontmost_stage(); executed = true; }
   else if (event_name == ::System::DESTROY_TOPMOST_STAGE) { system->destroy_topmost_stage(); executed = true; }
   else if (event_name == ::System::OPEN_HEXAGON_CONFIG_FILE) { system->open_hexagon_config_file(); executed = true; }
   else if (event_name == ::System::DESTROY_ALL_CODE_EDITOR_STAGES) { system->destroy_all_code_editor_stages(); executed = true; }
   else if (event_name == ::System::ESCAPE_CURRENT_MODAL) { system->escape_current_modal(); executed = true; }
   else if (event_name == ::System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE) { system->jump_to_next_code_point_on_stage(); executed = true; }
   else if (event_name == ::System::JUMP_TO_NEXT_OR_NEAREST_CODE_POINT_ON_STAGE)
   {
      system->jump_to_next_or_nearest_code_point_on_stage();
      executed = true;
   }
   else if (event_name == ::System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE) { system->offset_first_line_to_vertically_center_cursor_on_stage(); executed = true; }
   else if (event_name == ::System::ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES) {
      system->enable_drawing_info_overlays_on_all_code_editor_stages();
      executed = true;
   }
   else if (event_name == ::System::DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES)
   {
      system->disable_drawing_info_overlays_on_all_code_editor_stages();
      executed = true;
   }
   else if (event_name == ::System::PUSH_FILE_NAVIGATOR_SELECTION) { system->push_file_navigator_selection(); executed = true; }
   else if (event_name == ::System::PUSH_COMPONENT_NAVIGATOR_SELECTION) { system->push_component_navigator_selection(); executed = true; }
   else if (event_name == ::System::REFRESH_REGEX_HILIGHTS_ON_FRONTMOST_STAGE)
   {
      system->refresh_regex_hilights_on_frontmost_stage(); executed = true;
   }
   else if (event_name == ::System::REFRESH_REGEX_HILIGHTS_ON_ALL_CODE_EDITOR_STAGES)
   {
      system->refresh_regex_hilights_on_all_code_editor_stages();
      executed = true;
   }
   else if (event_name == ::System::REFRESH_GIT_MODIFIED_LINE_NUMBERS_ON_ALL_CODE_EDITOR_STAGES)
   {
      system->refresh_git_modified_line_numbers_on_all_code_editor_stages();
      executed = true;
   }
   else if (event_name == ::System::SET_SEARCH_REGEX_EXPRESSION_ON_ALL_CODE_EDITOR_STAGES_TO_REGEX_TEMP_FILE_CONTENTS)
   {
      system->set_search_regex_expression_on_all_code_editor_stages_to_regex_temp_file_contents();
      executed = true;
   }
   else if (event_name == ::System::REFRESH_RERUN_OUTPUT_WATCHERS) { system->refresh_rerun_output_watchers(); executed = true; }
   else if (event_name == ::System::INCREASE_FONT_SIZE) { system->increase_font_size(); executed = true; }
   else if (event_name == ::System::DECREASE_FONT_SIZE) { system->decrease_font_size(); executed = true; }
   else if (event_name == ::System::ADD_FILE_IS_UNSAVED_NOTIFICATION) { system->add_file_is_unsaved_notification(); executed = true; }
   else if (event_name == ::System::WRITE_FOCUSED_COMPONENT_NAME_TO_FILE) { system->write_focused_component_name_to_file(); executed = true; }
   else if (event_name == ::System::REMOVE_FILE_IS_UNSAVED_NOTIFICATION) { system->remove_file_is_unsaved_notification(); executed = true; }
   else if (event_name == ::System::TOGGLE_COMMAND_MODE_ON) { system->toggle_command_mode_on(); executed = true; }
   else if (event_name == ::System::TOGGLE_COMMAND_MODE_OFF) { system->toggle_command_mode_off(); executed = true; }
   else if (event_name == ::System::ROTATE_STAGE_LEFT) { system->rotate_stage_left(); executed = true; }
   else if (event_name == ::System::ROTATE_STAGE_RIGHT) { system->rotate_stage_right(); executed = true; }
   else if (event_name == ::System::ROTATE_RELATIVE_UP) { system->rotate_relative_up(); executed = true; }
   else if (event_name == ::System::ROTATE_RELATIVE_DOWN) { system->rotate_relative_down(); executed = true; }
   else if (event_name == ::System::RUN_MAKE) { system->run_make(); executed = true; }
   else if (event_name == ::System::CLEAR_LAST_COMPILED_ERROR_MESSAGES) { system->clear_last_compiled_error_messages(); executed = true; }
   else if (event_name == ::System::RUN_PROJECT_TESTS) { system->run_project_tests(); executed = true; }
   else if (event_name == ::System::SAVE_FRONTMOST_CODE_EDITOR_STAGE) { system->save_frontmost_code_editor_stage(); executed = true; }
   else if (event_name == ::System::SET_FOCUSED_COMPONENT_NAME_TO_TOPMOST_RELATIVE) { system->set_focused_component_name_to_topmost_relative(); executed = true; }
   else if (event_name == ::System::SPAWN_COMPONENT_NAVIGATOR) { system->spawn_component_navigator(); executed = true; }
   else if (event_name == ::System::EXECUTE_MAGIC_COMMAND) { system->execute_magic_command(); executed = true; }
   else if (event_name == ::System::SPAWN_FILE_NAVIGATOR) { system->spawn_file_navigator(); executed = true; }
   else if (event_name == ::System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL) { system->spawn_regex_input_box_modal(); executed = true; }
   else if (event_name == ::System::SPAWN_GIT_COMMIT_MESSAGE_INPUT_BOX_MODAL)
   {
      system->spawn_git_commit_message_input_box_modal();
      executed = true;
   }
   else if (event_name == ::System::SPAWN_RERUN_OUTPUT_WATCHER) { system->spawn_rerun_output_watcher(); executed = true; }
   else if (event_name == ::System::SUBMIT_CURRENT_MODAL) { system->submit_current_modal(); executed = true; }
   else if (event_name == ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE) { system->fx__play_focus_animation_on_frontmost_stage(); executed = true; }
   else if (event_name == ::System::CHECK_GIT_SYNC_AND_UPDATE_POWERBAR)
   {
      system->check_git_sync_and_update_powerbar();
      executed = true;
   }
   else if (event_name == ::System::COMMIT_ALL_FILES_WITH_LAST_GIT_COMMIT_MESSAGE_FROM_REGEX_TEMP_FILE_CONTENTS)
   {
      system->commit_all_files_with_last_git_commit_message_from_regex_temp_file_contents();
      executed = true;
   }
   else if (event_name == ::System::PUSH_TO_GIT_REMOTE)
   {
      system->push_to_git_remote();
      executed = true;
   }

   if (!executed) std::cout << "???? cannot execute "" << event_name << "".  It does not exist." << std::endl;
}
catch (const std::exception &exception)
{
   std::cout << ">BOOM< cannot execute \"" << event_name << "\".  The following exception occurred: " << exception.what() << std::endl;
   // add the thing right here
   std::stringstream error_message;
   error_message << "An exception was thrown: \"" << exception.what() << "\"";
   add_notification(error_message.str());
}
return;

}
} // namespace System
} // namespace Hexagon


