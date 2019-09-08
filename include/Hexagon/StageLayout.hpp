#pragma once


#include <allegro_flare/placement3d.h>
#include <map>
#include <string>


namespace Hexagon
{
   class StageLayout
   {
   private:
      std::map<std::string, placement3d> placements;

   public:
      StageLayout(std::map<std::string, placement3d> placements={});
      ~StageLayout();

      void set_placements(std::map<std::string, placement3d> placements);

      std::map<std::string, placement3d> get_placements();
      std::map<std::string, placement3d> &get_placements_ref();
   placement3d placement_for(std::string label="");
   };
}



