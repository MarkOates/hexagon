#include <iostream>
#include <sstream>


#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


#include <allegro_flare/placement2d.h>


#include <Blast/StringSplitter.hpp>
#include <Blast/KeyboardCommandMapper.hpp>
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>

using namespace Blast;


#include <Hexagon/Logo.hpp>

using namespace Hexagon;


std::string resource(std::vector<std::string> components, std::string filename="")
{
   std::string result;

   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   for (auto &component : components) al_append_path_component(path, component.c_str());

   al_set_path_filename(path, filename.c_str());
   result = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);

   std::cout << result << std::endl;

   return result;
}



std::string::size_type rfind_first_not_of(const std::string& s,
        const std::string& delims, std::string::size_type pos)
{
    std::string::size_type p = pos;
    while (delims.find(s[p]) != std::string::npos) {
        if (p == 0) // not found
            return std::string::npos;
        --p;
    }
    return p;
}

std::string::size_type rfind_first_of(const std::string& s,
        const std::string& delims, std::string::size_type pos)
{
    std::string::size_type p = pos;
    while (delims.find(s[p]) == std::string::npos) {
        if (p == 0) // not found
            return std::string::npos;
        --p;
    }
    return p;
}

#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>        // std::size_t

int find_whitespace(std::string &string, int current_cursor_position)
{
  std::size_t position = string.find_first_of(" \n\r\t", current_cursor_position);
  if (position != std::string::npos) return position;
  return 0;
}

int find_non_whitespace(std::string &string, int current_cursor_position)
{
  std::size_t position = string.find_first_not_of(" \n\r\t", current_cursor_position);
  if (position != std::string::npos) return position;
  return 0;
}

int rfind_whitespace(std::string &string, int current_cursor_position)
{
  std::size_t position = rfind_first_of(string, " \n\r\t", current_cursor_position);
  if (position != std::string::npos) return position;
  return 0;
}

int rfind_non_whitespace(std::string &string, int current_cursor_position)
{
  std::size_t position = rfind_first_not_of(string, " \n\r\t", current_cursor_position);
  if (position != std::string::npos) return position;
  return 0;
}


#include <fstream>

bool read_file(std::vector<std::string> &lines, std::string filename)
{
   std::ifstream file(filename);

   lines.clear();

   if (file.is_open())
   {
      std::string line;
      while (getline(file, line)) { lines.push_back(line); }
      file.close();
   }

   return true;
}

bool save_file(std::vector<std::string> &lines, std::string filename)
{
   std::ofstream file(filename);

   if (file.is_open())
   {
      for (auto &line : lines) file << line << '\n';
      file.close();
   }
   else
   {
      throw std::runtime_error("couldn't save file -- file failed at is_open()");
   }

   return true;
}



#include <string>
#include <vector>


class Stage
{
public:
   enum mode_t
   {
      EDIT,
      INSERT,
   };

private:
   std::vector<std::string> lines;
   int cursor_x;
   int cursor_y;

   mode_t mode;

   std::string filename;


   // presentation

   placement2d place;
   int first_line_num;

public:
   Stage(std::string filename, placement2d place)
      : lines()
      , cursor_x(0)
      , cursor_y(0)
      , mode(EDIT)
      , filename(filename)
      , place(place)
      , first_line_num(0)
   {}

   // accessors

   bool set_content(std::string content)
   {
      lines = StringSplitter(content, '\n').split();
      return true;
   }

   bool set_content(std::vector<std::string> content)
   {
      lines = content;
      return true;
   }

   placement2d &get_place_ref()
   {
      return place;
   }

   // inference

   int num_lines() {
      return lines.size();
   }

   int num_columns() {
      if (cursor_y >= lines.size()) return -1;
      return lines[cursor_y].length();
   }

   std::string &current_line_ref()
   {
      return lines[cursor_y];
   }

   std::string &next_line_ref()
   {
      return lines[cursor_y+1];
   }

   std::string get_current_mode_string()
   {
      if (mode == EDIT) return "EDIT";
      if (mode == INSERT) return "INSERT";
      return "---";
   }

   // actions

   bool move_cursor_up()
   {
      if (num_lines() <= 0) return false;
      cursor_y -= 1;
      return true;
   }
   bool move_cursor_down()
   {
      if (cursor_y >= num_lines()) return false;
      cursor_y += 1;
      return true;
   }
   bool move_cursor_left()
   {
      cursor_x -= 1;
      return true;
   }
   bool move_cursor_right()
   {
      cursor_x += 1;
      return true;
   }
   bool move_cursor_jump_to_next_word()
   {
      int position = 0;

      position = find_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; }

      position = find_non_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; return true; }

      return false;
   }
   bool move_cursor_jump_to_previous_word()
   {
      int position = 0;

      position = rfind_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; }

      position = rfind_non_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; return true; }

      return false;
   }
   bool move_cursor_to_start_of_line()
   {
      cursor_x = 0;
      return true;
   }
   bool delete_character()
   {
      current_line_ref().erase(cursor_x, 1);
      return true;
   }
   bool join_lines()
   {
      lines[cursor_y] += lines[cursor_y+1];
      lines.erase(lines.begin() + cursor_y+1);
      return true;
   }
   bool split_lines()
   {
     lines.insert(lines.begin() + cursor_y + 1, lines[cursor_y].substr(cursor_x));
     current_line_ref().erase(cursor_x);
     return true;
   }
   bool insert_string(std::string string)
   {
      current_line_ref().insert(cursor_x, string);
      return true;
   }
   bool save_file()
   {
      ::save_file(lines, filename);
      return true;
   }

   // editor mode
   bool set_insert_mode()
   {
      mode = INSERT;
      return true;
   }
   bool set_edit_mode()
   {
      mode = EDIT;
      return true;
   }


   // presentation

   // actions

   bool offset_first_line_num(int delta)
   {
      first_line_num += delta;
      if (first_line_num < 0) first_line_num = 0;
      if (first_line_num >= lines.size()) first_line_num = lines.size()-1;
      return true;
   }

   bool offset_cursor_position_y(int delta)
   {
      cursor_y += delta;
      if (cursor_y < 0) cursor_y = 0;
      if (cursor_y >= lines.size()) cursor_y = lines.size()-1;
      return true;
   }

   bool move_stage_up(float distance=100)
   {
      place.position.y += distance;
      return true;
   }

   bool move_stage_down(float distance=100)
   {
      place.position.y -= distance;
      return true;
   }

   bool scale_stage_delta(float delta)
   {
      place.scale += vec2d(delta, delta);
      return true;
   }

   void render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height)
   {
      place.start_transform();

      // render cursor
      float _cursor_y = cursor_y - first_line_num;
      switch(mode)
      {
      case EDIT:
         al_draw_filled_rectangle(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width + cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"));
         break;
      case INSERT:
         al_draw_line(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"), 3);
         break;
      }


      // render lines
      for (int line_number = first_line_num; line_number < lines.size(); line_number++)
      {
         al_draw_text(font, al_color_name("white"), 0, (line_number-first_line_num)*cell_height, ALLEGRO_ALIGN_LEFT, lines[line_number].c_str());
         std::stringstream ss;
         ss << (line_number+1);
         al_draw_text(font, al_color_name("darkolivegreen"), -20, (line_number-first_line_num)*cell_height, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());
      }

      place.restore_transform();

      // render edit mode
      al_draw_text(font, mode == EDIT ? al_color_name("red") : al_color_name("lime"), al_get_display_width(display)/2, al_get_display_height(display)-al_get_font_line_height(font)*2, ALLEGRO_ALIGN_CENTER, get_current_mode_string().c_str());
   }

   // events

   static const std::string MOVE_CURSOR_UP;
   static const std::string MOVE_CURSOR_DOWN;
   static const std::string MOVE_CURSOR_LEFT;
   static const std::string MOVE_CURSOR_RIGHT;
   static const std::string MOVE_CURSOR_JUMP_TO_NEXT_WORD;
   static const std::string MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD;
   static const std::string DELETE_CHARACTER;
   static const std::string INSERT_STRING;
   static const std::string SET_INSERT_MODE;
   static const std::string SET_EDIT_MODE;
   static const std::string JOIN_LINES;
   static const std::string SPLIT_LINES;
   static const std::string MOVE_CURSOR_TO_START_OF_LINE;
   static const std::string SAVE_FILE;
   static const std::string MOVE_STAGE_UP;
   static const std::string MOVE_STAGE_DOWN;
   static const std::string SCALE_STAGE_UP;
   static const std::string SCALE_STAGE_DOWN;
   static const std::string OFFSET_FIRST_LINE_NUM_DOWN;
   static const std::string OFFSET_FIRST_LINE_NUM_UP;
   static const std::string OFFSET_CURSOR_POSITION_Y_DOWN;
   static const std::string OFFSET_CURSOR_POSITION_Y_UP;

   void process_local_event(std::string event_name, intptr_t data1=0, intptr_t data2=0)
   {
      try {
         if (event_name == MOVE_CURSOR_UP) move_cursor_up();
         else if (event_name == MOVE_CURSOR_DOWN) move_cursor_down();
         else if (event_name == MOVE_CURSOR_LEFT) move_cursor_left();
         else if (event_name == MOVE_CURSOR_RIGHT) move_cursor_right();
         else if (event_name == MOVE_CURSOR_JUMP_TO_NEXT_WORD) move_cursor_jump_to_next_word();
         else if (event_name == MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD) move_cursor_jump_to_previous_word();
         else if (event_name == DELETE_CHARACTER) delete_character();
         else if (event_name == INSERT_STRING) insert_string(*(std::string *)data1);
         else if (event_name == SET_INSERT_MODE) set_insert_mode();
         else if (event_name == SET_EDIT_MODE) set_edit_mode();
         else if (event_name == JOIN_LINES) join_lines();
         else if (event_name == SPLIT_LINES) split_lines();
         else if (event_name == MOVE_CURSOR_TO_START_OF_LINE) move_cursor_to_start_of_line();
         else if (event_name == SAVE_FILE) save_file();
         else if (event_name == MOVE_STAGE_UP) move_stage_up();
         else if (event_name == MOVE_STAGE_DOWN) move_stage_down();
         else if (event_name == SCALE_STAGE_UP) scale_stage_delta(0.1);
         else if (event_name == SCALE_STAGE_DOWN) scale_stage_delta(-0.1);
         else if (event_name == OFFSET_FIRST_LINE_NUM_DOWN) offset_first_line_num(10);
         else if (event_name == OFFSET_FIRST_LINE_NUM_UP) offset_first_line_num(-10);
         else if (event_name == OFFSET_CURSOR_POSITION_Y_DOWN) offset_cursor_position_y(10);
         else if (event_name == OFFSET_CURSOR_POSITION_Y_UP) offset_cursor_position_y(-10);
      }
      catch (const std::exception &e)
      {
         std::cout << "💥 cannot execute \"" << event_name << "\"" << std::endl;
      }

      std::cout << event_name << std::endl;
   }

   void process_event(ALLEGRO_EVENT &event)
   {
      //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
      //bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::vector<std::string> comand_identifier);
      KeyboardCommandMapper edit_mode__keyboard_command_mapper;
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, true,  false, false, { Stage::MOVE_CURSOR_TO_START_OF_LINE, Stage::MOVE_CURSOR_JUMP_TO_NEXT_WORD, Stage::SET_INSERT_MODE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, false, false, false, { Stage::MOVE_CURSOR_DOWN });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, true,  false, false, { Stage::JOIN_LINES });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K, false, false, false, { Stage::MOVE_CURSOR_UP });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_H, false, false, false, { Stage::MOVE_CURSOR_LEFT });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_L, false, false, false, { Stage::MOVE_CURSOR_RIGHT });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_W, false, false, false, { Stage::MOVE_CURSOR_JUMP_TO_NEXT_WORD });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_B, false, false, false, { Stage::MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_X, false, false, false, { Stage::DELETE_CHARACTER });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, false, false, false, { Stage::SET_INSERT_MODE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_0, false, false, false, { Stage::MOVE_CURSOR_TO_START_OF_LINE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, true, false, { Stage::SAVE_FILE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_U, false, true, false, { Stage::OFFSET_FIRST_LINE_NUM_UP, Stage::OFFSET_CURSOR_POSITION_Y_UP });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_D, false, true, false, { Stage::OFFSET_FIRST_LINE_NUM_DOWN, Stage::OFFSET_CURSOR_POSITION_Y_DOWN });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_EQUALS, false, true, false, { Stage::SCALE_STAGE_UP });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_MINUS, false, true, false, { Stage::SCALE_STAGE_DOWN });


      //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
      //bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::vector<std::string> comand_identifier);
      KeyboardCommandMapper insert_mode__keyboard_command_mapper;
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, { Stage::SET_EDIT_MODE });
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKSPACE, false, false, false, { Stage::MOVE_CURSOR_LEFT, Stage::DELETE_CHARACTER });
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, { Stage::SPLIT_LINES, Stage::MOVE_CURSOR_DOWN, Stage::MOVE_CURSOR_TO_START_OF_LINE });
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, true, false, { Stage::SAVE_FILE });


      switch(mode)
      {
      case EDIT:
         switch(event.type)
         {
         case ALLEGRO_EVENT_KEY_DOWN:
            break;
         case ALLEGRO_EVENT_KEY_UP:
            break;
         case ALLEGRO_EVENT_KEY_CHAR:
            bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL || event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
            bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
            std::vector<std::string> mapped_events = edit_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
            for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
            break;
         }
         break;
      case INSERT:
         switch(event.type)
         {
         case ALLEGRO_EVENT_KEY_DOWN:
            break;
         case ALLEGRO_EVENT_KEY_UP:
            break;
         case ALLEGRO_EVENT_KEY_CHAR:
            bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL || event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
            bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
            std::vector<std::string> mapped_events = insert_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
            for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
            if (mapped_events.empty())
            {
               char character = (char)(event.keyboard.unichar);
               std::string *string = new std::string(" ");
               string->operator[](0) = character;
               process_local_event(INSERT_STRING, (intptr_t)string);
               process_local_event(MOVE_CURSOR_RIGHT);
               delete string;
            }
            break;
         }
      }
   }
};


std::string const Stage::MOVE_CURSOR_UP = "MOVE_CURSOR_UP";
std::string const Stage::MOVE_CURSOR_DOWN = "MOVE_CURSOR_DOWN";
std::string const Stage::MOVE_CURSOR_LEFT = "MOVE_CURSOR_LEFT";
std::string const Stage::MOVE_CURSOR_RIGHT = "MOVE_CURSOR_RIGHT";
std::string const Stage::MOVE_CURSOR_JUMP_TO_NEXT_WORD = "MOVE_CURSOR_JUMP_TO_NEXT_WORD";
std::string const Stage::MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD = "MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD";
std::string const Stage::DELETE_CHARACTER = "DELETE_CHARACTER";
std::string const Stage::INSERT_STRING = "INSERT_STRING";
std::string const Stage::SET_INSERT_MODE = "SET_INSERT_MODE";
std::string const Stage::SET_EDIT_MODE = "SET_EDIT_MODE";
std::string const Stage::JOIN_LINES = "JOIN_LINES";
std::string const Stage::SPLIT_LINES = "SPLIT_LINES";
std::string const Stage::MOVE_CURSOR_TO_START_OF_LINE = "MOVE_CURSOR_TO_START_OF_LINE";
std::string const Stage::SAVE_FILE = "SAVE_FILE";
std::string const Stage::MOVE_STAGE_UP = "MOVE_STAGE_UP";
std::string const Stage::MOVE_STAGE_DOWN = "MOVE_STAGE_DOWN";
std::string const Stage::OFFSET_FIRST_LINE_NUM_UP = "OFFSET_FIRST_LINE_NUM_UP";
std::string const Stage::OFFSET_FIRST_LINE_NUM_DOWN = "OFFSET_FIRST_LINE_NUM_DOWN";
std::string const Stage::OFFSET_CURSOR_POSITION_Y_UP = "OFFSET_CURSOR_POSITION_Y_UP";
std::string const Stage::OFFSET_CURSOR_POSITION_Y_DOWN = "OFFSET_CURSOR_POSITION_Y_DOWN";
std::string const Stage::SCALE_STAGE_UP = "SCALE_STAGE_UP";
std::string const Stage::SCALE_STAGE_DOWN = "SCALE_STAGE_DOWN";


const std::string sonnet = R"END(Is it thy will thy image should keep open
My heavy eyelids to the weary night?
Dost thou desire my slumbers should be broken,
While shadows like to thee do mock my sight?
Is it thy spirit that thou send'st from thee
So far from home into my deeds to pry,
To find out shames and idle hours in me,
The scope and tenor of thy jealousy?
O, no! thy love, though much, is not so great:
It is my love that keeps mine eye awake;
Mine own true love that doth my rest defeat,
To play the watchman ever for thy sake:
For thee watch I whilst thou dost wake elsewhere,
From me far off, with others all too near.

- William Shakespere)END";


void run_program(std::string filename)
{
   if (!al_init()) std::cerr << "al_init() failed" << std::endl;
   if (!al_init_font_addon()) std::cerr << "al_init_font_addon() failed" << std::endl;
   if (!al_init_ttf_addon()) std::cerr << "al_init_ttf_addon() failed" << std::endl;

   if (!al_install_keyboard()) std::cerr << "al_install_keyboard() failed" << std::endl;

   //ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   //al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
   //std::cout << al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP) << std::endl;
   //al_destroy_path(resource_path);

   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

   al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *consolas_font = al_load_font(resource({"data", "fonts"}, "consolas.ttf").c_str(), 30, 0);

   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));

   float logo_radius = 60;
   Logo logo(display_width/2, display_height/2 - logo_radius * 1.4, logo_radius, al_color_name("darkviolet"), 3);
   logo.render();
   al_draw_text(consolas_font, al_color_name("darkviolet"), display_width/2, display_height/2, ALLEGRO_ALIGN_CENTER, "hexagon");
   al_draw_text(consolas_font, al_color_name("gray"), display_width/2, display_height/2+al_get_font_line_height(consolas_font), ALLEGRO_ALIGN_CENTER, filename.c_str());


   al_flip_display();


   placement2d place(100, 20, 400, 400);
   place.align = vec2d(0, 0);
   place.scale = vec2d(0.65, 0.65);
   Stage stage(filename.empty() ? "~TMP.txt" : filename, place);

   std::vector<std::string> lines;
   if (!filename.empty()) read_file(lines, filename);
   filename.empty() ? stage.set_content(sonnet) : stage.set_content(lines);

   bool shutdown_program = false;
   bool first_load = true;


   while(!shutdown_program)
   {
      ALLEGRO_EVENT this_event;
      if (!first_load) al_wait_for_event(event_queue, &this_event);
      first_load = false;

      stage.process_event(this_event);

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
         shutdown_program = true;
         break;
      }

      al_clear_to_color(al_color_name("black"));
      stage.render(display, consolas_font, al_get_text_width(consolas_font, " "), al_get_font_line_height(consolas_font));
      al_flip_display();
   }


   al_destroy_event_queue(event_queue);
   al_destroy_font(consolas_font);
   al_destroy_display(display);
}

int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=0; i<argc; i++) args.push_back(argv[i]);
   CommandLineFlaggedArgumentsParser command_line_flagged_arguments_parser(args);

   std::vector<std::vector<std::string>> filenames = command_line_flagged_arguments_parser.get_flagged_args("-f");
   std::vector<std::string> first_filenames_set = filenames.empty() ? std::vector<std::string>{} : filenames[0];
   std::string first_filename = first_filenames_set.empty() ? "" : first_filenames_set[0];

   run_program(first_filename);
   return 0;
}


