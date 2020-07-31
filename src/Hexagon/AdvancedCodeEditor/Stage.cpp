

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>
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
   , text_mesh({nullptr, num_columns, num_rows})
   , advanced_code_editor({})
   , initialized(false)
{
}


Stage::~Stage()
{
}


Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &Stage::get_advanced_code_editor_ref()
{
   return advanced_code_editor;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
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

text_mesh.set_font(obtain_text_font());
text_mesh.initialize();

advanced_code_editor.cursor_set_width(text_mesh.get_cell_width());
advanced_code_editor.cursor_set_height(text_mesh.get_cell_height());

initialized = true;
return;

}

bool Stage::cursor_move_up()
{
return advanced_code_editor.cursor_move_up();

}

bool Stage::cursor_move_down()
{
return advanced_code_editor.cursor_move_down();

}

bool Stage::cursor_move_left()
{
return advanced_code_editor.cursor_move_left();

}

bool Stage::cursor_move_right()
{
return advanced_code_editor.cursor_move_right();

}

bool Stage::delete_character()
{
bool result = advanced_code_editor.delete_character();
if (result == true) refresh_text_mesh();
return result;

}

bool Stage::join_lines()
{
bool result = advanced_code_editor.join_lines();
if (result == true) refresh_text_mesh();
return result;

}

bool Stage::split_lines()
{
bool result = advanced_code_editor.split_lines();
if (result == true) refresh_text_mesh();
return result;

}

bool Stage::delete_line()
{
bool result = advanced_code_editor.delete_line();
if (result == true) refresh_text_mesh();
return result;

}

bool Stage::insert_string(std::string string)
{
bool result = advanced_code_editor.insert_string(string);
if (result == true) refresh_text_mesh();
return result;

}

bool Stage::insert_lines(std::vector<std::string> lines_to_insert)
{
bool result = advanced_code_editor.insert_lines(lines_to_insert);
if (result == true) refresh_text_mesh();
return result;

}

bool Stage::insert_three_spaces_at_start_of_line()
{
// TODO
return false;

}

bool Stage::cursor_move_to(int x, int y)
{
advanced_code_editor.cursor_move_to(x, y);
return true;

}

void Stage::set_content(std::string content)
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "set_content" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
bool result = advanced_code_editor.set_content(content);
if (result == true) refresh_text_mesh();
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
Hexagon::AdvancedCodeEditor::EventController event_controller(this, build_local_events_dictionary());
event_controller.process_local_event(event_name, action_data);
return;

}

void Stage::process_event(ALLEGRO_EVENT& event)
{
Hexagon::AdvancedCodeEditor::EventController event_controller(this, build_local_events_dictionary());
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

std::vector<std::string> Stage::get_lines()
{
return advanced_code_editor.get_lines();

}

Hexagon::AdvancedCodeEditor::Cursor Stage::get_cursor()
{
return advanced_code_editor.get_cursor_ref();

}

std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> Stage::build_local_events_dictionary()
{
std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> local_events = {
   { "cursor_move_up", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_up },
   { "cursor_move_down", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_down },
   { "cursor_move_left", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_left },
   { "cursor_move_right", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_right },
   { "delete_character", &Hexagon::AdvancedCodeEditor::Stage::delete_character },
   { "split_lines", &Hexagon::AdvancedCodeEditor::Stage::split_lines },
   { "join_lines", &Hexagon::AdvancedCodeEditor::Stage::join_lines },
};
return local_events;

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


