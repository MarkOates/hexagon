

#include <Hexagon/Testing/Comparison/Hexagon/CodeRange.hpp>


//namespace Hexagon (should be but CodeRange is currently at global scope until it is fixed)
//{


//// this is not used because the == operator exists on the CodeRange class itself
//bool operator==(const CodeRange& object, const CodeRange& other_object)
//{
   //CodePoint start = object.infer_cursor_start();
   //CodePoint other_start = other_object.infer_cursor_start();

   //if (start.get_x() != other_start.get_x()) return false;
   //if (start.get_y() != other_start.get_y()) return false;

   //CodePoint end = object.infer_cursor_end();
   //CodePoint other_end = other_object.infer_cursor_end();

   //if (end.get_x() != other_end.get_x()) return false;
   //if (end.get_y() != other_end.get_y()) return false;

   //return true;
//}



void PrintTo(const CodeRange& object, ::std::ostream* os)
{
   CodePoint start = object.infer_cursor_start();
   CodePoint end = object.infer_cursor_end();
   *os << "CodeRange("
       << "start: {" << start.get_x() << ", " << start.get_y() << "}, "
       << "end: {" << end.get_x() << ", " << end.get_y() << "})";
}


//}


