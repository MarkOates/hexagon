

#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>

#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/AdvancedComponentNavigator/EventController.hpp>
#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string project_root, ALLEGRO_COLOR base_text_color, ALLEGRO_COLOR base_backfill_color, bool represents_symlink)
   : StageInterface(StageInterface::COMPONENT_NAVIGATOR)
   , font_bin(nullptr)
   , project_root(project_root)
   , component(project_root)
   , is_focused(true)
   , display(nullptr)
   , font(nullptr)
   , cell_width(10)
   , cell_height(20)
   , base_text_color(base_text_color)
   , base_backfill_color(base_backfill_color)
   , represents_symlink(represents_symlink)
   , MOVE_CURSOR_UP("move_cursor_up")
   , MOVE_CURSOR_DOWN("move_cursor_down")
   , YANK_SELECTED_TEXT_LABEL("yank_selected_text_label")
   , YANK_SELECTED_TEXT_AS_COMPONENT_NAME("yank_selected_text_as_component_name")
   , YANK_SELECTED_TEXT_AS_QUINTESSENCE_FILENAME("yank_selected_text_as_quintessence_filename")
   , YANK_SELECTED_TEXT_AS_INCLUDE_DIRECTIVE("yank_selected_text_as_include_directive")
   , YANK_SELECTED_TEXT_AS_ERROR_MESSAGE_TEMPLATE("yank_selected_text_as_error_message_template")
   , YANK_SELECTED_TEXT_AS_QUINTESSENCE_DEPENDENCY_LINES("yank_selected_text_as_quintessence_dependency_lines")
   , YANK_SELECTED_TEXT_AS_PUBLIC_PARENT_CLASS_LINES("yank_selected_text_as_public_parent_class_lines")
   , YANK_SELECTED_TEXT_AS_INJECTED_DEPENDENCY_PROPERTY("yank_selected_text_as_injected_dependency_property")
{
}


Stage::~Stage()
{
}


void Stage::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
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


AllegroFlare::FontBin* Stage::get_font_bin() const
{
   return font_bin;
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


bool Stage::get_represents_symlink() const
{
   return represents_symlink;
}


Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator &Stage::get_component_ref()
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

   //static const std::string MOVE_CURSOR_UP = "move_cursor_up";
   //static const std::string MOVE_CURSOR_DOWN = "move_cursor_down";
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
      mapping.set_mapping(ALLEGRO_KEY_Y, NO_MODIFIER, { YANK_SELECTED_TEXT_LABEL });
      mapping.set_mapping(ALLEGRO_KEY_C, NO_MODIFIER, { YANK_SELECTED_TEXT_AS_COMPONENT_NAME });
      mapping.set_mapping(ALLEGRO_KEY_F, NO_MODIFIER, { YANK_SELECTED_TEXT_AS_QUINTESSENCE_FILENAME });
      mapping.set_mapping(ALLEGRO_KEY_I, NO_MODIFIER, { YANK_SELECTED_TEXT_AS_INCLUDE_DIRECTIVE });
      mapping.set_mapping(ALLEGRO_KEY_I, SHIFT, { YANK_SELECTED_TEXT_AS_INJECTED_DEPENDENCY_PROPERTY });
      mapping.set_mapping(ALLEGRO_KEY_D, NO_MODIFIER, { YANK_SELECTED_TEXT_AS_QUINTESSENCE_DEPENDENCY_LINES });
      mapping.set_mapping(ALLEGRO_KEY_P, NO_MODIFIER, { YANK_SELECTED_TEXT_AS_PUBLIC_PARENT_CLASS_LINES });
      mapping.set_mapping(ALLEGRO_KEY_E, NO_MODIFIER, { YANK_SELECTED_TEXT_AS_ERROR_MESSAGE_TEMPLATE });
      mapping.set_mapping(ALLEGRO_KEY_A, NO_MODIFIER, { YANK_SELECTED_TEXT_AS_STATIC_CASTED_AS });
   }
   else if (component.is_mode_typing_in_search_bar())
   {
      mapping.set_mapping(ALLEGRO_KEY_TAB, NO_MODIFIER,
         { REFRESH_LIST, MOVE_CURSOR_TO_TOP, SET_MODE_TO_NAVIGATING_LIST });
   }
   return mapping;
}

std::map<std::string, std::function<void(Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator&)>> Stage::build_local_events_dictionary()
{
   std::map<std::string, std::function<void(AdvancedComponentNavigator&)>> local_events = {
      { MOVE_CURSOR_UP, &AdvancedComponentNavigator::move_cursor_up },
      { MOVE_CURSOR_DOWN, &AdvancedComponentNavigator::move_cursor_down },
      { YANK_SELECTED_TEXT_LABEL, &AdvancedComponentNavigator::yank_selected_text_label },
      { YANK_SELECTED_TEXT_AS_COMPONENT_NAME, &AdvancedComponentNavigator::yank_selected_text_as_component_name },
      { YANK_SELECTED_TEXT_AS_QUINTESSENCE_FILENAME, &AdvancedComponentNavigator::yank_selected_text_as_quintessence_filename},
      { YANK_SELECTED_TEXT_AS_INCLUDE_DIRECTIVE,
        &AdvancedComponentNavigator::yank_selected_text_as_include_directive },
      { YANK_SELECTED_TEXT_AS_ERROR_MESSAGE_TEMPLATE,
        &AdvancedComponentNavigator::yank_selected_text_as_error_message_template },
      { YANK_SELECTED_TEXT_AS_QUINTESSENCE_DEPENDENCY_LINES,
        &AdvancedComponentNavigator::yank_selected_text_as_quintessence_dependency_lines },
      { YANK_SELECTED_TEXT_AS_PUBLIC_PARENT_CLASS_LINES,
        &AdvancedComponentNavigator::yank_selected_text_as_public_parent_class_lines },
      { YANK_SELECTED_TEXT_AS_INJECTED_DEPENDENCY_PROPERTY,
        &AdvancedComponentNavigator::yank_selected_text_as_injected_dependency_property },
      { "refresh_list", &AdvancedComponentNavigator::refresh_list },
      { "move_cursor_to_top", &AdvancedComponentNavigator::move_cursor_to_top },
      { "set_mode_to_navigating_list", &AdvancedComponentNavigator::set_mode_to_navigating_list },
      { "set_mode_to_typing_in_search_bar", &AdvancedComponentNavigator::set_mode_to_typing_in_search_bar },
      { YANK_SELECTED_TEXT_AS_STATIC_CASTED_AS,
        &AdvancedComponentNavigator::yank_selected_text_as_static_casted_as },
   };
   return local_events;
}

void Stage::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::AdvancedComponentNavigator::Stage::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::AdvancedComponentNavigator::Stage::render]: error: guard \"font_bin\" not met");
   }
   float backfill_opacity = 0.8f;

   std::vector<std::string> input_hints_tokens = {
      "Y - copy Component/Name"
      "    "
      "C - copy Class::Name"
      "    "
      "f - copy quintessence filename (relative)"
      "    "
      "I - copy #include<>"
      "    "
      "D - copy as dependency item"
      "    "
      "P - copy as parent_classes item"
      "    "
      "SHIFT+I - as injected dependency property"
      "    "
      "E - copy as error message template"
   };

   Hexagon::AdvancedComponentNavigator::Renderer renderer(
      this,
      font_bin,
      is_focused,
      font,
      cell_width,
      cell_height,
      base_backfill_color,
      backfill_opacity,
      base_text_color,
      input_hints_tokens
   );
   renderer.render();
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   using Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator;
   std::map<std::string, std::function<void(AdvancedComponentNavigator&)>> local_events =
      build_local_events_dictionary();
   Hexagon::AdvancedComponentNavigator::EventController event_controller(&component, local_events);
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


} // namespace AdvancedComponentNavigator
} // namespace Hexagon


