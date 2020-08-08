

#include <Hexagon/System/EventController.hpp>
#include <Hexagon/shared_globals.hpp>
#include <map>
#include <string>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace System
{


EventController::EventController(::System* system, std::map<std::string, std::function<bool(::System&)>> function_mapping)
   : system(system)
   , function_mapping(function_mapping)
{
}


EventController::~EventController()
{
}


ALLEGRO_EVENT& EventController::dummy_ALLEGRO_EVENT()
{
static ALLEGRO_EVENT ev;
return ev;

}

std::map<std::string, std::function<bool(::System&)>> EventController::get_default_function_mapping()
{
std::map<std::string, std::function<bool(::System&)>> default_function_mapping = {
   {
      ::System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION,
      &::System::attempt_to_create_stage_from_last_file_navigator_selection,
   },
   {
      ::System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION,
      &::System::attempt_to_create_stage_from_last_component_navigator_selection,
   },
   {
      ::System::SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION,
      &::System::spawn_file_navigator_from_last_file_navigator_folder_selection,
   },
   {
      ::System::CREATE_STAGES_FROM_LAYOUT_OF_LAST_COMPONENT_NAVIGATOR_SELECTION,
      &::System::create_stages_from_layout_of_last_component_navigator_selection,
   },
   {
      ::System::CREATE_THREE_SPLIT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION,
      &::System::create_three_split_from_last_component_navigator_selection,
   },
   {
      ::System::CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION,
      &::System::create_two_or_three_split_layout_from_last_component_navigator_selection,
   },
   {
      ::System::CREATE_RAILS_RESOURCE_LAYOUT,
      &::System::create_rails_resource_layout,
   },
   {
      ::System::CLEAR_RERUN_OUTPUT_WATCHERS,
      &::System::clear_rerun_output_watchers,
   },
   {
      ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
      &::System::center_camera_on_frontmost_stage,
   },
   {
      ::System::DESTROY_TOPMOST_STAGE,
      &::System::destroy_topmost_stage,
   },
   {
      ::System::OPEN_HEXAGON_CONFIG_FILE,
      &::System::open_hexagon_config_file,
   },
   {
      ::System::DESTROY_ALL_CODE_EDITOR_STAGES,
      &::System::destroy_all_code_editor_stages,
   },
   {
      ::System::ESCAPE_CURRENT_MODAL,
      &::System::escape_current_modal,
   },
   {
      ::System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE,
      &::System::jump_to_next_code_point_on_stage,
   },
   {
      ::System::JUMP_TO_NEXT_OR_NEAREST_CODE_POINT_ON_STAGE,
      &::System::jump_to_next_or_nearest_code_point_on_stage,
   },
   {
      ::System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE,
      &::System::offset_first_line_to_vertically_center_cursor_on_stage,
   },
   {
      ::System::ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES,
      &::System::enable_drawing_info_overlays_on_all_code_editor_stages,
   },
   {
      ::System::DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES,
      &::System::disable_drawing_info_overlays_on_all_code_editor_stages,
   },
   {
      ::System::PUSH_FILE_NAVIGATOR_SELECTION,
      &::System::push_file_navigator_selection,
   },
   {
      ::System::PUSH_COMPONENT_NAVIGATOR_SELECTION,
      &::System::push_component_navigator_selection,
   },
   {
      ::System::REFRESH_REGEX_HILIGHTS_ON_FRONTMOST_STAGE,
      &::System::refresh_regex_hilights_on_frontmost_stage,
   },
   {
      ::System::REFRESH_REGEX_HILIGHTS_ON_ALL_CODE_EDITOR_STAGES,
      &::System::refresh_regex_hilights_on_all_code_editor_stages,
   },
   {
      ::System::REFRESH_GIT_MODIFIED_LINE_NUMBERS_ON_ALL_CODE_EDITOR_STAGES,
      &::System::refresh_git_modified_line_numbers_on_all_code_editor_stages,
   },
   {
      ::System::SET_SEARCH_REGEX_EXPRESSION_ON_ALL_CODE_EDITOR_STAGES_TO_REGEX_TEMP_FILE_CONTENTS,
      &::System::set_search_regex_expression_on_all_code_editor_stages_to_regex_temp_file_contents,
   },
   {
      ::System::REFRESH_RERUN_OUTPUT_WATCHERS,
      &::System::refresh_rerun_output_watchers,
   },
   {
      ::System::INCREASE_FONT_SIZE,
      &::System::increase_font_size,
   },
   {
      ::System::DECREASE_FONT_SIZE,
      &::System::decrease_font_size,
   },
   {
      ::System::ADD_FILE_IS_UNSAVED_NOTIFICATION,
      &::System::add_file_is_unsaved_notification,
   },
   {
      ::System::WRITE_FOCUSED_COMPONENT_NAME_TO_FILE,
      &::System::write_focused_component_name_to_file,
   },
   {
      ::System::REMOVE_FILE_IS_UNSAVED_NOTIFICATION,
      &::System::remove_file_is_unsaved_notification,
   },
   {
      ::System::TOGGLE_COMMAND_MODE_ON,
      &::System::toggle_command_mode_on,
   },
   {
      ::System::TOGGLE_COMMAND_MODE_OFF,
      &::System::toggle_command_mode_off,
   },
   {
      ::System::ROTATE_STAGE_LEFT,
      &::System::rotate_stage_left,
   },
   {
      ::System::ROTATE_STAGE_RIGHT,
      &::System::rotate_stage_right,
   },
   {
      ::System::ROTATE_RELATIVE_UP,
      &::System::rotate_relative_up,
   },
   {
      ::System::ROTATE_RELATIVE_DOWN,
      &::System::rotate_relative_down,
   },
   {
      ::System::RUN_MAKE,
      &::System::run_make,
   },
   {
      ::System::CLEAR_LAST_COMPILED_ERROR_MESSAGES,
      &::System::clear_last_compiled_error_messages,
   },
   {
      ::System::RUN_PROJECT_TESTS,
      &::System::run_project_tests,
   },
   {
      ::System::SAVE_FRONTMOST_CODE_EDITOR_STAGE,
      &::System::save_frontmost_code_editor_stage,
   },
   {
      ::System::SET_FOCUSED_COMPONENT_NAME_TO_TOPMOST_RELATIVE,
      &::System::set_focused_component_name_to_topmost_relative,
   },
   {
      ::System::SPAWN_COMPONENT_NAVIGATOR,
      &::System::spawn_component_navigator,
   },
   {
      ::System::EXECUTE_MAGIC_COMMAND,
      &::System::execute_magic_command,
   },
   {
      ::System::SPAWN_FILE_NAVIGATOR,
      &::System::spawn_file_navigator,
   },
   {
      ::System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL,
      &::System::spawn_regex_input_box_modal,
   },
   {
      ::System::SPAWN_GIT_COMMIT_MESSAGE_INPUT_BOX_MODAL,
      &::System::spawn_git_commit_message_input_box_modal,
   },
   {
      ::System::SPAWN_RERUN_OUTPUT_WATCHER,
      &::System::spawn_rerun_output_watcher,
   },
   {
      ::System::SUBMIT_CURRENT_MODAL,
      &::System::submit_current_modal,
   },
   {
      ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE,
      &::System::fx__play_focus_animation_on_frontmost_stage,
   },
   {
      ::System::CHECK_GIT_SYNC_AND_UPDATE_POWERBAR,
      &::System::check_git_sync_and_update_powerbar,
   },
   {
      ::System::COMMIT_ALL_FILES_WITH_LAST_GIT_COMMIT_MESSAGE_FROM_REGEX_TEMP_FILE_CONTENTS_AND_APPEND_PACKET_AND_CLEAR_SCORES,
      &::System::commit_all_files_with_last_git_commit_message_from_regex_temp_file_contents_and_append_packet_and_clear_scores,
   },
   {
      ::System::PUSH_TO_GIT_REMOTE,
      &::System::push_to_git_remote,
   },
};
return default_function_mapping;

}

void EventController::process_local_event(std::string event_name)
{
if (!(system))
   {
      std::stringstream error_message;
      error_message << "EventController" << "::" << "process_local_event" << ": error: " << "guard \"system\" not met";
      throw std::runtime_error(error_message.str());
   }
std::map<std::string, std::function<bool(::System&)>> event_function_mapping = get_default_function_mapping();

std::map<std::string, std::function<bool(::System&)>>::const_iterator it = event_function_mapping.find(event_name);
bool function_mapping_exists = it != event_function_mapping.end();

if (!function_mapping_exists)
{
   std::cout << "???? attempted to find mapping for \""
             << event_name
             << "\" in \"System/EventController\" but it does not exist."
             << std::endl;
}
else
{
   try
   {
      std::cout << "System::EventController::" << event_name << std::endl;

      // could use the iterator element found via the find() call above, rather than doing a new lookup
      std::function<bool(::System&)> function_to_be_called = event_function_mapping[event_name];
      bool function_returned_true_from_execution = function_to_be_called(*system);
      if (!function_returned_true_from_execution)
      {
         // TODO: add some throwing code here
      }
      return;
   }
   catch (const std::exception &exception)
   {
      std::cout << ">BOOM< cannot execute \""
                << event_name
                << "\".  The following exception occurred: "
                << exception.what()
                << std::endl;

      std::stringstream error_message;
      error_message << "An exception was thrown: \"" << exception.what() << "\"";
      add_notification(error_message.str());
   }
}


return;

}

void EventController::process_event(ALLEGRO_EVENT& event)
{
if (!(system))
   {
      std::stringstream error_message;
      error_message << "EventController" << "::" << "process_event" << ": error: " << "guard \"system\" not met";
      throw std::runtime_error(error_message.str());
   }
KeyboardCommandMapper keyboard_key_up_mapper;
KeyboardCommandMapper keyboard_key_down_mapper;
KeyboardCommandMapper keyboard_command_mapper;

keyboard_key_down_mapper.set_mapping(ALLEGRO_KEY_COMMAND, false, false, false, false, {
  ::System::TOGGLE_COMMAND_MODE_ON,
  ::System::ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES,
});
keyboard_key_up_mapper.set_mapping(ALLEGRO_KEY_COMMAND, false, false, false, false, {
  ::System::TOGGLE_COMMAND_MODE_OFF,
  ::System::DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES,
});


//                      set_mapping(al_keycode,         shift, ctrl,  alt,   command, std::vector<std::string>)
keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, {
   ::System::DESTROY_TOPMOST_STAGE });

if (system->is_current_stage_a_modal())
{
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, false, {
      ::System::SUBMIT_CURRENT_MODAL });
}
else
{
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_PAD_PLUS, false, false, false, false, {
      ::System::INCREASE_FONT_SIZE });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_PAD_MINUS, false, false, false, false, {
      ::System::DECREASE_FONT_SIZE });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, false, false, true, {
      ::System::ROTATE_STAGE_LEFT,
      ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
      ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_CLOSEBRACE, false, false, false, true, {
      ::System::ROTATE_STAGE_RIGHT,
      ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
      ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKQUOTE, false, false, false, false, {
      ::System::OPEN_HEXAGON_CONFIG_FILE,
      ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
       });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, true, false, false, true, {
      ::System::ROTATE_RELATIVE_UP,
      ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
      ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_R, false, true, false, false, {
      ::System::DESTROY_ALL_CODE_EDITOR_STAGES,
      ::System::CREATE_RAILS_RESOURCE_LAYOUT,
      ::System::ROTATE_STAGE_RIGHT,
      ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
      ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_CLOSEBRACE, true, false, false, true, {
      ::System::DESTROY_ALL_CODE_EDITOR_STAGES,
      ::System::ROTATE_RELATIVE_DOWN,
      ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
      ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, false, false, true, {
      ::System::SAVE_FRONTMOST_CODE_EDITOR_STAGE, });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_T, false, false, true, false, {
      ::System::SAVE_FRONTMOST_CODE_EDITOR_STAGE,
      ::System::RUN_PROJECT_TESTS });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_M, false, false, false, true, {
      ::System::SAVE_FRONTMOST_CODE_EDITOR_STAGE,
      ::System::CLEAR_LAST_COMPILED_ERROR_MESSAGES,
      ::System::RUN_MAKE });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, true, false, false, false, {
      ::System::SPAWN_FILE_NAVIGATOR });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, false, false, false, false, {
      ::System::SPAWN_COMPONENT_NAVIGATOR });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_8, true, true, false, false, {
      ::System::EXECUTE_MAGIC_COMMAND });

   if (system->is_current_stage_in_edit_mode())
   {
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, false, {
        ::System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL,
         });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, true, false, false, {
         ::System::SPAWN_GIT_COMMIT_MESSAGE_INPUT_BOX_MODAL,
         });
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
   StageInterface *frontmost_stage = system->get_frontmost_stage();
   if (frontmost_stage) frontmost_stage->process_event(event);
}
return;

}
} // namespace System
} // namespace Hexagon


