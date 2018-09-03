#include <iostream>


#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


#include <allegro_flare/placement2d.h>


#include <Blast/StringSplitter.hpp>


using namespace Blast;


#include <string>
#include <vector>


class Stage
{
private:
   std::vector<std::string> lines;
   int cursor_x;
   int cursor_y;

public:
   Stage()
      : lines()
      , cursor_x(0)
      , cursor_y(0)
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

   // presentation

   void render(placement2d place, ALLEGRO_FONT *font, int cell_width, int cell_height)
   {
      place.start_transform();
      // render cursor
      al_draw_filled_rectangle(cursor_x*cell_width, cursor_y*cell_height, cursor_x*cell_width + cell_width, cursor_y*cell_height + cell_height, al_color_name("gray"));

      int line_number = 0;
      for (auto &line : lines)
      {
         al_draw_text(font, al_color_name("white"), 0, line_number*cell_height, ALLEGRO_ALIGN_LEFT, line.c_str());
         line_number++;
      }

      place.restore_transform();
   }
};



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

   ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
   al_destroy_path(resource_path);

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *consolas_font = al_load_font("data/fonts/consolas.ttf", 28, 0);

   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);

   al_draw_text(consolas_font, al_color_name("white"), display_width/2, display_height/2, ALLEGRO_ALIGN_CENTER, "Hello world.");


   Stage stage;
   stage.set_content(sonnet);

   placement2d place(100, 100, 400, 400);
   place.align = vec2d(0, 0);

   stage.render(place, consolas_font, al_get_text_width(consolas_font, " "), al_get_font_line_height(consolas_font));

   al_flip_display();


   sleep(3);
}



int main(int, char**) {
  run_program();
  return 0;
}

