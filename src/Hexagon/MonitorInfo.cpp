

#include <Hexagon/MonitorInfo.hpp>

#include <allegro5/allegro.h>
#include <iostream>


namespace Hexagon
{


MonitorInfo::MonitorInfo()
   : monitors({})
   , initialized(false)
{
}


MonitorInfo::~MonitorInfo()
{
}


void MonitorInfo::initialize()
{
   int num_video_adapters = al_get_num_video_adapters();
   std::cout << "Num video adapters: " << num_video_adapters << std::endl;
   return;
}


} // namespace Hexagon


