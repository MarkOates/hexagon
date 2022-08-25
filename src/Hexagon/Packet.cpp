

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


int Packet::get_searches_count() const
{
   return searches_count;
}


int Packet::get_saves_count() const
{
   return saves_count;
}


int Packet::calculate_score()
{
   // This current technique is naive. Please feel free to confidantly modify this scoring strategy in the future
   return searches_count + saves_count;
}
} // namespace Hexagon


