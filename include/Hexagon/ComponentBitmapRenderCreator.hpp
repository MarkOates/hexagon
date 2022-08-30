#pragma once


#include <ALLEGRO_BITMAP.hpp>
#include <Blast/Project/Component.hpp>
#include <string>


namespace Hexagon
{
   class ComponentBitmapRenderCreator
   {
   private:
      Blast::Project::Component* component;

   public:
      ComponentBitmapRenderCreator(Blast::Project::Component* component=nullptr);
      ~ComponentBitmapRenderCreator();

      ALLEGRO_BITMAP* create_bitmap_render();
      std::string render();
   };
}



