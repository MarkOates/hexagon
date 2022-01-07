


#include <Hexagon/CodePoint.hpp>



CodePoint::CodePoint(int x, int y)
   : x(x)
   , y(y)
{}



CodePoint::~CodePoint()
{}



int CodePoint::get_x() const { return x; }



int CodePoint::get_y() const { return y; }



void CodePoint::set_x(int x) { this->x = x; }



void CodePoint::set_y(int y) { this->y = y; }



bool operator<(const CodePoint &a, const CodePoint &b)
{
   if (a.get_y() < b.get_y()) return true;
   if (a.get_y() > b.get_y()) return false;
   if (a.get_y() == b.get_y()) return (a.get_x() < b.get_x());
   throw std::runtime_error("Codepoint operator<: unexpected codepath");
}


bool operator==(const CodePoint &a, const CodePoint &b)
{
   if (a.get_x() != b.get_x()) return false;
   if (a.get_y() != b.get_y()) return false;
   return true;
}



std::ostream &operator<<(std::ostream &out, CodePoint &code_point)
{
   out << "(" << code_point.get_x() << ", " << code_point.get_y() << ")" << std::endl;
   return out;
}



