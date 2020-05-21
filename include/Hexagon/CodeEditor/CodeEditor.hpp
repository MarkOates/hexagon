#pragma once


#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      class CodeEditor
      {
      private:
         int cursor_x;
         int cursor_y;

      public:
         CodeEditor();
         ~CodeEditor();

         void set_cursor_x(int cursor_x);
         void set_cursor_y(int cursor_y);

         int get_cursor_x();
         int get_cursor_y();
      std::string run();
      };
   }
}



