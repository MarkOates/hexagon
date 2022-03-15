

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


EventController::EventController(Hexagon::System::System* system, std::map<std::string, std::function<bool(Hexagon::System::System&)>> function_mapping)
   : system(system)
   , function_mapping(function_mapping)
{
}


EventController::~EventController()
{
}


std::map<std::string, std::function<bool(Hexagon::System::System&)>> EventController::get_default_function_mapping()
{
   std::map<std::string, std::function<bool(Hexagon::System::System&)>> default_function_mapping = {
      {
         ::System::CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION,
         &::Hexagon::System::System::create_stage_from_last_file_navigator_selection,
      },
      {
         ::System::SPAWN_CLASS_BRIEF_MENU,
         &::Hexagon::System::System::spawn_class_brief_menu,
      },
      {
         ::System::CLEAR_HUD_TITLE,
         &::Hexagon::System::System::clear_hud_title,
      },
      {
         ::System::SET_HUD_CAPS_LOCK_LIGHT_ON,
         &::Hexagon::System::System::set_hud_caps_lock_light_on,
      },
      {
         ::System::SET_HUD_CAPS_LOCK_LIGHT_OFF,
         &::Hexagon::System::System::set_hud_caps_lock_light_off,
      },
      {
         ::System::SPAWN_DRAWING_BOX,
         &::Hexagon::System::System::spawn_drawing_box,
      },
      {
         ::System::PARSE_TEST_RESULTS_FROM_LAST_TEST_RUN_DUMP,
         &::Hexagon::System::System::parse_test_results_from_last_test_run_dump,
      },
      {
         ::System::PULL_BACK_CAMERA_TO_OFF_AXIS_LEFT,
         &::Hexagon::System::System::pull_back_camera_to_off_axis_left,
      },
      {
         ::System::PULL_BACK_CAMERA_TO_OFF_AXIS_RIGHT,
         &::Hexagon::System::System::pull_back_camera_to_off_axis_right,
      },
      {
         ::System::SEND_MESSAGE_TO_DAEMUS_TO_BUILD,
         &::Hexagon::System::System::send_message_to_daemus_to_build,
      },
      {
         ::System::SET_FRONTMOST_GIT_COMMIT_MESSAGE_INPUT_BOX_TO_SUBMITTED_AND_PENDING_DESTRUCTION,
         &::Hexagon::System::System::set_frontmost_git_commit_message_input_box_to_submitted_and_pending_destruction,
      },
      {
         ::System::SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION,
         &::Hexagon::System::System::spawn_file_navigator_from_last_file_navigator_folder_selection,
      },
      {
         ::System::CREATE_STAGES_FROM_LAYOUT_OF_LAST_COMPONENT_NAVIGATOR_SELECTION,
         &::Hexagon::System::System::create_stages_from_layout_of_last_component_navigator_selection,
      },
      {
         ::System::CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION,
         &::Hexagon::System::System::create_two_or_three_split_layout_from_last_component_navigator_selection,
      },
      {
         ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
         &::Hexagon::System::System::center_camera_on_frontmost_stage,
      },
      {
         ::System::DESTROY_TOPMOST_STAGE,
         &::Hexagon::System::System::destroy_topmost_stage,
      },
      {
         ::System::OPEN_HEXAGON_CONFIG_FILE,
         &::Hexagon::System::System::open_hexagon_config_file,
      },
      {
         ::System::DESTROY_ALL_CODE_EDITOR_STAGES,
         &::Hexagon::System::System::destroy_all_code_editor_stages,
      },
      {
         ::System::ESCAPE_CURRENT_MODAL,
         &::Hexagon::System::System::escape_current_modal,
      },
      {
         ::System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE,
         &::Hexagon::System::System::jump_to_next_code_point_on_stage,
      },
      {
         ::System::JUMP_TO_NEXT_OR_NEAREST_CODE_POINT_ON_STAGE,
         &::Hexagon::System::System::jump_to_next_or_nearest_code_point_on_stage,
      },
      {
         ::System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE,
         &::Hexagon::System::System::offset_first_line_to_vertically_center_cursor_on_stage,
      },
      {
         ::System::ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES,
         &::Hexagon::System::System::enable_drawing_info_overlays_on_all_code_editor_stages,
      },
      {
         ::System::DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES,
         &::Hexagon::System::System::disable_drawing_info_overlays_on_all_code_editor_stages,
      },
      {
         ::System::PUSH_FILE_NAVIGATOR_SELECTION,
         &::Hexagon::System::System::push_file_navigator_selection,
      },
      {
         ::System::PUSH_PROJECT_NAVIGATOR_SELECTION,
         &::Hexagon::System::System::push_project_navigator_selection,
      },
      {
         ::System::PUSH_COMPONENT_RELATIONS_NAVIGATOR_SELECTION,
         &::Hexagon::System::System::push_component_relations_navigator_selection,
      },
      {
         ::System::PUSH_COMPONENT_NAVIGATOR_SELECTION,
         &::Hexagon::System::System::push_component_navigator_selection,
      },
      {
         ::System::REFRESH_REGEX_HILIGHTS_ON_FRONTMOST_STAGE,
         &::Hexagon::System::System::refresh_regex_hilights_on_frontmost_stage,
      },
      {
         ::System::REFRESH_REGEX_HILIGHTS_ON_ALL_CODE_EDITOR_STAGES,
         &::Hexagon::System::System::refresh_regex_hilights_on_all_code_editor_stages,
      },
      {
         ::System::REFRESH_GIT_MODIFIED_LINE_NUMBERS_ON_ALL_CODE_EDITOR_STAGES,
         &::Hexagon::System::System::refresh_git_modified_line_numbers_on_all_code_editor_stages,
      },
      {
         ::System::SET_REGEX_TEMP_FILE_CONTENTS_TO_WORD_UNDER_CURRENT_ADVANCED_CODE_EDITOR_CURSOR,
         &::Hexagon::System::System::set_regex_temp_file_contents_to_word_under_current_advanced_code_editor_cursor,
      },
      {
         ::System::SET_SEARCH_REGEX_EXPRESSION_ON_ALL_CODE_EDITOR_STAGES_TO_REGEX_TEMP_FILE_CONTENTS,
         &::Hexagon::System::System::set_search_regex_expression_on_all_code_editor_stages_to_regex_temp_file_contents,
      },
      {
         ::System::INCREASE_FONT_SIZE,
         &::Hexagon::System::System::increase_font_size,
      },
      {
         ::System::DECREASE_FONT_SIZE,
         &System::decrease_font_size,
      },
      {
         ::System::ADD_FILE_IS_UNSAVED_NOTIFICATION,
         &System::add_file_is_unsaved_notification,
      },
      {
         ::System::WRITE_FOCUSED_COMPONENT_NAME_TO_FILE,
         &System::write_focused_component_name_to_file,
      },
      {
         ::System::REMOVE_FILE_IS_UNSAVED_NOTIFICATION,
         &System::remove_file_is_unsaved_notification,
      },
      {
         ::System::TOGGLE_COMMAND_MODE_ON,
         &System::toggle_command_mode_on,
      },
      {
         ::System::TOGGLE_COMMAND_MODE_OFF,
         &System::toggle_command_mode_off,
      },
      {
         ::System::RESET_CAMERA_TO_CENTER,
         &System::reset_camera_to_center,
      },
      {
         ::System::ROTATE_STAGE_LEFT,
         &System::rotate_stage_left_and_update_focused_state_on_changed_stages,
      },
      {
         ::System::ROTATE_STAGE_RIGHT,
         &System::rotate_stage_right_and_update_focused_state_on_changed_stages,
      },
      {
         ::System::CLEAR_LAST_COMPILED_ERROR_MESSAGES,
         &System::clear_last_compiled_error_messages,
      },
      {
         ::System::RUN_PROJECT_TESTS,
         &System::run_project_tests,
      },
      {
         ::System::SAVE_FRONTMOST_CODE_EDITOR_STAGE_AND_TOUCH_IF_SYMLINK,
         &System::save_frontmost_code_editor_stage_and_touch_if_symlink,
      },
      {
         ::System::SPAWN_COMPONENT_NAVIGATOR,
         &System::spawn_component_navigator,
      },
      {
         ::System::SPAWN_PROJECT_NAVIGATOR,
         &System::spawn_project_navigator,
      },
      {
         ::System::SPAWN_FANCY,
         &System::spawn_fancy,
      },
      {
         ::System::SPAWN_COMPONENT_RELATIONS_NAVIGATOR,
         &System::spawn_component_relations_navigator,
      },
      {
         ::System::EXECUTE_MAGIC_COMMAND,
         &System::execute_magic_command,
      },
      {
         ::System::SPAWN_FILE_NAVIGATOR,
         &System::spawn_file_navigator,
      },
      {
         ::System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL,
         &System::spawn_regex_input_box_modal,
      },
      {
         ::System::SPAWN_GIT_COMMIT_MESSAGE_INPUT_BOX_MODAL,
         &System::spawn_git_commit_message_input_box_modal,
      },
      {
         ::System::SUBMIT_CURRENT_MODAL,
         &System::submit_current_modal,
      },
      {
         ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE,
         &System::fx__play_focus_animation_on_frontmost_stage,
      },
      {
         ::System::CHECK_GIT_SYNC_AND_UPDATE_POWERBAR,
         &System::check_git_sync_and_update_powerbar,
      },
      {
         ::System::OPEN_DOCUMENTATION_IN_BROWSER,
         &System::open_documentation_in_browser,
      },
      {
         ::System::COMMIT_ALL_FILES_WITH_LAST_GIT_COMMIT_MESSAGE_FROM_REGEX_TEMP_FILE_CONTENTS,
         &System::commit_all_files_with_last_git_commit_message_from_regex_temp_file_contents,
      },
      {
         ::System::APPEND_PACKET_USING_LAST_COMMIT_MESSAGE_AND_CLEAR_SCORES,
         &System::append_packet_using_last_commit_message_and_clear_scores,
      },
      {
         ::System::PUSH_TO_GIT_REMOTE,
         &System::push_to_git_remote,
      },
      {
         ::System::SPAWN_MULTIPLEX_DELETE_MENU,
         &System::spawn_multiplex_delete_menu,
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
   std::map<std::string, std::function<bool(Hexagon::System::System&)>> event_function_mapping =
      get_default_function_mapping();

   std::map<std::string, std::function<bool(Hexagon::System::System&)>>::const_iterator it =
      event_function_mapping.find(event_name);
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
         std::function<bool(Hexagon::System::System&)> function_to_be_called = event_function_mapping[event_name];
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

void EventController::process_event(ALLEGRO_EVENT* event_ptr)
{
   if (!(system))
      {
         std::stringstream error_message;
         error_message << "EventController" << "::" << "process_event" << ": error: " << "guard \"system\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_ptr))
      {
         std::stringstream error_message;
         error_message << "EventController" << "::" << "process_event" << ": error: " << "guard \"event_ptr\" not met";
         throw std::runtime_error(error_message.str());
      }
   KeyboardCommandMapper keyboard_key_up_mapper;
   KeyboardCommandMapper keyboard_key_down_mapper;
   KeyboardCommandMapper keyboard_key_char_mapper;
   ALLEGRO_EVENT &event = *event_ptr;

   auto KEYMOD_SHIFT = KeyboardCommandMapper::SHIFT;
   auto KEYMOD_CTRL = KeyboardCommandMapper::CTRL;

   //KeyboardCommandMapper::COMMAND

   keyboard_key_down_mapper.set_mapping(ALLEGRO_KEY_COMMAND, false, false, false, false, {
     ::System::TOGGLE_COMMAND_MODE_ON,
     ::System::ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES,
   });
   keyboard_key_up_mapper.set_mapping(ALLEGRO_KEY_COMMAND, false, false, false, false, {
     ::System::TOGGLE_COMMAND_MODE_OFF,
     ::System::DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES,
   });


   //                      set_mapping(al_keycode,         shift, ctrl,  alt,   command, std::vector<std::string>)
   //keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, {
   //   ::System::DESTROY_TOPMOST_STAGE });

   if (system->is_current_stage_a_modal()) // should remove this principal
   {
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, false, {
         ::System::SET_FRONTMOST_GIT_COMMIT_MESSAGE_INPUT_BOX_TO_SUBMITTED_AND_PENDING_DESTRUCTION,
         ::System::SUBMIT_CURRENT_MODAL
      });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, {
         ::System::DESTROY_TOPMOST_STAGE,
         ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
      });
   }
   else
   {
      if (!system->is_topmost_stage_an_advanced_code_editor())
      {
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, {
            ::System::DESTROY_TOPMOST_STAGE,
            ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE, // consider if this is desired behavior or not
         });
      }

      if (system->has_no_stages() || (!system->is_current_stage_in_insert_mode()))
      {
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, false, {
            ::System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL,
            });
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, true, false, false, {
            ::System::SPAWN_GIT_COMMIT_MESSAGE_INPUT_BOX_MODAL,
            });
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_TAB, true, false, false, false, {
            ::System::SPAWN_FILE_NAVIGATOR,
            ::System::PULL_BACK_CAMERA_TO_OFF_AXIS_LEFT,
          });
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_TAB, false, false, false, false, {
            ::System::SPAWN_COMPONENT_NAVIGATOR,
            ::System::PULL_BACK_CAMERA_TO_OFF_AXIS_LEFT,
          });
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_BACKQUOTE, false, false, false, false, {
            ::System::SPAWN_PROJECT_NAVIGATOR,
            ::System::PULL_BACK_CAMERA_TO_OFF_AXIS_LEFT,
          });
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_Z, KEYMOD_CTRL, { ::System::SPAWN_FANCY });
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_BACKSLASH, false, false, false, false, {
            ::System::SPAWN_COMPONENT_RELATIONS_NAVIGATOR,
            ::System::PULL_BACK_CAMERA_TO_OFF_AXIS_RIGHT,
          });
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_BACKSLASH, true, false, false, false, {
            ::System::SPAWN_CLASS_BRIEF_MENU });
      }

      if (system->is_topmost_stage_advanced_code_editor_in_edit_mode())
      {
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_D, false, false, false, false, {
            ::System::SPAWN_MULTIPLEX_DELETE_MENU });
         keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_8, true, false, false, false, {
            ::System::SET_REGEX_TEMP_FILE_CONTENTS_TO_WORD_UNDER_CURRENT_ADVANCED_CODE_EDITOR_CURSOR,
            ::System::SET_SEARCH_REGEX_EXPRESSION_ON_ALL_CODE_EDITOR_STAGES_TO_REGEX_TEMP_FILE_CONTENTS,
            ::System::REFRESH_REGEX_HILIGHTS_ON_ALL_CODE_EDITOR_STAGES }); // TODO, consider adding this "SHIFT+*"
                                                                           // mapping to the AdvancedCodeEditor itself,
                                                                           // too. But it will also be overridden
                                                                           // here to affect all stages as a feature.
      }

      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_EQUALS, false, true, false, false, {
         ::System::SPAWN_DRAWING_BOX });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_PAD_PLUS, false, false, false, false, {
         ::System::INCREASE_FONT_SIZE });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_PAD_MINUS, false, false, false, false, {
         ::System::DECREASE_FONT_SIZE });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, false, false, true, {
         ::System::ROTATE_STAGE_LEFT,
         ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
         ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_CLOSEBRACE, false, false, false, true, {
         ::System::ROTATE_STAGE_RIGHT,
         ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
         ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_BACKQUOTE, true, false, false, false, {
         ::System::OPEN_HEXAGON_CONFIG_FILE,
         ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
          });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_S, false, false, false, true, {
         ::System::SAVE_FRONTMOST_CODE_EDITOR_STAGE_AND_TOUCH_IF_SYMLINK, });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_D, KeyboardCommandMapper::COMMAND, {
         ::System::OPEN_DOCUMENTATION_IN_BROWSER,
         });
      keyboard_key_char_mapper.set_mapping(ALLEGRO_KEY_T, false, false, true, false, {
         ::System::SAVE_FRONTMOST_CODE_EDITOR_STAGE_AND_TOUCH_IF_SYMLINK,
         ::System::RUN_PROJECT_TESTS });
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
           keyboard_key_char_mapper.get_mapping(
             event.keyboard.keycode, shift, ctrl, alt, command);
         if (!mapped_events.empty()) event_caught = true;
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
      }
      break;
   case ALLEGRO_EVENT_MOUSE_AXES:
      {
         //std::cout << "axes " << event.mouse.x << ", " << event.mouse.y << std::endl;
         // TODO: add mouse events
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


