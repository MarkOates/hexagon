

#include <Hexagon/CodeEditor/Cursor.hpp>




namespace Hexagon
{
namespace CodeEditor
{


Cursor::Cursor(float x, float y, float width, float height)
   : x(x)
   , y(y)
   , width(width)
   , height(height)
{
}


Cursor::~Cursor()
{
}


std::string Cursor::run()
{
   return "Hello World!";
}


} // namespace CodeEditor
} // namespace Hexagon


