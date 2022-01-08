#pragma once



#include <Hexagon/CodePoint.hpp>



class CodeRange // TODO: move into Hexagon:: namespace
{
private:
   int cursor_anchor_x;
   int cursor_anchor_y;
   int cursor_end_x;
   int cursor_end_y;

public:
   CodeRange(int cursor_anchor_x=0, int cursor_anchor_y=0, int cursor_end_x=0, int cursor_end_y=0);
   ~CodeRange();

   CodePoint infer_cursor_start();
   CodePoint infer_cursor_end();
   void set_cursor_end_x(int x); // TODO: remove "cursor" in all method names
   void set_cursor_end_y(int y);
   bool is_empty();
   int infer_num_lines();
   bool in_range(int x, int y);
   bool operator==(const CodeRange &other) const;
};



std::ostream &operator<<(std::ostream &out, CodeRange &code_range);



