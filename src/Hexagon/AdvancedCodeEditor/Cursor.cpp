

#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>



namespace Hexagon
{
namespace AdvancedCodeEditor
{


Cursor::Cursor(int x, int y, float width, float height)
   : x(x)
   , y(y)
   , width(width)
   , height(height)
{
}


Cursor::~Cursor()
{
}


void Cursor::set_x(int x)
{
   this->x = x;
}


void Cursor::set_y(int y)
{
   this->y = y;
}


void Cursor::set_width(float width)
{
   this->width = width;
}


void Cursor::set_height(float height)
{
   this->height = height;
}


int Cursor::get_x()
{
   return x;
}


int Cursor::get_y()
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

void Cursor::move_to(int x, int y)
{
this->x = x;
this->y = y;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


