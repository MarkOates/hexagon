#pragma once


#include <Hexagon/Elements/TextMesh.hpp>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Renderer
      {
      private:
         Hexagon::Elements::TextMesh* text_mesh;

      public:
         Renderer(Hexagon::Elements::TextMesh* text_mesh=nullptr);
         ~Renderer();


      void render();
      };
   }
}



