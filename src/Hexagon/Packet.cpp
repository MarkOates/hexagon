

#include <Hexagon/Packet.hpp>



namespace Hexagon
{


Packet::Packet(int searches_count, int saves_count)
   : searches_count(searches_count)
   , saves_count(saves_count)
{
}


Packet::~Packet()
{
}


int Packet::get_searches_count()
{
   return searches_count;
}


int Packet::get_saves_count()
{
   return saves_count;
}


} // namespace Hexagon


