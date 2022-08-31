

#include <Hexagon/MultiplexMenu/Stage.hpp>

#include <Blast/StringSplitter.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>
#include <Hexagon/MultiplexMenu/Renderer.hpp>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace MultiplexMenu
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, StageInterface* stage_to_send_messages_to, Hexagon::System::System* system_to_tell_when_its_time_to_close_and_by_the_way_this_is_bad_design, Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu)
   : StageInterface(StageInterface::MULTIPLEX_MENU)
   , font_bin(font_bin)
   , stage_to_send_messages_to(stage_to_send_messages_to)
   , system_to_tell_when_its_time_to_close_and_by_the_way_this_is_bad_design(system_to_tell_when_its_time_to_close_and_by_the_way_this_is_bad_design)
   , multiplex_menu(multiplex_menu)
{
}


Stage::~Stage()
{
}


Hexagon::MultiplexMenu::MultiplexMenu &Stage::get_multiplex_menu_ref()
{
   return multiplex_menu;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render()
{
   placement3d &place = get_place();
   place.start_transform();

   Hexagon::MultiplexMenu::Renderer renderer(font_bin, &multiplex_menu);
   renderer.render();

   place.restore_transform();
   return;
}

void Stage::send_message_to_stage(std::string message)
{
   if (!(stage_to_send_messages_to))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "send_message_to_stage" << ": error: " << "guard \"stage_to_send_messages_to\" not met";
      throw std::runtime_error(error_message.str());
   }
   stage_to_send_messages_to->process_local_event(message);
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_DOWN:
      break;
   case ALLEGRO_EVENT_KEY_UP:
      break;
   case ALLEGRO_EVENT_KEY_CHAR:
      int al_keycode = event.keyboard.keycode;
      bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
      bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
      bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
      bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;

      // TODO
      // right now, pressing the A key will send "delete_word_under_cursor" to the stage
      //if (event.keyboard.keycode == ALLEGRO_KEY_A) send_message_to_stage("delete_word_under_cursor");
      
      // build an object representing this current keyboard command
      Hexagon::KeyboardCommandKey this_keyboard_command;
      this_keyboard_command.set_al_keycode(al_keycode);
      this_keyboard_command.set_ctrl(ctrl);
      this_keyboard_command.set_command(command);
      this_keyboard_command.set_alt(alt);
      this_keyboard_command.set_shift(shift);
      
      Hexagon::MultiplexMenu::MenuItem* menu_item_matching_key =
         find_menu_item_by_keyboard_command_key_on_current_page(this_keyboard_command);

      std::vector<std::string> final_command_set_to_execute;
      
      if (menu_item_matching_key)
      {
         bool commands_executed_and_assuming_close_menu = false;

         for (auto &command : menu_item_matching_key->get_value())
         {
            //std::string command = menu_item_matching_key->get_value();
            std::cout << "Found key combo on current page of multiplex menu. The command is \""
                      << command << "\"" << std::endl;
            //bool value_opens_another_page = false; // TODO evaluate this command
            if (infer_menu_item_value_is_instruction_to_open_page(command))
            {
               std::string page_name_to_open = extract_menu_item_value_page_name_to_open(command);
               multiplex_menu.open_page(page_name_to_open);
               final_command_set_to_execute.clear();
            }
            else
            {
               final_command_set_to_execute.push_back(command);
               //multiplex_menu.set_final_command_to_execute(command);
               //send_message_to_stage(command);
               commands_executed_and_assuming_close_menu = true;
            }
         }

         if (commands_executed_and_assuming_close_menu)
         {
            std::cout << "Notice: MultiplexMenu/Stage is about to notify the system that it should close the "
                      << "multiplex menu.  The way this is designed, I'm surprised it won't crash.  Keep an "
                      << "eye on it." << std::endl;

            multiplex_menu.set_final_command_set_to_execute(final_command_set_to_execute);
            notify_system_that_its_time_to_close_this_multiplex_menu();
         }
      }

      break;
   }
   return;
}

void Stage::notify_system_that_its_time_to_close_this_multiplex_menu()
{
   if (system_to_tell_when_its_time_to_close_and_by_the_way_this_is_bad_design)
      system_to_tell_when_its_time_to_close_and_by_the_way_this_is_bad_design->submit_current_modal();
      //system_to_tell_when_its_time_to_close_and_by_the_way_this_is_bad_design->close_topmost_multiplex_menu();
   return;
}

bool Stage::infer_menu_item_value_is_instruction_to_open_page(std::string menu_item_value)
{
   std::string magic_open_page_header = "open_page";
   Blast::StringSplitter splitter(menu_item_value, ':');
   std::vector<std::string> tokens = splitter.split();
   if (tokens.size() >= 2 && tokens[0] == magic_open_page_header) return true;
   return false;
}

std::string Stage::extract_menu_item_value_page_name_to_open(std::string menu_item_value)
{
   std::string magic_open_page_header = "open_page";
   Blast::StringSplitter splitter(menu_item_value, ':');
   std::vector<std::string> tokens = splitter.split();
   if (tokens.size() >= 2 && tokens[0] == magic_open_page_header && !tokens[1].empty()) return tokens[1];
   return "[invalid-value-from-extract_menu_item_value_page_name_to_open]";
}

void Stage::open_page(std::string page_name)
{
   multiplex_menu.open_page(page_name);
   return;
     
}

Hexagon::MultiplexMenu::MenuItem* Stage::find_menu_item_by_keyboard_command_key_on_current_page(Hexagon::KeyboardCommandKey keyboard_command_key)
{
   Hexagon::MultiplexMenu::MultiplexMenuPage *page = multiplex_menu.infer_current_page();
   if (!page) return nullptr;
   return page->find_item_by_keyboard_command_key(keyboard_command_key);
}


} // namespace MultiplexMenu
} // namespace Hexagon


