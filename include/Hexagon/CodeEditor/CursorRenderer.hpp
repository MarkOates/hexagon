#pragma once




namespace Hexagon
{
   namespace CodeEditor
   {
      class CursorRenderer
      {
      private:
         float x;
         float y;
         float width;
         float height;

      public:
         CursorRenderer(float x=0, float y=0, float width=1, float height=1);
         ~CursorRenderer();


      void render();
      };
   }
}



