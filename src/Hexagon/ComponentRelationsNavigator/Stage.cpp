

#include <Hexagon/ComponentRelationsNavigator/Stage.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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
   , dependents_menu_place(-700, -200, 0)
   , relatives_menu_place(0, -200, 0)
   , dependencies_menu_place(700, -200, 0)
   , initialized(false)
   , currently_active_menu(nullptr)
   , default_color({0.973, 0.592, 0.078, 1.0})
{
}


Stage::~Stage()
{
}


bool Stage::get_initialized() const
{
   return initialized;
}


Hexagon::Elements::ListMenu* Stage::get_currently_active_menu() const
{
   return currently_active_menu;
}


ALLEGRO_COLOR Stage::get_default_color() const
{
   return default_color;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::initialize()
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::initialize]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::initialize]: error: guard \"(!get_initialized())\" not met");
   }
   //al_color_html("4e2f1a");

   dependents_menu.set_color(default_color);
   relatives_menu.set_color(default_color);
   dependencies_menu.set_color(default_color);

   // default inactive color used to be ALLEGRO_COLOR{0.31, 0.18, 0.1, 1.0};
   //dependents_menu.set_inactive_color(default_inactive_color);
   //relatives_menu.set_inactive_color(default_inactive_color);
   //dependencies_menu.set_inactive_color(default_inactive_color);

   dependents_menu_place.size.x = 600; //dependents_menu.get_width();
   relatives_menu_place.size.x = 600; //relatives_menu.get_width();
   dependencies_menu_place.size.x = 600; //dependencies_menu.get_width();

   dependents_menu_place.align.x = 0.5;
   relatives_menu_place.align.x = 0.5;
   dependencies_menu_place.align.x = 0.5;

   set_currently_active_menu(&relatives_menu);
   initialized = true;

   dependents_menu.set_title_upcase(true);
   relatives_menu.set_title_upcase(true);
   dependencies_menu.set_title_upcase(true);

   dependents_menu.set_menu_items_upcase(false);
   relatives_menu.set_menu_items_upcase(false);
   dependencies_menu.set_menu_items_upcase(false);

   return;
}

void Stage::set_currently_active_menu(Hexagon::Elements::ListMenu* menu)
{
   if (!(menu))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::set_currently_active_menu]: error: guard \"menu\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::set_currently_active_menu]: error: guard \"menu\" not met");
   }
   dependents_menu.set_active(false);
   relatives_menu.set_active(false);
   dependencies_menu.set_active(false);

   this->currently_active_menu = menu;
   if (currently_active_menu) currently_active_menu->set_active(true);

   return;
}

bool Stage::is_currently_active_menu(Hexagon::Elements::ListMenu* currently_active_menu)
{
   return (get_currently_active_menu() == currently_active_menu);
}

void Stage::render()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::render]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::render]: error: guard \"get_initialized()\" not met");
   }
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
   if (is_currently_active_menu(&dependents_menu))
   {
      dependents_menu.move_cursor_up();
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      relatives_menu.move_cursor_up();
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      dependencies_menu.move_cursor_up();
   }
   return;
}

void Stage::move_cursor_down()
{
   if (is_currently_active_menu(&dependents_menu))
   {
      dependents_menu.move_cursor_down();
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      relatives_menu.move_cursor_down();
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      dependencies_menu.move_cursor_down();
   }
   return;
}

void Stage::move_cursor_left()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::move_cursor_left]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::move_cursor_left]: error: guard \"get_initialized()\" not met");
   }
   if (is_currently_active_menu(&dependents_menu))
   {
      set_currently_active_menu(&dependencies_menu);
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      set_currently_active_menu(&dependents_menu);
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      set_currently_active_menu(&relatives_menu);
   }
   else
   {
      // throw an error
   }
   return;
}

void Stage::move_cursor_right()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::move_cursor_right]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::move_cursor_right]: error: guard \"get_initialized()\" not met");
   }
   if (is_currently_active_menu(&dependents_menu))
   {
      set_currently_active_menu(&relatives_menu);
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      set_currently_active_menu(&dependencies_menu);
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      set_currently_active_menu(&dependents_menu);
   }
   else
   {
      // throw an error
   }
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::process_event]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::process_event]: error: guard \"get_initialized()\" not met");
   }
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

std::string Stage::get_current_selection_label_or_empty_string()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::get_current_selection_label_or_empty_string]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::get_current_selection_label_or_empty_string]: error: guard \"get_initialized()\" not met");
   }
   if (!(currently_active_menu))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::get_current_selection_label_or_empty_string]: error: guard \"currently_active_menu\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::get_current_selection_label_or_empty_string]: error: guard \"currently_active_menu\" not met");
   }
   std::string result;

   if (is_currently_active_menu(&dependents_menu))
   {
      result = dependents_menu.get_current_list_item_identifier();
   }
   else if (is_currently_active_menu(&relatives_menu))
   {
      result = relatives_menu.get_current_list_item_identifier();
   }
   else if (is_currently_active_menu(&dependencies_menu))
   {
      result = dependencies_menu.get_current_list_item_identifier();
   }
   else
   {
      std::stringstream error_message;
      error_message << "ComponentRelationsNavigator::Stage::get_current_selection_label_or_empty_string: error:"
                    << "Expecting an active menu, one of [dependents_menu, relatives_menu, dependencies_menu], "
                    << "but there is none.";
      throw std::runtime_error(error_message.str());
   }
   return result;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentRelationsNavigator::Stage::process_local_event]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentRelationsNavigator::Stage::process_local_event]: error: guard \"get_initialized()\" not met");
   }
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


