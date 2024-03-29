#pragma once



#include <string>
#include <Hexagon/EventControllerInterface.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/ActionQueueRecording.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>



namespace Hexagon
{
   namespace OneLineInputBox
   {
      class Stage;
   }
}



namespace OneLineInputBox
{
   class EventController : public EventControllerInterface
   {
   private:
      Hexagon::OneLineInputBox::Stage *stage;

      AllegroFlare::KeyboardCommandMapper edit_mode__keyboard_command_mapper;
      AllegroFlare::KeyboardCommandMapper insert_mode__keyboard_command_mapper;

      ActionQueueRecording last_performed_action_queue_recording;
      bool last_performed_action_queue_is_recording;

      bool clear_last_performed_action_queue_recording();
      bool start_recording_last_performed_action_queue_recording();
      bool stop_recording_last_performed_action_queue_recording();
      bool is_last_performed_action_queue_recording();
      bool play_last_performed_action_queue_recording();

   public:
      EventController(Hexagon::OneLineInputBox::Stage *stage=nullptr);
      virtual ~EventController();

      void process_local_event(std::string event_name, ActionData action_data1=ActionData()) override;
      void process_event(ALLEGRO_EVENT &event) override;

      static const std::string MOVE_CURSOR_UP;
      static const std::string MOVE_CURSOR_DOWN;
      static const std::string MOVE_CURSOR_LEFT;
      static const std::string MOVE_CURSOR_RIGHT;
      static const std::string MOVE_CURSOR_TO_TOP_OF_SCREEN;
      static const std::string MOVE_CURSOR_TO_MIDDLE_OF_SCREEN;
      static const std::string MOVE_CURSOR_TO_BOTTOM_OF_SCREEN;
      static const std::string MOVE_CURSOR_JUMP_TO_NEXT_WORD;
      static const std::string MOVE_CURSOR_JUMP_TO_NEXT_BIG_WORD;
      static const std::string MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD;
      static const std::string JUMP_CURSOR_TO_END_OF_NEXT_WORD;
      static const std::string JUMP_CURSOR_TO_END_OF_NEXT_BIG_WORD;
      static const std::string JUMP_TO_NEXT_CODE_POINT;
      static const std::string JUMP_TO_PREVIOUS_CODE_POINT;
      static const std::string JUMP_TO_NEXT_OR_NEAREST_CODE_POINT;
      static const std::string DELETE_CHARACTER;
      static const std::string INSERT_STRING;
      static const std::string SET_INSERT_MODE;
      static const std::string SET_EDIT_MODE;
      static const std::string JOIN_LINES;
      static const std::string SPLIT_LINES;
      static const std::string MOVE_CURSOR_TO_START_OF_LINE;
      static const std::string MOVE_CURSOR_TO_END_OF_LINE;
      static const std::string MOVE_CURSOR_TO_LAST_CHARACTER_OF_LINE;
      static const std::string MOVE_CURSOR_TO_FIRST_NON_WHITESPACE_CHARACTER;
      static const std::string SAVE_FILE_AND_TOUCH_IF_SYMLINK;
      //static const std::string MOVE_STAGE_UP;
      //static const std::string MOVE_STAGE_DOWN;
      //static const std::string SCALE_STAGE_UP;
      //static const std::string SCALE_STAGE_DOWN;
      static const std::string JUMP_FIRST_LINE_NUM_DOWN;
      static const std::string JUMP_FIRST_LINE_NUM_UP;
      static const std::string JUMP_FIRST_LINE_NUM_DOWN_WHOLE_SCREEN;
      static const std::string JUMP_FIRST_LINE_NUM_UP_WHOLE_SCREEN;
      static const std::string STEP_FIRST_LINE_NUM_DOWN;
      static const std::string STEP_FIRST_LINE_NUM_UP;
      static const std::string OFFSET_CURSOR_POSITION_Y_DOWN;
      static const std::string OFFSET_CURSOR_POSITION_Y_UP;
      static const std::string OFFSET_CURSOR_POSITION_Y_DOWN_WHOLE_SCREEN;
      static const std::string OFFSET_CURSOR_POSITION_Y_UP_WHOLE_SCREEN;
      static const std::string REFRESH_GIT_MODIFIED_LINE_NUMBERS;
      static const std::string DELETE_LINE;
      //static const std::string TOGGLE_SHOWING_CODE_MESSAGE_POINTS;
      static const std::string ENABLE_DRAWING_INFO_OVERLAY;
      static const std::string DISABLE_DRAWING_INFO_OVERLAY;
      static const std::string REFRESH_REGEX_MESSAGE_POINTS;
      static const std::string OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR;
      static const std::string CREATE_VISUAL_SELECTION_AT_CURRENT_CURSOR_LOCATION;
      static const std::string DESTROY_CURRENT_VISUAL_SELECTION;
      static const std::string TOGGLE_CURRENTLY_GRABBING_VISUAL_SELECTION;
      static const std::string YANK_SELECTED_TEXT_TO_CLIPBOARD;
      static const std::string PASTE_SELECTED_TEXT_FROM_CLIPBOARD;
      static const std::string CLEAR_LAST_PERFORMED_ACTION_QUEUE_RECORDING;
      static const std::string START_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING;
      static const std::string STOP_RECORDING_LAST_PERFORMED_ACTION_QUEUE_RECORDING;
      static const std::string PLAY_LAST_PERFORMED_ACTION_QUEUE_RECORDING;
      static const std::string INSERT_THREE_SPACES_AT_START_OF_LINE;
   };
} // namespace OneLineInputBox



