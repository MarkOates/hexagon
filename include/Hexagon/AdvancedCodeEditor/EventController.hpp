#pragma once


#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <string>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class EventController
      {
      private:
         Hexagon::AdvancedCodeEditor::Stage* stage;

      public:
         EventController();
         ~EventController();


      std::string run();
      };
   }
}



