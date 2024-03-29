#pragma once


#include <Hexagon/CodePoint.hpp>
#include <Hexagon/CodeRange.hpp>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Selection
      {
      private:
         std::vector<CodeRange> code_ranges;

      protected:


      public:
         Selection(std::vector<CodeRange> code_ranges={});
         ~Selection();

         std::vector<CodeRange> get_code_ranges() const;
         bool is_empty();
         void clear();
         void add(CodeRange code_range={});
         bool clear_select_lines(std::vector<int> line_indices={});
         bool push_down_from(int starting_on_line=0, int num_lines_to_push_down=0);
         bool pull_up_from(int starting_on_line=0, int num_lines_to_pull_up=0);
         CodePoint find_next_from(int position_x=0, int position_y=0);
         CodePoint find_previous_from(int position_x=0, int position_y=0);
      };
   }
}



