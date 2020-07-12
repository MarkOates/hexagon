#pragma once


#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/Elements/TextMesh.hpp>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Renderer
      {
      private:
         Hexagon::Elements::TextMesh* text_mesh;
         Hexagon::AdvancedCodeEditor::Cursor* cursor;
         float width;
         float height;

      public:
         Renderer(Hexagon::Elements::TextMesh* text_mesh=nullptr, Hexagon::AdvancedCodeEditor::Cursor* cursor=nullptr, float width=1, float height=2);
         ~Renderer();


      void render();
      };
   }
}



