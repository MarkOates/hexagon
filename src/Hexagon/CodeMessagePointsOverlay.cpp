


#include <Hexagon/CodeMessagePointsOverlay.hpp>
#include <Hexagon/CodeMessagePointRenderer.hpp>



CodeMessagePointsOverlay::CodeMessagePointsOverlay(ALLEGRO_COLOR color, std::vector<CodeMessagePoint> code_message_points)
   : color(color)
   , code_message_points(code_message_points)
{
   float alpha = 0.2;
   color.r *= alpha; color.g *= alpha; color.b *= alpha; color.a *= alpha;
}



void CodeMessagePointsOverlay::render(ALLEGRO_FONT *font, int first_line_number, float line_height, int cursor_x, int cursor_y)
{
   //al_draw_filled_rectangle(0, 0, 2400, 2000, color);
   int character_width = al_get_text_width(font, "x");
   for (auto &code_message_point : code_message_points)
   {
      CodeMessagePointRenderer code_message_point_renderer(code_message_point, font, first_line_number, al_get_font_line_height(font), character_width, cursor_x, cursor_y);
      code_message_point_renderer.render();
   }
}



