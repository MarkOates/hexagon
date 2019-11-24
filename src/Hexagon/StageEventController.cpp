


#include <Hexagon/StageEventController.hpp>

#include <Blast/KeyboardCommandMapper.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <iostream>



CodeEditorEventController::CodeEditorEventController(CodeEditor *stage)
   : EventControllerInterface()
   , stage(stage)
   , last_performed_action_queue_recording("last-performed-action-queue-recording")
   , last_performed_action_queue_is_recording(false)
{
}



CodeEditorEventController::~CodeEditorEventController()
{}



bool CodeEditorEventController::clear_last_performed_action_queue_recording()
{
   last_performed_action_queue_recording.clear_actions();
   return true;
}



bool CodeEditorEventController::start_recording_last_performed_action_queue_recording()
{
   last_performed_action_queue_is_recording = true;
   return true;
}



bool CodeEditorEventController::stop_recording_last_performed_action_queue_recording()
{
   last_performed_action_queue_is_recording = false;
   return true;
}



bool CodeEditorEventController::is_last_performed_action_queue_recording()
{
   return last_performed_action_queue_is_recording;
}



bool CodeEditorEventController::play_last_performed_action_queue_recording()
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



void CodeEditorEventController::process_local_event(std::string event_name, ActionData action_data1)
{
   if (!stage) throw std::runtime_error("[CodeEditorEventController::process_local_event()] error: stage cannot be a nullptr");

   std::cout << "CodeEditorEventController::" << event_name << std::endl;

   try {
      if (event_name == MOVE_CURSOR_UP) stage->move_cursor_up();
      else if (event_name == MOVE_CURSOR_DOWN) stage->move_cursor_down();
      else if (event_name == MOVE_CURSOR_LEFT) stage->move_cursor_left();
      else if (event_name == MOVE_CURSOR_RIGHT) stage->move_cursor_right();
      else if (event_name == MOVE_CURSOR_TO_TOP_OF_SCREEN) stage->move_cursor_to_top_of_screen();
      else if (event_name == MOVE_CURSOR_TO_MIDDLE_OF_SCREEN) stage->move_cursor_to_middle_of_screen();
      else if (event_name == MOVE_CURSOR_TO_BOTTOM_OF_SCREEN) stage->move_cursor_to_bottom_of_screen();
      else if (event_name == MOVE_CURSOR_JUMP_TO_NEXT_WORD) stage->move_cursor_jump_to_next_word();
      else if (event_name == MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD) stage->move_cursor_jump_to_next_big_word();
      else if (event_name == MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD) stage->move_cursor_jump_to_previous_word();
      else if (event_name == JUMP_CURSOR_TO_END_OF_NEXT_WORD) stage->jump_cursor_to_end_of_next_word();
      else if (event_name == JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD) stage->jump_cursor_to_end_of_next_big_word();
      else if (event_name == JUMP_TO_NEXT_CODE_POINT) stage->jump_to_next_code_point();
      else if (event_name == JUMP_TO_PREVIOUS_CODE_POINT) stage->jump_to_previous_code_point();
      else if (event_name == DELETE_CHARACTER) stage->delete_character();
      else if (event_name == INSERT_STRING) stage->insert_string(action_data1.get_string());
      else if (event_name == SET_INSERT_MODE) stage->set_insert_mode();
      else if (event_name == SET_EDIT_MODE) stage->set_edit_mode();
      else if (event_name == JOIN_LINES) stage->join_lines();
      else if (event_name == SPLIT_LINES) stage->split_lines();
      else if (event_name == MOVE_CURSOR_TO_START_OF_LINE) stage->move_cursor_to_start_of_line();
      else if (event_name == MOVE_CURSOR_TO_END_OF_LINE) stage->move_cursor_to_end_of_line();
      else if (event_name == SAVE_FILE) stage->save_file();
      else if (event_name == MOVE_STAGE_UP) stage->move_stage_up();
      else if (event_name == MOVE_STAGE_DOWN) stage->move_stage_down();
      else if (event_name == SCALE_STAGE_UP) stage->scale_stage_delta(0.1);
      else if (event_name == SCALE_STAGE_DOWN) stage->scale_stage_delta(-0.1);
      else if (event_name == JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN) stage->offset_first_line_number(stage->infer_num_lines_to_draw());
      else if (event_name == JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN) stage->offset_first_line_number(-stage->infer_num_lines_to_draw());
      else if (event_name == JUMP_FIRST_LINE_NUM_DOWN) stage->offset_first_line_number(stage->infer_num_lines_to_draw()/2);
      else if (event_name == JUMP_FIRST_LINE_NUM_UP) stage->offset_first_line_number(-stage->infer_num_lines_to_draw()/2);
      else if (event_name == STEP_FIRST_LINE_NUM_DOWN) stage->offset_first_line_number(1);
      else if (event_name == STEP_FIRST_LINE_NUM_UP) stage->offset_first_line_number(-1);
      else if (event_name == OFFSET_CURSOR_POSITION_Y_DOWN) stage->offset_cursor_position_y(stage->infer_num_lines_to_draw()/2);
      else if (event_name == OFFSET_CURSOR_POSITION_Y_UP) stage->offset_cursor_position_y(-stage->infer_num_lines_to_draw()/2);
      else if (event_name == OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN) stage->offset_cursor_position_y(stage->infer_num_lines_to_draw());
      else if (event_name == OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN) stage->offset_cursor_position_y(-stage->infer_num_lines_to_draw());
      else if (event_name == REFRESH_GIT_MODIFIED_LINE_NUMBERS) stage->refresh_git_modified_line_numbers();
      //else if (event_name == TOGGLE_SHOWING_CODE_MESSAGE_POINTS) toggle_showing_code_message_points();
      else if (event_name == REFRESH_REGEX_MESSAGE_POINTS) stage->refresh_regex_message_points();
      else if (event_name == OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR) stage->offset_first_line_to_vertically_center_cursor();
      else if (event_name == CREATE_VISUAL_SELECTION_AT_CURRENT_CURSOR_LOCATION) stage->create_visual_selection_at_current_cursor_location();
      else if (event_name == DESTROY_CURRENT_VISUAL_SELECTION) stage->destroy_current_visual_selection();
      else if (event_name == TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION) stage->toggle_currently_grabbing_visual_selection();
      else if (event_name == YANK_SELECTED_TEXT_TO_CLIPBOARD) stage->yank_selected_text_to_clipboard();
      else if (event_name == PASTE_SELECTED_TEXT_FROM_CLIPBOARD) stage->paste_selected_text_from_clipboard();
      else if (event_name == CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING) clear_last_performed_action_queue_recording();
      else if (event_name == START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING) start_recording_last_performed_action_queue_recording();
      else if (event_name == STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING) stop_recording_last_performed_action_queue_recording();
      else if (event_name == PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING) play_last_performed_action_queue_recording();
   }

   catch (const std::exception &e)
   {
      std::cout << "\033[0;33m💥 cannot execute \"" << event_name << "\": \033[0;31m" << e.what() << "\033[0;33m\033[0m" << std::endl;
   }

   if (last_performed_action_queue_is_recording && event_name != START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING)
   {
      std::cout << "   \033[0;30mCodeEditor:: recording " << event_name << " event to last_performed_action_queue_recording queue\033[0m" << std::endl;
      last_performed_action_queue_recording.append_action(Action(event_name, action_data1));
   }
}

void CodeEditorEventController::process_event(ALLEGRO_EVENT &event)
{
   //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
   //bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::vector<std::string> comand_identifier);
   KeyboardCommandMapper edit_mode__keyboard_command_mapper;
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_0, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_TO_START_OF_LINE });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, true,  false, false, false, { CodeEditorEventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::MOVE_CURSOR_TO_START_OF_LINE, CodeEditorEventController::MOVE_CURSOR_JUMP_TO_NEXT_WORD, CodeEditorEventController::SET_INSERT_MODE, });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_A, true,  false, false, false, { CodeEditorEventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::MOVE_CURSOR_TO_END_OF_LINE, CodeEditorEventController::SET_INSERT_MODE, });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_A, false,  false, false, false, { CodeEditorEventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::MOVE_CURSOR_RIGHT, CodeEditorEventController::SET_INSERT_MODE, });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_DOWN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, true,  false, false, false, { CodeEditorEventController::JOIN_LINES });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_UP });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_H, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_LEFT });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_L, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_RIGHT });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_H, true, false, false, false, { CodeEditorEventController::MOVE_CURSOR_TO_TOP_OF_SCREEN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_M, true, false, false, false, { CodeEditorEventController::MOVE_CURSOR_TO_MIDDLE_OF_SCREEN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_L, true, false, false, false, { CodeEditorEventController::MOVE_CURSOR_TO_BOTTOM_OF_SCREEN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_W, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_JUMP_TO_NEXT_WORD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_W, true, false, false, false, { CodeEditorEventController::MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_E, false, false, false, false, { CodeEditorEventController::JUMP_CURSOR_TO_END_OF_NEXT_WORD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_E, true, false, false, false, { CodeEditorEventController::JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_B, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_N, false, false, false, false, { CodeEditorEventController::JUMP_TO_NEXT_CODE_POINT, CodeEditorEventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_N, true, false, false, false, { CodeEditorEventController::JUMP_TO_PREVIOUS_CODE_POINT, CodeEditorEventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_X, false, false, false, false, { CodeEditorEventController::DELETE_CHARACTER });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, false, false, false, false, { CodeEditorEventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::SET_INSERT_MODE, });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_0, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_TO_START_OF_LINE });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, false, false, false, { CodeEditorEventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::DELETE_CHARACTER, CodeEditorEventController::SET_INSERT_MODE, });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, true, false, false, { CodeEditorEventController::SAVE_FILE });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_B, false, true, false, false, { CodeEditorEventController::JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN, CodeEditorEventController::OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_F, false, true, false, false, { CodeEditorEventController::JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN, CodeEditorEventController::OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_U, false, true, false, false, { CodeEditorEventController::JUMP_FIRST_LINE_NUM_UP, CodeEditorEventController::OFFSET_CURSOR_POSITION_Y_UP });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_D, false, true, false, false, { CodeEditorEventController::JUMP_FIRST_LINE_NUM_DOWN, CodeEditorEventController::OFFSET_CURSOR_POSITION_Y_DOWN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_Y, false, true, false, false, { CodeEditorEventController::STEP_FIRST_LINE_NUM_UP });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_E, false, true, false, false, { CodeEditorEventController::STEP_FIRST_LINE_NUM_DOWN });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_EQUALS, false, true, false, false, { CodeEditorEventController::SCALE_STAGE_UP });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_MINUS, false, true, false, false, { CodeEditorEventController::SCALE_STAGE_DOWN });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_O, false, false, false, false, { CodeEditorEventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::MOVE_CURSOR_TO_END_OF_LINE, CodeEditorEventController::SPLIT_LINES, CodeEditorEventController::MOVE_CURSOR_DOWN, CodeEditorEventController::MOVE_CURSOR_TO_START_OF_LINE, CodeEditorEventController::SET_INSERT_MODE, });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_O, true, false, false, false, { CodeEditorEventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING, CodeEditorEventController::MOVE_CURSOR_UP, CodeEditorEventController::MOVE_CURSOR_TO_END_OF_LINE, CodeEditorEventController::SPLIT_LINES, CodeEditorEventController::MOVE_CURSOR_DOWN, CodeEditorEventController::MOVE_CURSOR_TO_START_OF_LINE, CodeEditorEventController::SET_INSERT_MODE, });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_G, false, false, true, false, { CodeEditorEventController::SAVE_FILE, CodeEditorEventController::REFRESH_GIT_MODIFIED_LINE_NUMBERS });
   //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, false, false, false, { CodeEditorEventController::TOGGLE_SHOWING_CODE_MESSAGE_POINTS });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, false, { CodeEditorEventController::REFRESH_REGEX_MESSAGE_POINTS });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_Z, false, false, false, false, { CodeEditorEventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_V, false, false, false, false, { CodeEditorEventController::TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_Y, false, false, false, false, { CodeEditorEventController::YANK_SELECTED_TEXT_TO_CLIPBOARD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_P, true, false, false, false, { CodeEditorEventController::PASTE_SELECTED_TEXT_FROM_CLIPBOARD });
   edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_FULLSTOP, false, false, false, false, { CodeEditorEventController::PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING });


   //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
   //bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::vector<std::string> comand_identifier);
   KeyboardCommandMapper insert_mode__keyboard_command_mapper;
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, { CodeEditorEventController::SET_EDIT_MODE, CodeEditorEventController::STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING });
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, true, false, false, { CodeEditorEventController::SET_EDIT_MODE, CodeEditorEventController::STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING });
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKSPACE, false, false, false, false, { CodeEditorEventController::MOVE_CURSOR_LEFT, CodeEditorEventController::DELETE_CHARACTER });
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, false, { CodeEditorEventController::SPLIT_LINES, CodeEditorEventController::MOVE_CURSOR_DOWN, CodeEditorEventController::MOVE_CURSOR_TO_START_OF_LINE });
   insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, true, false, false, { CodeEditorEventController::SAVE_FILE });


   switch(stage->get_mode())
   {
   case CodeEditor::EDIT:
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
         std::vector<std::string> mapped_events = edit_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
         break;
      }
      break;
   case CodeEditor::INSERT:
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
         std::vector<std::string> mapped_events = insert_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
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



std::string const CodeEditorEventController::MOVE_CURSOR_UP = "MOVE_CURSOR_UP";
std::string const CodeEditorEventController::MOVE_CURSOR_DOWN = "MOVE_CURSOR_DOWN";
std::string const CodeEditorEventController::MOVE_CURSOR_LEFT = "MOVE_CURSOR_LEFT";
std::string const CodeEditorEventController::MOVE_CURSOR_RIGHT = "MOVE_CURSOR_RIGHT";
std::string const CodeEditorEventController::MOVE_CURSOR_TO_TOP_OF_SCREEN = "MOVE_CURSOR_TO_TOP_OF_SCREEN";
std::string const CodeEditorEventController::MOVE_CURSOR_TO_MIDDLE_OF_SCREEN = "MOVE_CURSOR_TO_MIDDLE_OF_SCREEN";
std::string const CodeEditorEventController::MOVE_CURSOR_TO_BOTTOM_OF_SCREEN = "MOVE_CURSOR_TO_BOTTOM_OF_SCREEN";
std::string const CodeEditorEventController::MOVE_CURSOR_JUMP_TO_NEXT_WORD = "MOVE_CURSOR_JUMP_TO_NEXT_WORD";
std::string const CodeEditorEventController::MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD = "MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD";
std::string const CodeEditorEventController::MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD = "MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD";
std::string const CodeEditorEventController::JUMP_CURSOR_TO_END_OF_NEXT_WORD = "JUMP_CURSOR_TO_END_OF_NEXT_WORD";
std::string const CodeEditorEventController::JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD = "JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD";
std::string const CodeEditorEventController::JUMP_TO_NEXT_CODE_POINT = "JUMP_TO_NEXT_CODE_POINT";
std::string const CodeEditorEventController::JUMP_TO_PREVIOUS_CODE_POINT = "JUMP_TO_PREVIOUS_CODE_POINT";
std::string const CodeEditorEventController::DELETE_CHARACTER = "DELETE_CHARACTER";
std::string const CodeEditorEventController::INSERT_STRING = "INSERT_STRING";
std::string const CodeEditorEventController::SET_INSERT_MODE = "SET_INSERT_MODE";
std::string const CodeEditorEventController::SET_EDIT_MODE = "SET_EDIT_MODE";
std::string const CodeEditorEventController::JOIN_LINES = "JOIN_LINES";
std::string const CodeEditorEventController::SPLIT_LINES = "SPLIT_LINES";
std::string const CodeEditorEventController::MOVE_CURSOR_TO_START_OF_LINE = "MOVE_CURSOR_TO_START_OF_LINE";
std::string const CodeEditorEventController::MOVE_CURSOR_TO_END_OF_LINE = "MOVE_CURSOR_TO_END_OF_LINE";
std::string const CodeEditorEventController::SAVE_FILE = "SAVE_FILE";
std::string const CodeEditorEventController::MOVE_STAGE_UP = "MOVE_STAGE_UP";
std::string const CodeEditorEventController::MOVE_STAGE_DOWN = "MOVE_STAGE_DOWN";
std::string const CodeEditorEventController::JUMP_FIRST_LINE_NUM_UP = "JUMP_FIRST_LINE_NUM_UP";
std::string const CodeEditorEventController::JUMP_FIRST_LINE_NUM_DOWN = "JUMP_FIRST_LINE_NUM_DOWN";
std::string const CodeEditorEventController::JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN = "JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN";
std::string const CodeEditorEventController::JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN = "JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN";
std::string const CodeEditorEventController::STEP_FIRST_LINE_NUM_UP = "STEP_FIRST_LINE_NUM_UP";
std::string const CodeEditorEventController::STEP_FIRST_LINE_NUM_DOWN = "STEP_FIRST_LINE_NUM_DOWN";
std::string const CodeEditorEventController::OFFSET_CURSOR_POSITION_Y_UP = "OFFSET_CURSOR_POSITION_Y_UP";
std::string const CodeEditorEventController::OFFSET_CURSOR_POSITION_Y_DOWN = "OFFSET_CURSOR_POSITION_Y_DOWN";
std::string const CodeEditorEventController::OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN = "OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN";
std::string const CodeEditorEventController::OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN = "OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN";
std::string const CodeEditorEventController::SCALE_STAGE_UP = "SCALE_STAGE_UP";
std::string const CodeEditorEventController::SCALE_STAGE_DOWN = "SCALE_STAGE_DOWN";
std::string const CodeEditorEventController::REFRESH_GIT_MODIFIED_LINE_NUMBERS = "REFRESH_GIT_MODIFIED_LINE_NUMBERS";
//std::string const CodeEditorEventController::TOGGLE_SHOWING_CODE_MESSAGE_POINTS = "TOGGLE_SHOWING_CODE_MESSAGE_POINTS";
std::string const CodeEditorEventController::REFRESH_REGEX_MESSAGE_POINTS = "REFRESH_REGEX_MESSAGE_POINTS";
std::string const CodeEditorEventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR = "OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR";
std::string const CodeEditorEventController::CREATE_VISUAL_SELECTION_AT_CURRENT_CURSOR_LOCATION = "CREATE_VISUAL_SELECTION_AT_CURRENT_CURSOR_LOCATION";
std::string const CodeEditorEventController::DESTROY_CURRENT_VISUAL_SELECTION = "DESTROY_CURRENT_VISUAL_SELECTION";
std::string const CodeEditorEventController::TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION = "TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION";
std::string const CodeEditorEventController::YANK_SELECTED_TEXT_TO_CLIPBOARD = "YANK_SELECTED_TEXT_TO_CLIPBOARD";
std::string const CodeEditorEventController::PASTE_SELECTED_TEXT_FROM_CLIPBOARD = "PASTE_SELECTED_TEXT_FROM_CLIPBOARD";
std::string const CodeEditorEventController::CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING = "CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING";
std::string const CodeEditorEventController::START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING = "START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING";
std::string const CodeEditorEventController::STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING = "STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING";
std::string const CodeEditorEventController::PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING = "PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING";



