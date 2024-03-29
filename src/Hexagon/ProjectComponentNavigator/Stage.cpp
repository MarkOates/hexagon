

#include <Hexagon/ProjectComponentNavigator/Stage.hpp>

#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/ProjectComponentNavigator/EventController.hpp>
#include <Hexagon/ProjectComponentNavigator/Renderer.hpp>


namespace Hexagon
{
namespace ProjectComponentNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string project_root, ALLEGRO_COLOR base_text_color, ALLEGRO_COLOR base_backfill_color)
   : StageInterface(StageInterface::PROJECT_COMPONENT_NAVIGATOR)
   , project_root(project_root)
   , component(project_root)
   , is_focused(true)
   , display(nullptr)
   , font(nullptr)
   , cell_width(10)
   , cell_height(20)
   , base_text_color(base_text_color)
   , base_backfill_color(base_backfill_color)
{
}


Stage::~Stage()
{
}


void Stage::set_project_root(std::string project_root)
{
   this->project_root = project_root;
}


void Stage::set_is_focused(bool is_focused)
{
   this->is_focused = is_focused;
}


void Stage::set_display(ALLEGRO_DISPLAY* display)
{
   this->display = display;
}


void Stage::set_font(ALLEGRO_FONT* font)
{
   this->font = font;
}


void Stage::set_cell_width(int cell_width)
{
   this->cell_width = cell_width;
}


void Stage::set_cell_height(int cell_height)
{
   this->cell_height = cell_height;
}


void Stage::set_base_text_color(ALLEGRO_COLOR base_text_color)
{
   this->base_text_color = base_text_color;
}


void Stage::set_base_backfill_color(ALLEGRO_COLOR base_backfill_color)
{
   this->base_backfill_color = base_backfill_color;
}


std::string Stage::get_project_root() const
{
   return project_root;
}


bool Stage::get_is_focused() const
{
   return is_focused;
}


ALLEGRO_DISPLAY* Stage::get_display() const
{
   return display;
}


ALLEGRO_FONT* Stage::get_font() const
{
   return font;
}


int Stage::get_cell_width() const
{
   return cell_width;
}


int Stage::get_cell_height() const
{
   return cell_height;
}


ALLEGRO_COLOR Stage::get_base_text_color() const
{
   return base_text_color;
}


ALLEGRO_COLOR Stage::get_base_backfill_color() const
{
   return base_backfill_color;
}


Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &Stage::get_component_ref()
{
   return component;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


AllegroFlare::KeyboardCommandMapper Stage::build_keyboard_command_mapping()
{
   constexpr auto NO_MODIFIER = AllegroFlare::KeyboardCommandMapper::NO_MODIFIER;
   constexpr auto SHIFT = AllegroFlare::KeyboardCommandMapper::SHIFT;
   constexpr auto CTRL = AllegroFlare::KeyboardCommandMapper::CTRL;
   constexpr auto ALT = AllegroFlare::KeyboardCommandMapper::ALT;
   constexpr auto COMMAND = AllegroFlare::KeyboardCommandMapper::COMMAND;
   constexpr auto OPTION = AllegroFlare::KeyboardCommandMapper::OPTION;

   AllegroFlare::KeyboardCommandMapper mapping;

   static const std::string MOVE_CURSOR_UP = "move_cursor_up";
   static const std::string MOVE_CURSOR_DOWN = "move_cursor_down";
   static const std::string MOVE_CURSOR_TO_TOP = "move_cursor_to_top";
   static const std::string SET_MODE_TO_NAVIGATING_LIST = "set_mode_to_navigating_list";
   static const std::string SET_MODE_TO_TYPING_IN_SEARCH_BAR = "set_mode_to_typing_in_search_bar";
   static const std::string REFRESH_LIST = "refresh_list";

   if (component.is_mode_navigating_list())
   {
      mapping.set_mapping(ALLEGRO_KEY_J, NO_MODIFIER, { MOVE_CURSOR_DOWN });
      mapping.set_mapping(ALLEGRO_KEY_K, NO_MODIFIER, { MOVE_CURSOR_UP });
      mapping.set_mapping(ALLEGRO_KEY_UP, NO_MODIFIER, { MOVE_CURSOR_UP });
      mapping.set_mapping(ALLEGRO_KEY_DOWN, NO_MODIFIER, { MOVE_CURSOR_DOWN });

      mapping.set_mapping(ALLEGRO_KEY_SLASH, NO_MODIFIER, { SET_MODE_TO_TYPING_IN_SEARCH_BAR });
   }
   else if (component.is_mode_typing_in_search_bar())
   {
      mapping.set_mapping(ALLEGRO_KEY_TAB, NO_MODIFIER,
         { REFRESH_LIST, MOVE_CURSOR_TO_TOP, SET_MODE_TO_NAVIGATING_LIST });
   }
   return mapping;
}

std::map<std::string, std::function<void(Hexagon::ProjectComponentNavigator::ProjectComponentNavigator&)>> Stage::build_local_events_dictionary()
{
   std::map<std::string, std::function<void(Hexagon::ProjectComponentNavigator::ProjectComponentNavigator&)>>
      local_events = {
         { "refresh_list", &ProjectComponentNavigator::refresh_list },
         { "move_cursor_to_top", &ProjectComponentNavigator::move_cursor_to_top },
         { "move_cursor_up", &ProjectComponentNavigator::move_cursor_up },
         { "move_cursor_down", &ProjectComponentNavigator::move_cursor_down },
         { "set_mode_to_navigating_list", &ProjectComponentNavigator::set_mode_to_navigating_list },
         { "set_mode_to_typing_in_search_bar", &ProjectComponentNavigator::set_mode_to_typing_in_search_bar },
      };
   return local_events;
}

void Stage::render()
{
   float backfill_opacity = 0.8f;

   Hexagon::ProjectComponentNavigator::Renderer renderer(
      this, font, cell_width, cell_height, &base_backfill_color, backfill_opacity, &base_text_color
   );
   renderer.render();
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   using Hexagon::ProjectComponentNavigator::ProjectComponentNavigator;
   std::map<std::string, std::function<void(ProjectComponentNavigator&)>> local_events =
      build_local_events_dictionary();
   Hexagon::ProjectComponentNavigator::EventController event_controller(&component, local_events);
   event_controller.process_local_event(event_name, action_data);
   return;
}

void Stage::process_char_event(int keycode, int unichar, bool is_repeat)
{
   if (keycode == ALLEGRO_KEY_BACKSPACE)
   {
      if (component.is_mode_typing_in_search_bar())
      {
         std::string search_text = component.get_search_text();
         if (!search_text.empty())
         {
            search_text.pop_back();
            component.set_search_text(search_text);
         }
      }
   }
   else if (keycode == ALLEGRO_KEY_TAB) {}
   else if (keycode == ALLEGRO_KEY_ENTER) {}
   else if (keycode == ALLEGRO_KEY_ESCAPE) {}
   else if (keycode == ALLEGRO_KEY_DELETE) {}
   else
   {
      if (component.is_mode_typing_in_search_bar())
      {
         std::string search_text = component.get_search_text();
         search_text += unichar;
         component.set_search_text(search_text);
      }
      //search_text += unichar; // <-- for example
   }
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   switch(event.type)
   {
   case ALLEGRO_EVENT_KEY_UP:
      break;
   case ALLEGRO_EVENT_KEY_DOWN:
      break;
   case ALLEGRO_EVENT_KEY_CHAR:
      {
         AllegroFlare::KeyboardCommandMapper keyboard_command_mapper = build_keyboard_command_mapping();
         bool event_caught = false;

         bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
         bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         bool ctrl_or_command = ctrl || command;

         std::vector<std::string> mapped_events =
            keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl_or_command, alt);
         if (!mapped_events.empty()) event_caught = true;
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
         if (!event_caught) process_char_event(event.keyboard.keycode, event.keyboard.unichar, event.keyboard.repeat);
      }
      break;
   }
   return;
}

bool Stage::save_file()
{
   return true;
}


} // namespace ProjectComponentNavigator
} // namespace Hexagon


