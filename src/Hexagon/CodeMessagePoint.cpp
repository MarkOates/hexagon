


#include <Hexagon/CodeMessagePoint.hpp>



CodeMessagePoint::CodeMessagePoint(int x, int y, int length, int cursor_placement_offset, std::string message, CodeMessagePoint::type_t type)
   : x(x)
   , y(y)
   , length(length)
   , cursor_placement_offset(cursor_placement_offset)
   , message(message)
   , type(type)
{}



CodeMessagePoint::~CodeMessagePoint()
{}



int CodeMessagePoint::get_x()
{
   return x;
}



int CodeMessagePoint::get_x2()
{
   return x + length;
}



int CodeMessagePoint::get_y()
{
   return y;
}



int CodeMessagePoint::get_length()
{
   return length;
}



int CodeMessagePoint::get_cursor_placement_offset()
{
   return cursor_placement_offset;
}



std::string CodeMessagePoint::get_message()
{
   return message;
}



CodeMessagePoint::type_t CodeMessagePoint::get_type()
{
   return type;
}



bool CodeMessagePoint::infer_at_point(int x, int y)
{
   return (x == this->x && y == this->y);
}



void CodeMessagePoint::move_to(int new_x, int new_y)
{
   this->x = new_x;
   this->y = new_y;
   return;
}

const bool CodeMessagePoint::operator==(const CodeMessagePoint &other)
{
   return true;
}

