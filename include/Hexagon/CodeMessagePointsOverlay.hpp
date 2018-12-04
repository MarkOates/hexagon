#pragma once



#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <Hexagon/CodeMessagePoint.hpp>
#include <string>
#include <vector>



class CodeMessagePointsOverlay
{
public:
   std::string name;
   ALLEGRO_COLOR color;
   std::vector<CodeMessagePoint> code_message_points;

   CodeMessagePointsOverlay(ALLEGRO_COLOR color, std::vector<CodeMessagePoint> code_message_points);
   void render(ALLEGRO_FONT *font, int first_line_number, float line_height, int cursor_x, int cursor_y);
};



