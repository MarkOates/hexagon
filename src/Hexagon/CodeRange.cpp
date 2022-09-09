


#include <Hexagon/CodeRange.hpp>

#include <iostream>



CodeRange::CodeRange(int cursor_anchor_x, int cursor_anchor_y, int cursor_end_x, int cursor_end_y)
   : cursor_anchor_x(cursor_anchor_x)
   , cursor_anchor_y(cursor_anchor_y)
   , cursor_end_x(cursor_end_x)
   , cursor_end_y(cursor_end_y)
{}



CodeRange::~CodeRange() {}



CodePoint CodeRange::infer_cursor_start() const
{
   return std::min(CodePoint(cursor_anchor_x, cursor_anchor_y), CodePoint(cursor_end_x, cursor_end_y));
}



CodePoint CodeRange::infer_cursor_end() const
{
   return std::max(CodePoint(cursor_anchor_x, cursor_anchor_y), CodePoint(cursor_end_x, cursor_end_y));
}


void CodeRange::move(int dx, int dy)
{
   cursor_anchor_x += dx;
   cursor_anchor_y += dy;
   cursor_end_x += dx;
   cursor_end_y += dy;
}



void CodeRange::set_cursor_anchor_x(int x)
{
   this->cursor_anchor_x = x;
}


void CodeRange::set_cursor_anchor_y(int y)
{
   this->cursor_anchor_y = y;
}


void CodeRange::set_cursor_end_x(int x) { cursor_end_x = x; }



void CodeRange::set_cursor_end_y(int y) { cursor_end_y = y; }



bool CodeRange::is_empty()
{
   // TODO: this equation does not mean it's empty, consider re-evaluating
   return cursor_end_y == cursor_anchor_y && cursor_end_x == cursor_anchor_x;
}



int CodeRange::infer_num_lines()
{
   if (is_empty()) return 0;
   CodePoint start = infer_cursor_start();
   CodePoint end = infer_cursor_end();

   return end.get_y() - start.get_y() + 1;
}



bool CodeRange::in_range(int x, int y)
{
  // if at start, in range
  if (y < cursor_anchor_y) return false;
  else if (y > cursor_end_y) return false;
  else if (y == cursor_anchor_y == cursor_end_y)
  {
     if (x < cursor_anchor_x) return false;
     if (x >= cursor_end_x) return false;
     return true;
  }
  else
  {
     return true;
  }


  std::cout << "x: " << x << std::endl;
  std::cout << "y: " << y << std::endl;
  std::cout << "cursor_anchor_x: " << cursor_anchor_x << std::endl;
  std::cout << "cursor_anchor_y: " << cursor_anchor_y << std::endl;
  std::cout << "cursor_end_x: " << cursor_end_x << std::endl;
  std::cout << "cursor_end_y: " << cursor_end_y << std::endl;

  throw std::runtime_error("Hmm, the code never should have gotten here.  There's an error in the logic. debug data "
                           "was dumped to cout."
                          );
}



bool CodeRange::operator==(const CodeRange &other) const
{
   if (cursor_anchor_x != other.cursor_anchor_x) return false;
   if (cursor_anchor_y != other.cursor_anchor_y) return false;
   if (cursor_end_x != other.cursor_end_x) return false;
   if (cursor_end_y != other.cursor_end_y) return false;
   return true;
}


std::ostream &operator<<(std::ostream &out, CodeRange &code_range)
{
   CodePoint start = code_range.infer_cursor_start();
   CodePoint end = code_range.infer_cursor_end();
   out << "(" << start.get_x() << ", " << start.get_y() << ")-(" << end.get_x() << ", " << end.get_y() << ")" << std::endl;
   return out;
}



