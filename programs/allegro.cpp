#include <iostream>


#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


#include <allegro_flare/placement2d.h>


#include <Blast/StringSplitter.hpp>
#include <Blast/KeyboardCommandMapper.hpp>


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


using namespace Blast;


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

public:
   Stage()
      : lines()
      , cursor_x(0)
      , cursor_y(0)
      , mode(EDIT)
   {}

   // accessors

   bool set_content(std::string contnent)
   {
      lines = StringSplitter(contnent, '\n').split();
      return true;
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
   bool delete_character()
   {
      current_line_ref().erase(cursor_x, 1);
      return true;
   }
   bool insert_string(std::string string)
   {
      current_line_ref().insert(cursor_x, string);
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

   void render(ALLEGRO_DISPLAY *display, placement2d place, ALLEGRO_FONT *font, int cell_width, int cell_height)
   {
      place.start_transform();

      // render cursor
      switch(mode)
      {
      case EDIT:
         al_draw_filled_rectangle(cursor_x*cell_width, cursor_y*cell_height, cursor_x*cell_width + cell_width, cursor_y*cell_height + cell_height, al_color_name("gray"));
         break;
      case INSERT:
         al_draw_line(cursor_x*cell_width, cursor_y*cell_height, cursor_x*cell_width, cursor_y*cell_height + cell_height, al_color_name("gray"), 3);
         break;
      }


      // render lines
      int line_number = 0;
      for (auto &line : lines)
      {
         al_draw_text(font, al_color_name("white"), 0, line_number*cell_height, ALLEGRO_ALIGN_LEFT, line.c_str());
         line_number++;
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
   static const std::string DELETE_CHARACTER;
   static const std::string INSERT_STRING;
   static const std::string SET_INSERT_MODE;
   static const std::string SET_EDIT_MODE;

   void process_local_event(std::string event_name, intptr_t data1=0)
   {
      if (event_name == MOVE_CURSOR_UP) move_cursor_up();
      else if (event_name == MOVE_CURSOR_DOWN) move_cursor_down();
      else if (event_name == MOVE_CURSOR_LEFT) move_cursor_left();
      else if (event_name == MOVE_CURSOR_RIGHT) move_cursor_right();
      else if (event_name == MOVE_CURSOR_JUMP_TO_NEXT_WORD) move_cursor_jump_to_next_word();
      else if (event_name == DELETE_CHARACTER) delete_character();
      else if (event_name == INSERT_STRING) insert_string(*(std::string *)data1);
      else if (event_name == SET_INSERT_MODE) set_insert_mode();
      else if (event_name == SET_EDIT_MODE) set_edit_mode();

      std::cout << event_name << std::endl;
   }

   void process_event(ALLEGRO_EVENT &event)
   {
      //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
      KeyboardCommandMapper edit_mode__keyboard_command_mapper;
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, false, false, false, { Stage::MOVE_CURSOR_DOWN });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K, false, false, false, { Stage::MOVE_CURSOR_UP });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_H, false, false, false, { Stage::MOVE_CURSOR_LEFT });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_L, false, false, false, { Stage::MOVE_CURSOR_RIGHT });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_W, false, false, false, { Stage::MOVE_CURSOR_JUMP_TO_NEXT_WORD });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_X, false, false, false, { Stage::DELETE_CHARACTER });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, false, false, false, { Stage::SET_INSERT_MODE });


      //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
      KeyboardCommandMapper insert_mode__keyboard_command_mapper;
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, { Stage::SET_EDIT_MODE });
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKSPACE, false, false, false, { Stage::MOVE_CURSOR_LEFT, Stage::DELETE_CHARACTER });


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
            std::vector<std::string> mapped_events = edit_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, false, false, false);
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
            std::vector<std::string> mapped_events = insert_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, false, false, false);
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
std::string const Stage::DELETE_CHARACTER = "DELETE_CHARACTER";
std::string const Stage::INSERT_STRING = "INSERT_STRING";
std::string const Stage::SET_INSERT_MODE = "SET_INSERT_MODE";
std::string const Stage::SET_EDIT_MODE = "SET_EDIT_MODE";


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



void run_program()
{
   if (!al_init()) std::cerr << "al_init() failed" << std::endl;
   if (!al_init_font_addon()) std::cerr << "al_init_font_addon() failed" << std::endl;
   if (!al_init_ttf_addon()) std::cerr << "al_init_ttf_addon() failed" << std::endl;

   if (!al_install_keyboard()) std::cerr << "al_install_keyboard() failed" << std::endl;

   ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
   al_destroy_path(resource_path);

   al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *consolas_font = al_load_font("data/fonts/consolas.ttf", 28, 0);

   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));


   Stage stage;
   stage.set_content(sonnet);

   bool shutdown_program = false;


   al_draw_text(consolas_font, al_color_name("white"), display_width/2, display_height/2, ALLEGRO_ALIGN_CENTER, "Hello world.");

   al_flip_display();


   while(!shutdown_program)
   {
      ALLEGRO_EVENT this_event;
      al_wait_for_event(event_queue, &this_event);

      stage.process_event(this_event);

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
         shutdown_program = true;
         break;
      }

      placement2d place(100, 100, 400, 400);
      place.align = vec2d(0, 0);
      place.scale = vec2d(0.75, 0.75);
      al_clear_to_color(al_color_name("black"));
      stage.render(display, place, consolas_font, al_get_text_width(consolas_font, " "), al_get_font_line_height(consolas_font));
      al_flip_display();
   }


   al_destroy_display(display);
}



int main(int, char**) {
  run_program();
  return 0;
}

