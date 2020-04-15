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
         int bitmap_width;
         int bitmap_height;
         bool initialized;
         std::vector<ALLEGRO_BITMAP*> cache;
         ALLEGRO_BITMAP* source;
         ALLEGRO_FONT* font;

      public:
         CachedLineRenderer(ALLEGRO_FONT* font=nullptr);
         ~CachedLineRenderer();


      void initialize();
      int size();
      bool exists(int index=0);
      ALLEGRO_BITMAP* pull(int index=0);
      };
   }
}



