

#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>



namespace Hexagon
{
namespace AdvancedCodeEditor
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


float Cursor::get_x()
{
   return x;
}


float Cursor::get_y()
{
   return y;
}


float Cursor::get_width()
{
   return width;
}


float Cursor::get_height()
{
   return height;
}


void Cursor::move_up()
{
y -= 1;
}

void Cursor::move_down()
{
y += 1;
}

void Cursor::move_left()
{
x -= 1;
}

void Cursor::move_right()
{
x += 1;
}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


