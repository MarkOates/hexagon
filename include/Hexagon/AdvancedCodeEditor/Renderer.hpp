#pragma once


#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
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
         Hexagon::AdvancedCodeEditor::Cursor* cursor;
         float width;
         float height;
         bool cursor_is_bar;
         float text_mesh_y_offset;

      public:
         Renderer(Hexagon::Elements::TextMesh* text_mesh=nullptr, ALLEGRO_BITMAP* surface_render=nullptr, Hexagon::AdvancedCodeEditor::Cursor* cursor=nullptr, float width=1, float height=1, bool cursor_is_bar=false, float text_mesh_y_offset=0.0f);
         ~Renderer();


      void render();
      void render_cursor();
      };
   }
}



