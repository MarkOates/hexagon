#pragma once


#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <allegro5/allegro_color.h>


namespace Hexagon
{
   namespace CodeEditor
   {
      class CursorRenderer
      {
      private:
         ALLEGRO_COLOR color;
         float x;
         float y;
         float width;
         float height;
         ::CodeEditor::CodeEditor::mode_t mode;
         bool focus;

      public:
         CursorRenderer(ALLEGRO_COLOR color=al_color_name("white"), float x=0, float y=0, float width=1, float height=1, ::CodeEditor::CodeEditor::mode_t mode=::CodeEditor::CodeEditor::EDIT, bool focus=true);
         ~CursorRenderer();


         ALLEGRO_COLOR get_color();
      void render();
      };
   }
}



