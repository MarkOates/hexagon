#pragma once


#include <Hexagon/StageInterface.hpp>
#include <Hexagon/System/Config.hpp>
#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>
#include <string>


namespace Hexagon
{
   class StageFactory
   {
   private:
      Hexagon::System::Config* config;

   public:
      StageFactory(Hexagon::System::Config* config=nullptr);
      ~StageFactory();


   std::string obtain_default_navigator_directory();
   ALLEGRO_COLOR obtain_base_text_color();
   ALLEGRO_COLOR obtain_base_backfill_color();
   StageInterface* create();
   StageInterface* create_advanced_component_navigator();
   ALLEGRO_DISPLAY* get_current_display();
   placement3d build_component_navigator_initial_place();
   };
}



