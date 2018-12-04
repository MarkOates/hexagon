


#include <Hexagon/CodeMessagePointRenderer.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>



CodeMessagePointRenderer::CodeMessagePointRenderer(CodeMessagePoint code_message_point, ALLEGRO_FONT *font, int current_line_number_offset, int line_height, int character_width, int cursor_x, int cursor_y)
   : code_message_point(code_message_point)
   , current_line_number_offset(current_line_number_offset)
   , line_height(line_height)
   , character_width(character_width)
   , font(font)
   , place(0, 0, 2200, 500)
   , cursor_x(cursor_x)
   , cursor_y(cursor_y)
{
   if (!font) throw std::runtime_error("font not valid in CodeMessagePointRenderer");
}



void CodeMessagePointRenderer::render()
{
   float horizontal_padding = 20;
   place.position = vec2d(code_message_point.get_x() * character_width, (code_message_point.get_y()-1)*line_height - (current_line_number_offset)*line_height + line_height*0.5);
   place.align = vec2d(0, 0);
   place.start_transform();
   ALLEGRO_COLOR spot_color, background_color, text_color, outline_color;

   switch(code_message_point.get_type())
   {
   case CodeMessagePoint::POSITION:
      {
         spot_color = al_color_name("dodgerblue");
         outline_color = al_color_name("yellow");
         ALLEGRO_STATE blender_state;
         float padding_x = 2;
         float padding_y = 2;
         float radius = 3;
         float outline_thickness = 2.0;
         bool cursor_at_code_point = ((cursor_x >= code_message_point.get_x()) && (cursor_x < code_message_point.get_x2()) && (code_message_point.get_y()-1) == cursor_y);
         if (!cursor_at_code_point)
         {
            float opacity = 0.6;
            spot_color.r *= opacity; spot_color.g *= opacity, spot_color.b *= opacity; spot_color.a *= opacity;
         }
         al_store_state(&blender_state, ALLEGRO_STATE_BLENDER);
         al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
         al_draw_filled_rounded_rectangle(0-padding_x, -line_height/2.0-padding_y, std::max(10, code_message_point.get_length()*character_width)+padding_x, line_height/2.0+padding_y, radius, radius, spot_color);
         if (cursor_at_code_point) al_draw_rounded_rectangle(0-padding_x, -line_height/2.0-padding_y, std::max(10, code_message_point.get_length()*character_width)+padding_x, line_height/2.0+padding_y, radius, radius, outline_color, outline_thickness);
         al_restore_state(&blender_state);
      }
      break;
   case CodeMessagePoint::ERROR:
      {
         spot_color = al_color_name("red");
         background_color = al_color_name("webmaroon");
         text_color = al_color_name("red");
         float radius = 6.0;
         float padding = 6.0;

         // draw the marker
         al_draw_filled_circle(0, 0, 16, spot_color);

         /// draw the message (if open)
         if (code_message_point.infer_at_point(cursor_x, cursor_y+1))
         {
            al_draw_filled_rounded_rectangle(-padding*2, -padding*2, place.size.x+padding*2, place.size.y+padding*2, radius, radius, al_color_name("black"));
            al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, background_color);
            al_draw_rounded_rectangle(-padding, -padding, place.size.x+padding, place.size.y+padding, radius, radius, text_color, 3.0);
            al_draw_multiline_text(font, text_color, 10, 10, place.size.x - horizontal_padding*2, line_height, ALLEGRO_ALIGN_LEFT, code_message_point.get_message().c_str());
         }
      }
      break;
   case CodeMessagePoint::TEST_FAILURE:
   default:
      {
         spot_color = al_color_name("deeppink");
         background_color = al_color_name("webmaroon");
         text_color = al_color_name("deeppink");
         float radius = 6.0;
         float padding = 6.0;

         // draw the marker
         al_draw_filled_circle(0, 0, 16, spot_color);

         /// draw the message (if open)
         if (code_message_point.infer_at_point(cursor_x, cursor_y+1))
         {
            al_draw_filled_rounded_rectangle(-padding*2, -padding*2, place.size.x+padding*2, place.size.y+padding*2, radius, radius, al_color_name("black"));
            al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, background_color);
            al_draw_rounded_rectangle(-padding, -padding, place.size.x+padding, place.size.y+padding, radius, radius, text_color, 3.0);
            al_draw_multiline_text(font, text_color, 10, 10, place.size.x - horizontal_padding*2, line_height, ALLEGRO_ALIGN_LEFT, code_message_point.get_message().c_str());
         }
      }
      break;
   }

   place.restore_transform();
}



