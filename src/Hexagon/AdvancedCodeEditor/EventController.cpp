

#include <Hexagon/AdvancedCodeEditor/EventController.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


ALLEGRO_EVENT EventController::a_default_empty_event = {};


EventController::EventController(Hexagon::AdvancedCodeEditor::Stage* stage, std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> events_dictionary, AllegroFlare::KeyboardCommandMapper keyboard_command_mapping)
   : stage(stage)
   , events_dictionary(events_dictionary)
   , keyboard_command_mapping(keyboard_command_mapping)
{
}


EventController::~EventController()
{
}


std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> &EventController::get_events_dictionary_ref()
{
   return events_dictionary;
}


ALLEGRO_EVENT &EventController::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


bool EventController::process_local_event(std::string event_name, ActionData action_data)
{
   if (!(stage))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::EventController::process_local_event]: error: guard \"stage\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::EventController::process_local_event]: error: guard \"stage\" not met");
   }
   Hexagon::AdvancedCodeEditor::Stage &component = *stage;

   std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>>::iterator it =
      events_dictionary.find(event_name);
   if (it == events_dictionary.end())
   {
      std::stringstream error_message;
      error_message << "AdvancedCodeEditor::EventController::process_local_event: error: "
                    << "No local event named \"" << event_name << "\" exists.";
      throw std::runtime_error(error_message.str());
      return false; // NOTE: this return is redundant
   }
   else
   {
      std::cout << "AdvancedCodeEditor::" << event_name << std::endl;

      bool caught = false;
      std::string caught_name = "";
      std::string caught_what = "";
      // NOTE: some exceptions have additional information. For example, "future_error" has "code" memeber
      // https://en.cppreference.com/w/cpp/thread/future_error

      try
      {
         events_dictionary[event_name](component);
      }
      // TODO complete list of possible exceptions to catch at https://en.cppreference.com/w/cpp/error/exception
      catch (const std::logic_error &exception)
      {
         caught = true;
         caught_name = "std::logic_error";
         caught_what = exception.what();
      }
      catch (const std::exception &exception)
      {
         caught = true;
         caught_name = "std::exception";
         caught_what = exception.what();
      }

      if (caught)
      {
         // TODO make this error message output in red
         std::cout << ">>BOOM<< an unexpected exception was thrown, cannot execute \""
                   << event_name
                   << "\". The exception was thrown with the following information returned:"
                   << std::endl << "   exception_type: " << caught_name
                   << std::endl << "   exception_what: " << caught_what
                   << std::endl;
         return false;
      }

      // Record the action (unless replaying)
      if (stage->is_in_insert_mode() && !stage->get_currently_playing_action_queue_recording())
      {
         stage->append_action_to_action_queue_recording(event_name, action_data);
      }
      if (event_name == Stage::ACTION_SET_TO_INSERT_MODE) stage->clear_action_queue_recording();
   }

   return true;
}

void EventController::process_event(ALLEGRO_EVENT& event)
{
   if (!(stage))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedCodeEditor::EventController::process_event]: error: guard \"stage\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedCodeEditor::EventController::process_event]: error: guard \"stage\" not met");
   }
   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_DOWN:
      break;
   case ALLEGRO_EVENT_KEY_UP:
      break;
   case ALLEGRO_EVENT_KEY_CHAR:
      bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
      bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
      bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
      bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
      std::vector<std::string> mapped_events =
         keyboard_command_mapping.get_mapping(event.keyboard.keycode, shift, ctrl, alt, command);
      for (auto &mapped_event : mapped_events) process_local_event(mapped_event);

      if (stage->is_in_insert_mode())
      {
         if (mapped_events.empty()) // TODO: I'm not sure what the purpose of this section is
         {
            char character = (char)(event.keyboard.unichar);
            stage->get_input_buffer_ref() = " ";
            stage->get_input_buffer_ref()[0] = character;
            process_local_event("insert_string_from_input_buffer");
            process_local_event("cursor_move_right");
         }
         return;
      }
   }
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


