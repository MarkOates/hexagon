#pragma once



#include <allegro5/allegro_font.h>
#include <allegro_flare/placement2d.h>
#include <Hexagon/CodeMessagePoint.hpp>



class CodeMessagePointRenderer
{
private:
   CodeMessagePoint code_message_point;
   int current_line_number_offset;
   int line_height;
   int character_width;
   ALLEGRO_FONT *font;
   placement2d place;
   int cursor_x;
   int cursor_y;

public:
   CodeMessagePointRenderer(
      CodeMessagePoint code_message_point,
      ALLEGRO_FONT *font,
      int current_line_number_offset,
      int line_height,
      int character_width,
      int cursor_x,
      int cursor_y
   );

   void render();
};


