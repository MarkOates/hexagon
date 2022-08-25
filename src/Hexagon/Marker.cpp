

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


std::string Marker::get_filename() const
{
   return filename;
}


int Marker::get_line_num() const
{
   return line_num;
}


} // namespace Hexagon


