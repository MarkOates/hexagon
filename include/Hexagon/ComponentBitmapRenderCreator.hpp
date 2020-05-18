#pragma once


#include <Blast/Project/Component.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   class ComponentBitmapRenderCreator
   {
   private:
      Blast::Project::Component* component;

   public:
      ComponentBitmapRenderCreator();
      ~ComponentBitmapRenderCreator();


   ALLEGRO_BITMAP* create_bitmap_render();
   std::string render();
   };
}



