

#include <Hexagon/Marker.hpp>



namespace Hexagon
{


Marker::Marker()
   : filename("unset-filename-for-marker-target.txt")
   , line_num(0)
{
}


Marker::~Marker()
{
}


std::string Marker::get_filename()
{
   return filename;
}


int Marker::get_line_num()
{
   return line_num;
}


} // namespace Hexagon


