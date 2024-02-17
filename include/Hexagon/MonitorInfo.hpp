#pragma once


#include <Hexagon/Monitor.hpp>
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
      void initialize();
   };
}



