#include <Hexagon/FileNavigatorEventController.hpp>
#include <Hexagon/FileNavigator.hpp>
#include <Blast/KeyboardCommandMapper.hpp>
#include <iostream>



FileNavigatorEventController::FileNavigatorEventController(FileNavigator *file_navigator)
   : file_navigator(file_navigator)
{}



FileNavigatorEventController::~FileNavigatorEventController() {}



void FileNavigatorEventController::process_local_event(std::string event_name, ActionData action_data1)
{
   std::cout << "FileNavigator::" << event_name << std::endl;

   try
   {
      bool executed = false;

      if (event_name == MOVE_CURSOR_UP) { file_navigator->move_cursor_up(); executed = true; }
      if (event_name == MOVE_CURSOR_DOWN) { file_navigator->move_cursor_down(); executed = true; }

      if (!executed) std::cout << "???? cannot execute \"" << event_name << "\".  It does not exist." << std::endl;
   }
   catch (const std::exception &exception)
   {
      std::cout << "💥 cannot execute \"" << event_name << "\"" << std::endl;
   }
}



void FileNavigatorEventController::process_event(ALLEGRO_EVENT &event)
{
   KeyboardCommandMapper keyboard_command_mapper;
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, false, false, false, { MOVE_CURSOR_DOWN });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K, false, false, false, { MOVE_CURSOR_UP });

   bool event_caught = false;

   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_UP:
      break;
   case ALLEGRO_EVENT_KEY_DOWN:
      break;
   case ALLEGRO_EVENT_KEY_CHAR:
      bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
      bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
      bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL || event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
      std::vector<std::string> mapped_events = keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
      if (!mapped_events.empty()) event_caught = true;
      for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
      break;
   }
}



const std::string FileNavigatorEventController::MOVE_CURSOR_UP = "MOVE_CURSOR_UP";
const std::string FileNavigatorEventController::MOVE_CURSOR_DOWN = "MOVE_CURSOR_DOWN";

