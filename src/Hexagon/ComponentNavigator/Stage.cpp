

#include <Hexagon/ComponentNavigator/Stage.hpp>
#include <iostream>
#include <iostream>
#include <iostream>
#include <Blast/KeyboardCommandMapper.hpp>


namespace Hexagon
{
namespace ComponentNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::FILE_NAVIGATOR)
{
}


Stage::~Stage()
{
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
std::cout << "LocalEvent::" << event_name << std::endl;

try
{
   bool executed = false;

   //if (event_name == "refresh_list")
   {
     executed = true;
     //refresh_list();
   }
}
catch (const std::exception &exception)
{
   std::cerr << ">BOOM< cannot execute \"" << event_name << "\".  The following exception occurred: " << exception.what() << std::endl;
}

}

bool Stage::save_file()
{
return true;

}

void Stage::process_event(ALLEGRO_EVENT& event)
{
KeyboardCommandMapper keyboard_command_mapper;
                                           // al_keycodee, shift, ctrl, alt, command, { command_identifier }
//static const std::string SET_NODE_ROOT_TO_SYSTEM_ROOT_DIRECTORY = "set_node_root_to_system_root_directory";

                                   // al_keycodee,         shift, ctrl, alt, command, { command_identifier }
//keyboard_command_mapper.set_mapping(ALLEGRO_KEY_FULLSTOP,  false, false, false, false, { SET_NODE_ROOT_TO_REPOS_DIRECTORY, REFRESH_LIST, MOVE_CURSOR_TO_TOP });

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
   bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
   bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
   bool ctrl_or_command = ctrl || command;
   std::vector<std::string> mapped_events = keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl_or_command, alt);
   if (!mapped_events.empty()) event_caught = true;
   for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
   break;
}
return;

}
} // namespace ComponentNavigator
} // namespace Hexagon


