

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>
#include <Blast/StringSplitter.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/AdvancedCodeEditor/EventController.hpp>
#include <Hexagon/AdvancedCodeEditor/EventController.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, int num_columns, int num_rows)
   : StageInterface(StageInterface::ADVANCED_CODE_EDITOR)
   , font_bin(font_bin)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , __lines({})
   , text_mesh({nullptr, num_columns, num_rows})
   , initialized(false)
   , advanced_code_editor({})
{
}


Stage::~Stage()
{
}


std::vector<std::string> Stage::get___lines()
{
   return __lines;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &Stage::get_advanced_code_editor_ref()
{
   return advanced_code_editor;
}


std::vector<std::string> Stage::get_lines()
{
return advanced_code_editor.get_lines();

}

Hexagon::AdvancedCodeEditor::Cursor& Stage::get_cursor_ref()
{
return advanced_code_editor.get_cursor_ref();

}

bool Stage::delete_character()
{
return advanced_code_editor.delete_character();

Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();
std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

if (!is_cursor_in_bounds()) return false;
lines[cursor.get_y()].erase(cursor.get_x(), 1);
refresh_text_mesh();
return true;

}

bool Stage::join_lines()
{
return advanced_code_editor.join_lines();

}

bool Stage::split_lines()
{
// TODO
return false;

}

bool Stage::delete_line()
{
// TODO
return false;

}

bool Stage::insert_lines()
{
// TODO
return false;

}

bool Stage::insert_string(std::string string)
{
Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();
std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

if (!is_cursor_in_bounds()) return false;
lines[cursor.get_y()].insert(cursor.get_x(), string);
refresh_text_mesh();
return true;

}

bool Stage::insert_three_spaces_at_start_of_line()
{
// TODO
return false;

}

bool Stage::cursor_move_up()
{
advanced_code_editor.cursor_move_up();
return true;

}

bool Stage::cursor_move_down()
{
advanced_code_editor.cursor_move_down();
return true;

}

bool Stage::cursor_move_left()
{
advanced_code_editor.cursor_move_left();
return true;

}

bool Stage::cursor_move_right()
{
advanced_code_editor.cursor_move_right();
return true;

}

bool Stage::cursor_move_to(int x, int y)
{
advanced_code_editor.cursor_move_to(x, y);
return true;

}

void Stage::initialize()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
if (initialized) return;

Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();

text_mesh.set_font(obtain_text_font());
text_mesh.initialize();

cursor.set_width(text_mesh.get_cell_width());
cursor.set_height(text_mesh.get_cell_height());

initialized = true;
return;

}

void Stage::set_content(std::string content)
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "set_content" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
advanced_code_editor.set_content(content);
refresh_text_mesh();
return;

}

void Stage::render()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::AdvancedCodeEditor::Renderer renderer(
   &text_mesh,
   &advanced_code_editor.get_cursor_ref(),
   get_place().size.x,
   get_place().size.y
);

get_place().start_transform();
renderer.render();
get_place().restore_transform();

return;

}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
Hexagon::AdvancedCodeEditor::EventController event_controller(this);
event_controller.process_local_event(event_name, action_data);
return;

}

void Stage::process_event(ALLEGRO_EVENT& event)
{
Hexagon::AdvancedCodeEditor::EventController event_controller;
event_controller.process_event(event);
return;

}

ALLEGRO_FONT* Stage::obtain_text_font()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "obtain_text_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
return font_bin->auto_get("Menlo-Regular.ttf -30");

}

bool Stage::is_cursor_in_bounds()
{
return advanced_code_editor.is_cursor_in_bounds();

}

bool Stage::is_cursor_on_last_line()
{
return advanced_code_editor.is_cursor_on_last_line();

}

void Stage::refresh_text_mesh()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "refresh_text_mesh" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
char clear_char = '\0';
ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
ALLEGRO_COLOR on_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

for (unsigned y=0; y<num_rows; y++)
{
   for (unsigned x=0; x<num_columns; x++)
   {
      char char_to_set = clear_char;
      ALLEGRO_COLOR color_to_set = clear_color;

      if (y < lines.size())
      {
         if (x < lines[y].size())
         {
            char_to_set = lines[y][x];
            color_to_set = on_color;
         }
      }

      text_mesh.set_cell_character(x, y, char_to_set);
      text_mesh.set_cell_color(x, y, color_to_set);
   }
}
return;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


