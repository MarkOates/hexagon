#pragma once


#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      class Cursor
      {
      private:
         float x;
         float y;
         float width;
         float height;

      public:
         Cursor(float x=0, float y=0, float width=1, float height=1);
         ~Cursor();

         std::string run();
      };
   }
}



