

#include <Hexagon/MonitorInfo.hpp>

#include <Hexagon/Errors.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


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


int MonitorInfo::get_num_monitors()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[MonitorInfo::get_num_monitors]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MonitorInfo::get_num_monitors: error: guard \"initialized\" not met");
   }
   return monitors.size();
}

Hexagon::Monitor MonitorInfo::get_primary_monitor_info()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[MonitorInfo::get_primary_monitor_info]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MonitorInfo::get_primary_monitor_info: error: guard \"initialized\" not met");
   }
   for (auto &monitor : monitors)
   {
      if (monitor.infer_is_primary_monitor()) return monitor;
   }

   throw std::runtime_error(Hexagon::Errors::build_error_message(
     "Hexagon::MonitorInfo::obtain_primary_monitor_info",
     "Could not infer primary monitor. This is unexpected behavior, as there should always be a primary "
       "monitor present"
   ));
}

std::string MonitorInfo::dump_monitor_info()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[MonitorInfo::dump_monitor_info]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MonitorInfo::dump_monitor_info: error: guard \"initialized\" not met");
   }
   std::stringstream result;
   int i=0;
   for (auto &monitor : monitors)
   {
      result << "Monitor " << i << ": " << std::endl;
      result << "        x1: " << monitor.get_desktop_x1() << std::endl;
      result << "        y1: " << monitor.get_desktop_y1() << std::endl;
      result << "        x2: " << monitor.get_desktop_x2() << std::endl;
      result << "        y2: " << monitor.get_desktop_y2() << std::endl;
      i++;
   }
   return result.str();
}

void MonitorInfo::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[MonitorInfo::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MonitorInfo::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[MonitorInfo::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MonitorInfo::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   ALLEGRO_MONITOR_INFO info;

   for (int i=0; i<al_get_num_video_adapters(); i++)
   {
      al_get_monitor_info(i, &info);
      monitors.push_back(
         Hexagon::Monitor(
            info.x1,
            info.y1,
            info.x2,
            info.y2,
            al_get_monitor_dpi(i)
         )
      );
   }
   initialized = true;
   return;
}


} // namespace Hexagon


