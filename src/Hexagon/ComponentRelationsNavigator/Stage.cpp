

#include <Hexagon/ComponentRelationsNavigator/Stage.hpp>
#include <iostream>


namespace Hexagon
{
namespace ComponentRelationsNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, std::string>> dependents_menu_items, std::vector<std::tuple<std::string, std::string>> relatives_menu_items, std::vector<std::tuple<std::string, std::string>> dependencies_menu_items)
   : StageInterface(StageInterface::COMPONENT_RELATIONS_NAVIGATOR)
   , font_bin(font_bin)
   , dependents_menu_items(dependents_menu_items)
   , relatives_menu_items(relatives_menu_items)
   , dependencies_menu_items(dependencies_menu_items)
   , dependents_menu(font_bin, "Dependents", dependents_menu_items)
   , relatives_menu(font_bin, "Relatives", relatives_menu_items)
   , dependencies_menu(font_bin, "Dependencies", dependencies_menu_items)
   , dependents_menu_place(-400, 0, 0)
   , relatives_menu_place(0, 0, 0)
   , dependencies_menu_place(400, 0, 0)
   , initialized(false)
{
}


Stage::~Stage()
{
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::initialize()
{
   dependents_menu.set_active(false);
   relatives_menu.set_active(true);
   dependencies_menu.set_active(false);
   return;
}

void Stage::render()
{
   placement3d &place = get_place();
   place.start_transform();
      dependents_menu_place.start_transform();
         dependents_menu.render();
      dependents_menu_place.restore_transform();
      relatives_menu_place.start_transform();
         relatives_menu.render();
      relatives_menu_place.restore_transform();
      dependencies_menu_place.start_transform();
         dependencies_menu.render();
      dependencies_menu_place.restore_transform();
   place.restore_transform();
   return;
}

void Stage::move_cursor_up()
{
   dependents_menu.move_cursor_up();
   relatives_menu.move_cursor_up();
   dependencies_menu.move_cursor_up();
   return;
}

void Stage::move_cursor_down()
{
   dependents_menu.move_cursor_down();
   relatives_menu.move_cursor_down();
   dependencies_menu.move_cursor_down();
   return;
}

void Stage::move_cursor_left()
{
   // not yet implemented
   return;
}

void Stage::move_cursor_right()
{
   // not yet implemented
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_CHAR:
     switch(event.keyboard.keycode)
     {
       case ALLEGRO_KEY_K:
         move_cursor_up();
         break;
       case ALLEGRO_KEY_J:
         move_cursor_down();
         break;
       case ALLEGRO_KEY_H:
         move_cursor_left();
         break;
       case ALLEGRO_KEY_L:
         move_cursor_right();
         break;
       case ALLEGRO_KEY_ENTER:
         emit_submission();
         break;
     }
     break;
   }
   return;
}

void Stage::set_upcase(bool upcase)
{
   dependents_menu.set_upcase(upcase);
   relatives_menu.set_upcase(upcase);
   dependencies_menu.set_upcase(upcase);
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return;
}

void Stage::emit_submission()
{
   std::cout << "DUMMY_MESSAGE: Sumitting ComponentRelationsNavigator/Stage with current selections (\""
             << dependents_menu.get_current_list_item_identifier() << ", "
             << relatives_menu.get_current_list_item_identifier() << ", "
             << dependencies_menu.get_current_list_item_identifier() << ")"
             << "\"" << std::endl;
}
} // namespace ComponentRelationsNavigator
} // namespace Hexagon


