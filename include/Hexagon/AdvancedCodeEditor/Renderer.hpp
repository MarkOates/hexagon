#pragma once


#include <Hexagon/AdvancedCodeEditor/Stage.hpp>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Renderer
      {
      private:
         Hexagon::AdvancedCodeEditor::Stage* stage;

      public:
         Renderer(Hexagon::AdvancedCodeEditor::Stage* stage=nullptr);
         ~Renderer();


      void render();
      };
   }
}



