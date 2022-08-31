#pragma once


#include <Hexagon/Marker.hpp>
#include <map>
#include <string>


namespace Hexagon
{
   class MarkerNavigator
   {
   private:
      std::map<std::string, Hexagon::Marker> markers_index;

   protected:


   public:
      MarkerNavigator();
      ~MarkerNavigator();

      std::map<std::string, Hexagon::Marker> get_markers_index() const;
      void load();
      void clear();
      void add_or_override(std::string label="[no-label-set]", Hexagon::Marker marker={});
      bool marker_exists(std::string label="[no-label-set]");
   };
}



