

#include <Hexagon/ChatGPTIntegration/Chat/Stage.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace ChatGPTIntegration
{
namespace Chat
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::CHAT_GPT_CHAT)
   , font_bin(nullptr)
   , log_view()
   , log_source_filename("/Users/markoates/Repos/ChatGPT/log.txt")
   , initialized(false)
{
}


Stage::~Stage()
{
}


void Stage::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Stage::set_log_source_filename(std::string log_source_filename)
{
   this->log_source_filename = log_source_filename;
}


AllegroFlare::FontBin* Stage::get_font_bin() const
{
   return font_bin;
}


std::string Stage::get_log_source_filename() const
{
   return log_source_filename;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Stage::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::initialize: error: guard \"(!initialized)\" not met");
   }
   get_place().size = {500, 900};
   log_view.set_source_filename(log_source_filename);
   initialized = true;
   return;
}

void Stage::render()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Stage::render]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::render: error: guard \"(!initialized)\" not met");
   }
   ALLEGRO_FONT *dump_font = obtain_dump_font();
   float font_line_height = al_get_font_line_height(dump_font);
   ALLEGRO_COLOR dump_text_color = ALLEGRO_COLOR{0.9, 0.93, 1.0, 1.0};
   float width = 500;

   get_place().start_transform();
   Hexagon::ChatGPTIntegration::Chat::LogView log_view(log_source_filename);
   std::string log_view_text = log_view.get_log_text();
   al_draw_multiline_text(dump_font, dump_text_color, 0, 0, width, font_line_height, ALLEGRO_ALIGN_LEFT,
      log_view_text.c_str()
   );
   // TODO:
   // renderer.render();
   get_place().restore_transform();
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   //Hexagon::AdvancedCodeEditor::EventController event_controller(this, build_local_events_dictionary());
   //event_controller.process_local_event(event_name, action_data);
   return;
    //body_dependency_symbols:
      //- Hexagon::AdvancedCodeEditor::EventController
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   //AllegroFlare::KeyboardCommandMapper keyboard_command_mapping;
   //if (is_in_insert_mode()) keyboard_command_mapping = build_keyboard_command_mapping_for_insert_mode();
   //else if (is_in_edit_mode()) keyboard_command_mapping = build_keyboard_command_mapping_for_edit_mode();

   //Hexagon::AdvancedCodeEditor::EventController event_controller(
         //this,
         //build_local_events_dictionary(),
         //keyboard_command_mapping
      //);
   //event_controller.process_event(event);
   return;
    //body_dependency_symbols:
      //- Hexagon::AdvancedCodeEditor::EventController
}

void Stage::destroy()
{
   //if (surface_render) al_destroy_bitmap(surface_render);
   initialized = false;
   return;
}

ALLEGRO_FONT* Stage::obtain_dump_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Stage::obtain_dump_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::obtain_dump_font: error: guard \"font_bin\" not met");
   }
   float scale = 1.45;
   int font_size = -10 * scale;
   std::stringstream ident;
   ident << "Purista Medium.otf " << (int)(font_size * scale);
   return font_bin->auto_get(ident.str());
}


} // namespace Chat
} // namespace ChatGPTIntegration
} // namespace Hexagon


