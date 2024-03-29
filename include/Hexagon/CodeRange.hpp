#pragma once



#include <Hexagon/CodePoint.hpp>
#include <set>



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

   CodePoint infer_cursor_start() const;
   CodePoint infer_cursor_end() const;
   void set_cursor_anchor_x(int x);
   void set_cursor_anchor_y(int y);
   void set_cursor_end_x(int x); // TODO: remove "cursor" in all method names
   void set_cursor_end_y(int y);
   void move(int x, int y);
   bool is_empty();
   int infer_num_lines();
   std::set<int> infer_line_numbers();
   bool in_range(int x, int y);
   bool operator==(const CodeRange &other) const;
};



std::ostream &operator<<(std::ostream &out, CodeRange &code_range);



