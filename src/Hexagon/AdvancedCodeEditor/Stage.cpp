

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
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
   , lines({})
   , text_mesh({nullptr, num_columns, num_rows})
   , cursor({})
   , initialized(false)
{
}


Stage::~Stage()
{
}


std::vector<std::string> Stage::get_lines()
{
   return lines;
}


Hexagon::AdvancedCodeEditor::Cursor &Stage::get_cursor_ref()
{
   return cursor;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


bool Stage::cursor_move_up()
{
cursor.move_up();
return true;

}

bool Stage::cursor_move_down()
{
cursor.move_down();
return true;

}

bool Stage::cursor_move_left()
{
cursor.move_left();
return true;

}

bool Stage::cursor_move_right()
{
cursor.move_right();
return true;

}

void Stage::initialize()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
if (initialized) return;

text_mesh.set_font(obtain_text_font());
text_mesh.initialize();

cursor.set_width(text_mesh.get_cell_width());
cursor.set_height(text_mesh.get_cell_height());

initialized = true;
return;

}

void Stage::set_initial_content(std::string content)
{
lines = Blast::StringSplitter(content, '\n').split();
refresh_text_mesh();
return;

}

void Stage::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::AdvancedCodeEditor::Renderer renderer(
   &text_mesh,
   &cursor,
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
return;

}

void Stage::process_event(ALLEGRO_EVENT& event)
{
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

void Stage::refresh_text_mesh()
{
char clear_char = '\0';
ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
ALLEGRO_COLOR on_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
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


