#pragma once


#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/AdvancedCodeEditor/Selection.hpp>
#include <Hexagon/Elements/TextMesh.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


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
         std::vector<Hexagon::AdvancedCodeEditor::Selection>* selections;
         std::vector<std::string>* lines;
         float width;
         float height;
         bool cursor_is_bar;
         float text_mesh_y_offset;
         int first_row_offset;
         bool draw_line_numbers;
         ALLEGRO_FONT* font;

      public:
         Renderer(Hexagon::Elements::TextMesh* text_mesh=nullptr, ALLEGRO_BITMAP* surface_render=nullptr, Hexagon::AdvancedCodeEditor::Cursor* cursor=nullptr, std::vector<Hexagon::AdvancedCodeEditor::Selection>* selections={}, std::vector<std::string>* lines=nullptr, float width=1, float height=1, bool cursor_is_bar=false, float text_mesh_y_offset=0.0f, int first_row_offset=0, bool draw_line_numbers=false, ALLEGRO_FONT* font=nullptr);
         ~Renderer();

         void set_draw_line_numbers(bool draw_line_numbers);
         void set_font(ALLEGRO_FONT* font);

      void render();
      bool render_line_numbers();
      void render_cursor();
      void draw_selections();
      };
   }
}



