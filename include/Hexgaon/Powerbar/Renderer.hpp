#pragma once




namespace Hexgaon
{
   namespace Powerbar
   {
      class Renderer
      {
      private:
         float width;

      public:
         Renderer(float width=1000.0f);
         ~Renderer();


      void render();
      };
   }
}



