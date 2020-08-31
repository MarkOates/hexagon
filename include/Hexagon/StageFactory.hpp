#pragma once


#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>


namespace Hexagon
{
   class StageFactory
   {
   private:

   public:
      StageFactory();
      ~StageFactory();


   ALLEGRO_DISPLAY* get_current_display();
   placement3d build_component_navigator_initial_place();
   StageInterface* create();
   };
}



