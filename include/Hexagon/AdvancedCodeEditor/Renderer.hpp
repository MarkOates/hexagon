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

      public:
         Renderer(Hexagon::Elements::TextMesh* text_mesh=nullptr, Hexagon::AdvancedCodeEditor::Cursor* cursor=nullptr);
         ~Renderer();


      void render();
      };
   }
}



