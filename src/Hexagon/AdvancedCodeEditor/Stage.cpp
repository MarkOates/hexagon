

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
   , text_mesh({nullptr, num_columns, num_rows})
   , cursor({})
   , initialized(false)
{
}


Stage::~Stage()
{
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
std::vector<std::string> lines = Blast::StringSplitter(content, '\n').split();

int y=0;
for (auto &line : lines)
{
   int x=0;
   if (y >= text_mesh.get_num_rows()) break;
   for (auto &character : line)
   {
      if (x >= text_mesh.get_num_columns()) break;
      text_mesh.set_cell_character(x, y, character);
      x++;
   }
   y++;
}

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
} // namespace AdvancedCodeEditor
} // namespace Hexagon


