#pragma once


#include <Hexagon/CodeEditor/Stage.hpp>


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
         ::CodeEditor::Stage::mode_t mode;
         bool focus;

      public:
         CursorRenderer(float x=0, float y=0, float width=1, float height=1, ::CodeEditor::Stage::mode_t mode=::CodeEditor::Stage::EDIT, bool focus=true);
         ~CursorRenderer();


      void render();
      };
   }
}



