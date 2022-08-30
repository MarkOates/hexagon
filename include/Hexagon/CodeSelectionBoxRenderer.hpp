#pragma once


#include <CodeRange.hpp>
#include <allegro5/allegro_color.h>
#include <string>
#include <vector>


namespace Hexagon
{
   class CodeSelectionBoxRenderer
   {
   private:
      std::vector<std::string>* lines;
      CodeRange* code_range;
      int first_line_number;
      int cell_width;
      int cell_height;
      ALLEGRO_COLOR selection_color;

   public:
      CodeSelectionBoxRenderer(std::vector<std::string>* lines=nullptr, CodeRange* code_range=nullptr, int first_line_number=0, int cell_width=0, int cell_height=0, ALLEGRO_COLOR selection_color=ALLEGRO_COLOR{1.0*0.4, 0.65*0.4, 0.0*0.4, 1.0*0.4});
      ~CodeSelectionBoxRenderer();

      void set_selection_color(ALLEGRO_COLOR selection_color);
      void render_full_line_selection();
      void render();
      bool verify_line_in_range(int line_num=0);
      int get_line_length(int line_num=0);
   };
}



