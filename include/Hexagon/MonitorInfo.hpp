#pragma once


#include <Hexagon/Monitor.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   class MonitorInfo
   {
   private:
      std::vector<Hexagon::Monitor> monitors;
      bool initialized;

   protected:


   public:
      MonitorInfo();
      ~MonitorInfo();

      int get_num_monitors();
      Hexagon::Monitor get_primary_monitor_info();
      std::string dump_monitor_info();
      void initialize();
   };
}



