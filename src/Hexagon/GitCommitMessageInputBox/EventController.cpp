


#include <Hexagon/GitCommitMessageInputBox/EventController.hpp>

#include <Hexagon/GitCommitMessageInputBox/Stage.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <iostream>



GitCommitMessageInputBox::EventController::EventController(Hexagon::GitCommitMessageInputBox::Stage *stage)
   : EventControllerInterface()
   , stage(stage)
   , last_performed_action_queue_recording("last-performed-action-queue-recording")
   , last_performed_action_queue_is_recording(false)
{
}



GitCommitMessageInputBox::EventController::~EventController()
{}



bool GitCommitMessageInputBox::EventController::clear_last_performed_action_queue_recording()
{
   last_performed_action_queue_recording.clear_actions();
   return true;
}



bool GitCommitMessageInputBox::EventController::start_recording_last_performed_action_queue_recording()
{
   last_performed_action_queue_is_recording = true;
   return true;
}



bool GitCommitMessageInputBox::EventController::stop_recording_last_performed_action_queue_recording()
{
   last_performed_action_queue_is_recording = false;
   return true;
}



bool GitCommitMessageInputBox::EventController::is_last_performed_action_queue_recording()
{
   return last_performed_action_queue_is_recording;
}



bool GitCommitMessageInputBox::EventController::play_last_performed_action_queue_recording()
{
   bool previous_last_performed_action_queue_is_recording = last_performed_action_queue_is_recording;
   last_performed_action_queue_is_recording = false;

   ActionQueueRecording recording = last_performed_action_queue_recording;

   for (int i=0; i<recording.infer_num_actions(); i++)
   {
      Action action = recording.get_action_at(i);
      process_local_event(action.get_name(), action.get_data1());
   }

   last_performed_action_queue_is_recording = previous_last_performed_action_queue_is_recording;

   return true;
}



void GitCommitMessageInputBox::EventController::process_local_event(std::string event_name, ActionData action_data1)
{
   if (!stage)
   {
      throw std::runtime_error("[GitCommitMessageInputBox::EventController::process_local_event()] error: stage cannot be a nullptr");
   }

   std::cout << "GitCommitMessageInputBox::EventController::" << event_name << std::endl;

   // hack is that this member should not be a pointer, and this ref should ref a concrete object
   ::CodeEditor::CodeEditor *code_editor = &stage->get_code_editor_ref();

   try {
      if (event_name == MOVE_CURSOR_UP) code_editor->move_cursor_up();
      else if (event_name == MOVE_CURSOR_DOWN) code_editor->move_cursor_down();
      else if (event_name == MOVE_CURSOR_LEFT) code_editor->move_cursor_left();
      else if (event_name == MOVE_CURSOR_RIGHT) code_editor->move_cursor_right();
      else if (event_name == MOVE_CURSOR_TO_TOP_OF_SCREEN) code_editor->move_cursor_to_top_of_screen();
      else if (event_name == MOVE_CURSOR_TO_MIDDLE_OF_SCREEN) code_editor->move_cursor_to_middle_of_screen();
      else if (event_name == MOVE_CURSOR_TO_BOTTOM_OF_SCREEN) code_editor->move_cursor_to_bottom_of_screen();
      else if (event_name == MOVE_CURSOR_JUMP_TO_NEXT_WORD) code_editor->move_cursor_jump_to_next_word();
      else if (event_name == MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD) code_editor->move_cursor_jump_to_next_big_word();
      else if (event_name == MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD) code_editor->move_cursor_jump_to_previous_word();
      else if (event_name == JUMP_CURSOR_TO_END_OF_NEXT_WORD) code_editor->move_cursor_to_end_of_next_word();
      else if (event_name == JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD) code_editor->move_cursor_to_end_of_next_big_word();
      else if (event_name == JUMP_TO_NEXT_CODE_POINT) code_editor->jump_to_next_code_point();
      else if (event_name == JUMP_TO_PREVIOUS_CODE_POINT) code_editor->jump_to_previous_code_point();
      else if (event_name == JUMP_TO_NEXT_OR_NEAREST_CODE_POINT) code_editor->jump_to_next_or_nearest_code_point();
      else if (event_name == DELETE_CHARACTER) code_editor->delete_character();
      else if (event_name == INSERT_STRING) code_editor->insert_string(action_data1.get_string());
      else if (event_name == SET_INSERT_MODE) code_editor->set_insert_mode();
      else if (event_name == SET_EDIT_MODE) code_editor->set_edit_mode();
      else if (event_name == JOIN_LINES) code_editor->join_lines();
      else if (event_name == SPLIT_LINES) code_editor->split_lines();
      else if (event_name == MOVE_CURSOR_TO_START_OF_LINE) code_editor->move_cursor_to_start_of_line();
      else if (event_name == DELETE_LINE) code_editor->delete_line();
      else if (event_name == MOVE_CURSOR_TO_END_OF_LINE) code_editor->move_cursor_to_end_of_line();
      else if (event_name == MOVE_CURSOR_TO_LAST_CHARACTER_OF_LINE) code_editor->move_cursor_to_last_character_of_line();
      else if (event_name == MOVE_CURSOR_TO_FIRST_NON_WHITESPACE_CHARACTER)
         code_editor->move_cursor_to_first_non_whitespace_character();
      else if (event_name == SAVE_FILE_AND_TOUCH_IF_SYMLINK) code_editor->save_file_and_touch_if_symlink();
      //else if (event_name == MOVE_STAGE_UP) code_editor->move_stage_up();
      //else if (event_name == MOVE_STAGE_DOWN) code_editor->move_stage_down();
      //else if (event_name == SCALE_STAGE_UP) code_editor->scale_stage_delta(0.1);
      //else if (event_name == SCALE_STAGE_DOWN) code_editor->scale_stage_delta(-0.1);
      else if (event_name == JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN)
        code_editor->offset_first_line_number(code_editor->infer_num_lines_to_draw());
      else if (event_name == JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN)
        code_editor->offset_first_line_number(-code_editor->infer_num_lines_to_draw());
      else if (event_name == JUMP_FIRST_LINE_NUM_DOWN)
        code_editor->offset_first_line_number(code_editor->infer_num_lines_to_draw()/2);
      else if (event_name == JUMP_FIRST_LINE_NUM_UP)
        code_editor->offset_first_line_number(-code_editor->infer_num_lines_to_draw()/2);
      else if (event_name == STEP_FIRST_LINE_NUM_DOWN)
         code_editor->offset_first_line_number(1);
      else if (event_name == STEP_FIRST_LINE_NUM_UP)
         code_editor->offset_first_line_number(-1);
      else if (event_name == OFFSET_CURSOR_POSITION_Y_DOWN)
         code_editor->offset_cursor_position_y(code_editor->infer_num_lines_to_draw()/2);
      else if (event_name == OFFSET_CURSOR_POSITION_Y_UP)
         code_editor->offset_cursor_position_y(-code_editor->infer_num_lines_to_draw()/2);
      else if (event_name == OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN)
         code_editor->offset_cursor_position_y(code_editor->infer_num_lines_to_draw());
      else if (event_name == OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN)
         code_editor->offset_cursor_position_y(-code_editor->infer_num_lines_to_draw());
      else if (event_name == ENABLE_DRAWING_INFO_OVERLAY)
         code_editor->enable_drawing_info_overlay();
      else if (event_name == DISABLE_DRAWING_INFO_OVERLAY)
         code_editor->disable_drawing_info_overlay();
      else if (event_name == REFRESH_GIT_MODIFIED_LINE_NUMBERS)
         code_editor->refresh_git_modified_line_numbers();
      //else if (event_name == TOGGLE_SHOWING_CODE_MESSAGE_POINTS)
      //   toggle_showing_code_message_points();
      else if (event_name == REFRESH_REGEX_MESSAGE_POINTS)
         code_editor->refresh_regex_message_points();
      else if (event_name == OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR)
         code_editor->offset_first_line_to_vertically_center_cursor();
      else if (event_name == CREATE_VISUAL_SELECTION_AT_CURRENT_CURSOR_LOCATION)
         code_editor->create_visual_selection_at_current_cursor_location();
      else if (event_name == DESTROY_CURRENT_VISUAL_SELECTION)
         code_editor->destroy_current_visual_selection();
      else if (event_name == TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION)
         code_editor->toggle_currently_grabbing_visual_selection();
      else if (event_name == YANK_SELECTED_TEXT_TO_CLIPBOARD)
         code_editor->yank_selected_text_to_clipboard();
      else if (event_name == PASTE_SELECTED_TEXT_FROM_CLIPBOARD)
         code_editor->paste_selected_text_from_clipboard();
      else if (event_name == CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING)
         clear_last_performed_action_queue_recording();
      else if (event_name == START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING)
         start_recording_last_performed_action_queue_recording();
      else if (event_name == STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING)
         stop_recording_last_performed_action_queue_recording();
      else if (event_name == PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING)
         play_last_performed_action_queue_recording();
      else if (event_name == INSERT_THREE_SPACES_AT_START_OF_LINE)
         code_editor->insert_three_spaces_at_start_of_line();
   }

   catch (const std::exception &e)
   {
      std::cout << "cannot execute \"" << event_name << "\": "<< e.what() << std::endl;
   }

   if (last_performed_action_queue_is_recording && event_name != START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING)
   {
      std::cout << "   \033[0;30mGitCommitMessageInputBox:: recording "
                << event_name
                << " event to last_performed_action_queue_recording queue\033[0m"
                << std::endl;
      last_performed_action_queue_recording.append_action(Action(event_name, action_data1));
   }
}

void GitCommitMessageInputBox::EventController::process_event(ALLEGRO_EVENT &event)
{
   //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
   //bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::vector<std::string> comand_identifier);
   //KeyboardCommandMapper edit_mode__keyboard_command_mapper;
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_0, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_START_OF_LINE,
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, true,  false, false, false, {
      ::GitCommitMessageInputBox::EventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      //GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_START_OF_LINE,
      //GitCommitMessageInputBox::EventController::MOVE_CURSOR_JUMP_TO_NEXT_WORD,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_FIRST_NON_WHITESPACE_CHARACTER,
      ::GitCommitMessageInputBox::EventController::SET_INSERT_MODE,
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_A, true,  false, false, false, {
      ::GitCommitMessageInputBox::EventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_END_OF_LINE,
      ::GitCommitMessageInputBox::EventController::SET_INSERT_MODE,
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_A, false,  false, false, false, {
      ::GitCommitMessageInputBox::EventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_RIGHT,
      ::GitCommitMessageInputBox::EventController::SET_INSERT_MODE,
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_DOWN
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, true,  false, false, false, {
      ::GitCommitMessageInputBox::EventController::JOIN_LINES
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_UP
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_H, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_LEFT
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_L, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_RIGHT
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_H, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_TOP_OF_SCREEN
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_M, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_MIDDLE_OF_SCREEN
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_L, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_BOTTOM_OF_SCREEN
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_W, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_JUMP_TO_NEXT_WORD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_W, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_E, false, false, false, false, {
   //   GitCommitMessageInputBox::EventController::JUMP_CURSOR_TO_END_OF_NEXT_WORD });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_E, true, false, false, false, {
   //   GitCommitMessageInputBox::EventController::JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_B, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_N, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::JUMP_TO_NEXT_CODE_POINT,
      ::GitCommitMessageInputBox::EventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_N, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::JUMP_TO_PREVIOUS_CODE_POINT,
      ::GitCommitMessageInputBox::EventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_X, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::DELETE_CHARACTER });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::SET_INSERT_MODE, });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_0, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_START_OF_LINE });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::DELETE_CHARACTER, ::GitCommitMessageInputBox::EventController::SET_INSERT_MODE, });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, true, false, false, {
   //   ::GitCommitMessageInputBox::EventController::SAVE_FILE_AND_TOUCH_IF_SYMLINK,
   //   ::GitCommitMessageInputBox::EventController::REFRESH_GIT_MODIFIED_LINE_NUMBERS });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_B, false, true, false, false, {
      ::GitCommitMessageInputBox::EventController::JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN,
      ::GitCommitMessageInputBox::EventController::OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_F, false, true, false, false, {
      ::GitCommitMessageInputBox::EventController::JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN,
      ::GitCommitMessageInputBox::EventController::OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_U, false, true, false, false, {
      ::GitCommitMessageInputBox::EventController::JUMP_FIRST_LINE_NUM_UP,
      ::GitCommitMessageInputBox::EventController::OFFSET_CURSOR_POSITION_Y_UP });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_D, false, true, false, false, {
      ::GitCommitMessageInputBox::EventController::JUMP_FIRST_LINE_NUM_DOWN,
      ::GitCommitMessageInputBox::EventController::OFFSET_CURSOR_POSITION_Y_DOWN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_Y, false, true, false, false, {
      ::GitCommitMessageInputBox::EventController::STEP_FIRST_LINE_NUM_UP });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_E, false, true, false, false, {
   //   GitCommitMessageInputBox::EventController::STEP_FIRST_LINE_NUM_DOWN });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_EQUALS, false, true, false, false, {
   //   GitCommitMessageInputBox::EventController::SCALE_STAGE_UP });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_MINUS, false, true, false, false, {
   //   GitCommitMessageInputBox::EventController::SCALE_STAGE_DOWN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_O, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_END_OF_LINE,
      ::GitCommitMessageInputBox::EventController::SPLIT_LINES,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_DOWN,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_START_OF_LINE,
      ::GitCommitMessageInputBox::EventController::SET_INSERT_MODE,
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_O, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_START_OF_LINE,
      ::GitCommitMessageInputBox::EventController::SPLIT_LINES,
      ::GitCommitMessageInputBox::EventController::SET_INSERT_MODE,
      });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_G, false, false, true, false, {
     ::GitCommitMessageInputBox::EventController::SAVE_FILE_AND_TOUCH_IF_SYMLINK,
     ::GitCommitMessageInputBox::EventController::REFRESH_GIT_MODIFIED_LINE_NUMBERS });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, false, false, false, {
   //   GitCommitMessageInputBox::EventController::TOGGLE_SHOWING_CODE_MESSAGE_POINTS });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::REFRESH_REGEX_MESSAGE_POINTS });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_Z, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_V, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_Y, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::YANK_SELECTED_TEXT_TO_CLIPBOARD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_4, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_LAST_CHARACTER_OF_LINE });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_P, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::PASTE_SELECTED_TEXT_FROM_CLIPBOARD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_FULLSTOP, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING});
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_FULLSTOP, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::INSERT_THREE_SPACES_AT_START_OF_LINE });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKSPACE, true, false, false, false, {
      ::GitCommitMessageInputBox::EventController::DELETE_LINE });


   //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
   //bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::vector<std::string> comand_identifier);
   //KeyboardCommandMapper insert_mode__keyboard_command_mapper;
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::SET_EDIT_MODE,
      ::GitCommitMessageInputBox::EventController::STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING });
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, true, false, false, {
      ::GitCommitMessageInputBox::EventController::SET_EDIT_MODE,
      ::GitCommitMessageInputBox::EventController::STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING });
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKSPACE, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_LEFT,
      ::GitCommitMessageInputBox::EventController::DELETE_CHARACTER });
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, false, {
      ::GitCommitMessageInputBox::EventController::SPLIT_LINES,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_DOWN,
      ::GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_START_OF_LINE });
   //insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, true, false, false, {
   //   ::GitCommitMessageInputBox::EventController::SAVE_FILE_AND_TOUCH_IF_SYMLINK,
   //   ::GitCommitMessageInputBox::EventController::REFRESH_GIT_MODIFIED_LINE_NUMBERS });


   ::CodeEditor::CodeEditor *code_editor = &stage->get_code_editor_ref();


   switch(code_editor->get_mode())
   {
      case ::CodeEditor::CodeEditor::EDIT:
      switch(event.type)
      {
      case ALLEGRO_EVENT_KEY_DOWN:
         break;
      case ALLEGRO_EVENT_KEY_UP:
         break;
      case ALLEGRO_EVENT_KEY_CHAR:
         bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL || event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
         std::vector<std::string> mapped_events =
            edit_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
         break;
      }
      break;
      case ::CodeEditor::CodeEditor::INSERT:
      switch(event.type)
      {
      case ALLEGRO_EVENT_KEY_DOWN:
         break;
      case ALLEGRO_EVENT_KEY_UP:
         break;
      case ALLEGRO_EVENT_KEY_CHAR:
         bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL || event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
         std::vector<std::string> mapped_events =
            insert_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
         if (mapped_events.empty())
         {
            char character = (char)(event.keyboard.unichar);
            std::string string = " ";
            string[0] = character;
            process_local_event(INSERT_STRING, ActionData(string));
            process_local_event(MOVE_CURSOR_RIGHT);
         }
         break;
      }
      break;
   }
}



namespace GitCommitMessageInputBox
{
   std::string const EventController::MOVE_CURSOR_UP = "MOVE_CURSOR_UP";
   std::string const EventController::MOVE_CURSOR_DOWN = "MOVE_CURSOR_DOWN";
   std::string const EventController::MOVE_CURSOR_LEFT = "MOVE_CURSOR_LEFT";
   std::string const EventController::MOVE_CURSOR_RIGHT = "MOVE_CURSOR_RIGHT";
}


std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_TOP_OF_SCREEN = "MOVE_CURSOR_TO_TOP_OF_SCREEN";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_MIDDLE_OF_SCREEN = "MOVE_CURSOR_TO_MIDDLE_OF_SCREEN";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_BOTTOM_OF_SCREEN = "MOVE_CURSOR_TO_BOTTOM_OF_SCREEN";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_JUMP_TO_NEXT_WORD = "MOVE_CURSOR_JUMP_TO_NEXT_WORD";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD = "MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD = "MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD";
std::string const GitCommitMessageInputBox::EventController::JUMP_CURSOR_TO_END_OF_NEXT_WORD = "JUMP_CURSOR_TO_END_OF_NEXT_WORD";
std::string const GitCommitMessageInputBox::EventController::JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD =
   "JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD";
std::string const GitCommitMessageInputBox::EventController::JUMP_TO_NEXT_CODE_POINT = "JUMP_TO_NEXT_CODE_POINT";
std::string const GitCommitMessageInputBox::EventController::JUMP_TO_PREVIOUS_CODE_POINT = "JUMP_TO_PREVIOUS_CODE_POINT";
std::string const GitCommitMessageInputBox::EventController::JUMP_TO_NEXT_OR_NEAREST_CODE_POINT = "JUMP_TO_NEXT_OR_NEAREST_CODE_POINT";
std::string const GitCommitMessageInputBox::EventController::DELETE_CHARACTER = "DELETE_CHARACTER";
std::string const GitCommitMessageInputBox::EventController::INSERT_STRING = "INSERT_STRING";
std::string const GitCommitMessageInputBox::EventController::SET_INSERT_MODE = "SET_INSERT_MODE";
std::string const GitCommitMessageInputBox::EventController::SET_EDIT_MODE = "SET_EDIT_MODE";
std::string const GitCommitMessageInputBox::EventController::JOIN_LINES = "JOIN_LINES";
std::string const GitCommitMessageInputBox::EventController::SPLIT_LINES = "SPLIT_LINES";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_START_OF_LINE = "MOVE_CURSOR_TO_START_OF_LINE";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_END_OF_LINE = "MOVE_CURSOR_TO_END_OF_LINE";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_LAST_CHARACTER_OF_LINE =
   "MOVE_CURSOR_TO_LAST_CHARACTER_OF_LINE";
std::string const GitCommitMessageInputBox::EventController::MOVE_CURSOR_TO_FIRST_NON_WHITESPACE_CHARACTER =
   "MOVE_CURSOR_TO_FIRST_NON_WHITESPACE_CHARACTER";
std::string const GitCommitMessageInputBox::EventController::SAVE_FILE_AND_TOUCH_IF_SYMLINK = "SAVE_FILE_AND_TOUCH_IF_SYMLINK";
//std::string const GitCommitMessageInputBox::EventController::MOVE_STAGE_UP = "MOVE_STAGE_UP";
//std::string const GitCommitMessageInputBox::EventController::MOVE_STAGE_DOWN = "MOVE_STAGE_DOWN";
std::string const GitCommitMessageInputBox::EventController::DELETE_LINE = "DELETE_LINE";
std::string const GitCommitMessageInputBox::EventController::JUMP_FIRST_LINE_NUM_UP = "JUMP_FIRST_LINE_NUM_UP";
std::string const GitCommitMessageInputBox::EventController::JUMP_FIRST_LINE_NUM_DOWN = "JUMP_FIRST_LINE_NUM_DOWN";
std::string const GitCommitMessageInputBox::EventController::JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN = "JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN";
std::string const GitCommitMessageInputBox::EventController::JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN = "JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN";
std::string const GitCommitMessageInputBox::EventController::STEP_FIRST_LINE_NUM_UP = "STEP_FIRST_LINE_NUM_UP";
std::string const GitCommitMessageInputBox::EventController::STEP_FIRST_LINE_NUM_DOWN = "STEP_FIRST_LINE_NUM_DOWN";
std::string const GitCommitMessageInputBox::EventController::OFFSET_CURSOR_POSITION_Y_UP = "OFFSET_CURSOR_POSITION_Y_UP";
std::string const GitCommitMessageInputBox::EventController::OFFSET_CURSOR_POSITION_Y_DOWN = "OFFSET_CURSOR_POSITION_Y_DOWN";
std::string const GitCommitMessageInputBox::EventController::OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN = "OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN";
std::string const GitCommitMessageInputBox::EventController::OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN = "OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN";
//std::string const GitCommitMessageInputBox::EventController::SCALE_STAGE_UP = "SCALE_STAGE_UP";
//std::string const GitCommitMessageInputBox::EventController::SCALE_STAGE_DOWN = "SCALE_STAGE_DOWN";
std::string const GitCommitMessageInputBox::EventController::REFRESH_GIT_MODIFIED_LINE_NUMBERS = "REFRESH_GIT_MODIFIED_LINE_NUMBERS";
//std::string const GitCommitMessageInputBox::EventController::TOGGLE_SHOWING_CODE_MESSAGE_POINTS = "TOGGLE_SHOWING_CODE_MESSAGE_POINTS";
std::string const GitCommitMessageInputBox::EventController::ENABLE_DRAWING_INFO_OVERLAY = "ENABLE_DRAWING_INFO_OVERLAY";
std::string const GitCommitMessageInputBox::EventController::DISABLE_DRAWING_INFO_OVERLAY = "DISABLE_DRAWING_INFO_OVERLAY";
std::string const GitCommitMessageInputBox::EventController::REFRESH_REGEX_MESSAGE_POINTS = "REFRESH_REGEX_MESSAGE_POINTS";
std::string const GitCommitMessageInputBox::EventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR = "OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR";
std::string const GitCommitMessageInputBox::EventController::CREATE_VISUAL_SELECTION_AT_CURRENT_CURSOR_LOCATION = "CREATE_VISUAL_SELECTION_AT_CURRENT_CURSOR_LOCATION";
std::string const GitCommitMessageInputBox::EventController::DESTROY_CURRENT_VISUAL_SELECTION = "DESTROY_CURRENT_VISUAL_SELECTION";
std::string const GitCommitMessageInputBox::EventController::TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION = "TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION";
std::string const GitCommitMessageInputBox::EventController::YANK_SELECTED_TEXT_TO_CLIPBOARD = "YANK_SELECTED_TEXT_TO_CLIPBOARD";
std::string const GitCommitMessageInputBox::EventController::PASTE_SELECTED_TEXT_FROM_CLIPBOARD = "PASTE_SELECTED_TEXT_FROM_CLIPBOARD";
std::string const GitCommitMessageInputBox::EventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING = "CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING";
std::string const GitCommitMessageInputBox::EventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING = "START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING";
std::string const GitCommitMessageInputBox::EventController::STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING = "STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING";
std::string const GitCommitMessageInputBox::EventController::PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING = "PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING";
std::string const GitCommitMessageInputBox::EventController::INSERT_THREE_SPACES_AT_START_OF_LINE =
   "INSERT_THREE_SPACES_AT_START_OF_LINE";
