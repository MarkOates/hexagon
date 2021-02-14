#pragma once




namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class WindowRenderer
      {
      private:
         float width;
         float height;

      public:
         WindowRenderer(float width=1, float height=1);
         ~WindowRenderer();

         void render();
      };
   }
}



