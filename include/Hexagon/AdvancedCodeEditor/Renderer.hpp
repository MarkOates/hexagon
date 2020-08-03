#pragma once


#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/Elements/FontedTextGrid.hpp>
#include <Hexagon/Elements/TextMesh.hpp>
#include <allegro5/allegro.h>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Renderer
      {
      private:
         Hexagon::Elements::TextMesh* text_mesh;
         ALLEGRO_BITMAP* surface_render;
         Hexagon::Elements::FontedTextGrid* fonted_text_grid;
         Hexagon::AdvancedCodeEditor::Cursor* cursor;
         float width;
         float height;
         bool cursor_is_bar;

      public:
         Renderer(Hexagon::Elements::TextMesh* text_mesh=nullptr, ALLEGRO_BITMAP* surface_render=nullptr, Hexagon::Elements::FontedTextGrid* fonted_text_grid={}, Hexagon::AdvancedCodeEditor::Cursor* cursor=nullptr, float width=1, float height=1, bool cursor_is_bar=false);
         ~Renderer();


      void render();
      void render_cursor();
      };
   }
}



