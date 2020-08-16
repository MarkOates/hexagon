

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/util.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
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
#include <AllegroFlare/Timer.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
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
   , filename("untitled.txt")
   , advanced_code_editor({})
   , input_buffer("")
   , mode(0)
   , initialized(false)
   , offset_y(0.0f)
   , offset_y_updated_at(0.0f)
   , first_row_offset(0)
   , surface_render(nullptr)
{
}


Stage::~Stage()
{
}


void Stage::set_filename(std::string filename)
{
   this->filename = filename;
}


void Stage::set_input_buffer(std::string input_buffer)
{
   this->input_buffer = input_buffer;
}


void Stage::set_first_row_offset(int first_row_offset)
{
   this->first_row_offset = first_row_offset;
}


std::string Stage::get_filename()
{
   return filename;
}


std::string Stage::get_input_buffer()
{
   return input_buffer;
}


bool Stage::get_initialized()
{
   return initialized;
}


float Stage::get_offset_y()
{
   return offset_y;
}


float Stage::get_offset_y_updated_at()
{
   return offset_y_updated_at;
}


int Stage::get_first_row_offset()
{
   return first_row_offset;
}


ALLEGRO_BITMAP* Stage::get_surface_render()
{
   return surface_render;
}


Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &Stage::get_advanced_code_editor_ref()
{
   return advanced_code_editor;
}


std::string &Stage::get_input_buffer_ref()
{
   return input_buffer;
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

surface_render = al_create_bitmap(
   num_columns * text_mesh.get_cell_width(),
   num_rows * text_mesh.get_cell_height()
);
ALLEGRO_STATE previous_render_state;
al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);
al_set_target_bitmap(surface_render);

al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
al_restore_state(&previous_render_state);

advanced_code_editor.cursor_set_width(text_mesh.get_cell_width());
advanced_code_editor.cursor_set_height(text_mesh.get_cell_height());

get_place().size = vec3d(
   num_columns * text_mesh.get_cell_width(),
   num_rows * text_mesh.get_cell_height(),
   0
);

initialized = true;
return;

}

void Stage::destroy()
{
if (surface_render) al_destroy_bitmap(surface_render);
initialized = false;
return;

}

bool Stage::save_file()
{
std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();
::save_file(lines, filename);
//Hexagon::SymlinkToucher symlink_toucher(filename); // this is only needed because of rerun
//symlink_toucher.touch_if_symlink();
return true;

}

bool Stage::set_to_edit_mode()
{
mode = 0;
return true;

}

bool Stage::set_to_insert_mode()
{
mode = 1;
return true;

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

bool Stage::cursor_move_to_start_of_line()
{
return advanced_code_editor.cursor_move_to_start_of_line();

}

bool Stage::cursor_move_to_end_of_line()
{
return advanced_code_editor.cursor_move_to_end_of_line();

}

bool Stage::cursor_jump_to_next_word()
{
return advanced_code_editor.cursor_jump_to_next_word();

}

bool Stage::cursor_jump_to_previous_word()
{
return advanced_code_editor.cursor_jump_to_previous_word();

}

bool Stage::delete_character()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "delete_character" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
bool result = advanced_code_editor.delete_character();
if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
return result;

}

bool Stage::join_lines()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "join_lines" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
bool result = advanced_code_editor.join_lines();
if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
return result;

}

bool Stage::split_lines()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "split_lines" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
bool result = advanced_code_editor.split_lines();
if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
return result;

}

bool Stage::delete_line()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "delete_line" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
bool result = advanced_code_editor.delete_line();
if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
return result;

}

bool Stage::insert_string_from_input_buffer()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "insert_string_from_input_buffer" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
bool result = advanced_code_editor.insert_string(input_buffer);
if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
return result;

}

bool Stage::insert_lines(std::vector<std::string> lines_to_insert)
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "insert_lines" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
bool result = advanced_code_editor.insert_lines(lines_to_insert);
if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
return result;

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
if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
return;

}

bool Stage::insert_three_spaces_at_start_of_line()
{
// TODO
return false;

}

bool Stage::insert_blank_line()
{
return insert_lines({ {} });

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
   { "delete_line", &Hexagon::AdvancedCodeEditor::Stage::delete_line },
   { "insert_string_from_input_buffer", &Hexagon::AdvancedCodeEditor::Stage::insert_string_from_input_buffer },
   { "set_to_edit_mode", &Hexagon::AdvancedCodeEditor::Stage::set_to_edit_mode },
   { "set_to_insert_mode", &Hexagon::AdvancedCodeEditor::Stage::set_to_insert_mode },
   { "cursor_move_to_start_of_line", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_to_start_of_line },
   { "cursor_move_to_end_of_line", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_to_end_of_line },
   { "cursor_jump_to_next_word", &Hexagon::AdvancedCodeEditor::Stage::cursor_jump_to_next_word },
   { "cursor_jump_to_previous_word", &Hexagon::AdvancedCodeEditor::Stage::cursor_jump_to_previous_word },
   { "insert_blank_line", &Hexagon::AdvancedCodeEditor::Stage::insert_blank_line },
   { "save_file", &Hexagon::AdvancedCodeEditor::Stage::save_file },
};
return local_events;

}

KeyboardCommandMapper Stage::build_keyboard_command_mapping_for_edit_mode()
{
KeyboardCommandMapper result;
result.set_mapping(ALLEGRO_KEY_K, 0, { "cursor_move_up" });
result.set_mapping(ALLEGRO_KEY_J, 0, { "cursor_move_down" });
result.set_mapping(ALLEGRO_KEY_H, 0, { "cursor_move_left" });
result.set_mapping(ALLEGRO_KEY_L, 0, { "cursor_move_right" });
result.set_mapping(ALLEGRO_KEY_0, 0, { "cursor_move_to_start_of_line" });
result.set_mapping(ALLEGRO_KEY_4, ALLEGRO_KEYMOD_SHIFT, { "cursor_move_to_end_of_line" });
result.set_mapping(ALLEGRO_KEY_W, 0, { "cursor_jump_to_next_word" });
result.set_mapping(ALLEGRO_KEY_B, 0, { "cursor_jump_to_previous_word" });
result.set_mapping(ALLEGRO_KEY_X, 0, { "delete_character" });
result.set_mapping(ALLEGRO_KEY_BACKSPACE, ALLEGRO_KEYMOD_SHIFT, { "delete_line" });
result.set_mapping(ALLEGRO_KEY_S, KeyboardCommandMapper::COMMAND, { "save_file" });
result.set_mapping(ALLEGRO_KEY_I, 0, { "set_to_insert_mode" });
result.set_mapping(ALLEGRO_KEY_O, 0, {
   "cursor_move_down",
   "insert_blank_line",
   "cursor_move_to_start_of_line",
   "set_to_insert_mode",
   });
return result;

}

KeyboardCommandMapper Stage::build_keyboard_command_mapping_for_insert_mode()
{
KeyboardCommandMapper result;
result.set_mapping(ALLEGRO_KEY_UP, 0, { "cursor_move_up" });
result.set_mapping(ALLEGRO_KEY_DOWN, 0, { "cursor_move_down" });
result.set_mapping(ALLEGRO_KEY_LEFT, 0, { "cursor_move_left" });
result.set_mapping(ALLEGRO_KEY_RIGHT, 0, { "cursor_move_right" });

result.set_mapping(ALLEGRO_KEY_ENTER, 0, { "split_lines", "cursor_move_down", "cursor_move_to_start_of_line" });
result.set_mapping(ALLEGRO_KEY_BACKSPACE, 0, { "cursor_move_left", "delete_character" });

result.set_mapping(ALLEGRO_KEY_OPENBRACE, KeyboardCommandMapper::CTRL, { "set_to_edit_mode" });
result.set_mapping(ALLEGRO_KEY_S, KeyboardCommandMapper::COMMAND, { "save_file" });
return result;

}

bool Stage::cursor_move_to(int x, int y)
{
advanced_code_editor.cursor_move_to(x, y);
return true;

}

void Stage::render()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
placement3d &place = get_place();

Hexagon::AdvancedCodeEditor::Renderer renderer(
   &text_mesh,
   surface_render,
   &advanced_code_editor.get_cursor_ref(),
   place.size.x,
   place.size.y,
   is_in_insert_mode()
);

place.start_transform();
renderer.render();
//al_draw_text(obtain_text_font(), al_color_name("blue"), 20, 20, 0, is_in_insert_mode() ? "INSERT" : "EDIT");
place.restore_transform();

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
KeyboardCommandMapper keyboard_command_mapping;
if (is_in_insert_mode()) keyboard_command_mapping = build_keyboard_command_mapping_for_insert_mode();
else if (is_in_edit_mode()) keyboard_command_mapping = build_keyboard_command_mapping_for_edit_mode();

Hexagon::AdvancedCodeEditor::EventController event_controller(
      this,
      build_local_events_dictionary(),
      keyboard_command_mapping
   );
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

bool Stage::is_in_edit_mode()
{
return mode == 0;

}

bool Stage::is_in_insert_mode()
{
return mode == 1;

}

void Stage::refresh_render_surfaces()
{
AllegroFlare::Timer timer;

std::cout << "------------" << std::endl;
std::cout << "-num dirty cells: " << advanced_code_editor.dirty_cell_count() << std::endl;

timer.reset(); timer.start();
refresh_dirty_cells_on_text_mesh();
timer.pause(); std::cout << " refresh_dirty_cells_on_text_mesh: "
                         << timer.get_elapsed_time_microseconds() << std::endl;

timer.reset(); timer.start();
refresh_dirty_cells_on_surface_render();
timer.pause(); std::cout << " refresh_dirty_cells_on_surface_render: "
                         << timer.get_elapsed_time_microseconds() << std::endl;

advanced_code_editor.dirty_grid_clear();

return;

}

void Stage::refresh_dirty_cells_on_surface_render()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "refresh_dirty_cells_on_surface_render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_STATE previous_render_state;
al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);
al_set_target_bitmap(surface_render);
al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);

text_mesh.render_only_select_cells(advanced_code_editor.get_dirty_cells());

al_restore_state(&previous_render_state);
return;

}

void Stage::refresh_dirty_cells_on_text_mesh()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "refresh_dirty_cells_on_text_mesh" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
char clear_char = '\0';
ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
ALLEGRO_COLOR on_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

int text_mesh_max_x = num_columns;
int text_mesh_max_y = num_rows;

for (auto &cell : advanced_code_editor.get_dirty_cells())
{
   char char_to_set = clear_char;
   ALLEGRO_COLOR color_to_set = clear_color;
   int &x = cell.first;
   int &y = cell.second;

   if (y >= text_mesh_max_y) continue;
   if (x >= text_mesh_max_x) continue;

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
return;

}

void Stage::refresh_text_mesh_respecting_first_row_offset()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Stage" << "::" << "refresh_text_mesh_respecting_first_row_offset" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
char clear_char = '\0';
ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
ALLEGRO_COLOR on_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

for (unsigned y=first_row_offset; y<num_rows; y++)
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


