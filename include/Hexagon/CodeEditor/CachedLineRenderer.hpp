#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <vector>


namespace Hexagon
{
   namespace CodeEditor
   {
      class CachedLineRenderer
      {
      private:
         ALLEGRO_FONT* font;
         int bitmap_width;
         int num_caches_to_build;
         bool initialized;
         std::vector<ALLEGRO_BITMAP*> cache;
         ALLEGRO_BITMAP* source;

      public:
         CachedLineRenderer(ALLEGRO_FONT* font=nullptr);
         ~CachedLineRenderer();

         void initialize();
         void destruct();
         int size();
         bool exists(int index=0);
         ALLEGRO_BITMAP* pull(int index=0);
      };
   }
}



