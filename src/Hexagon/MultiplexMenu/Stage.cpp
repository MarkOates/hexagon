

#include <Hexagon/MultiplexMenu/Stage.hpp>
#include <Hexagon/MultiplexMenu/Renderer.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>


namespace Hexagon
{
namespace MultiplexMenu
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, StageInterface* stage_to_send_messages_to, Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu, std::string start_page_name)
   : StageInterface(StageInterface::MULTIPLEX_MENU)
   , font_bin(font_bin)
   , stage_to_send_messages_to(stage_to_send_messages_to)
   , multiplex_menu(multiplex_menu)
   , start_page_name(start_page_name)
{
}


Stage::~Stage()
{
}


void Stage::set_start_page_name(std::string start_page_name)
{
   this->start_page_name = start_page_name;
}


std::string Stage::get_start_page_name()
{
   return start_page_name;
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
      
      if (menu_item_matching_key)
      {
         std::string command = menu_item_matching_key->get_value();
         std::cout << "Found key combo on current page of multiplex menu. The command is \""
                   << command << "\"" << std::endl;
         bool value_opens_another_page = false; // TODO evaluate this command
         if (value_opens_another_page)
         {
            std::string page_name_to_open = ""; // TODO fill this logic
            multiplex_menu.open_page(page_name_to_open);
         }
         else
         {
            send_message_to_stage(command);
         }
      }

      break;
   }
   return;
}

void Stage::open_start_page()
{
   multiplex_menu.open_page(start_page_name);
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


