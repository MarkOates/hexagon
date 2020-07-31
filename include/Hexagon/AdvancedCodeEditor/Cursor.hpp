#pragma once




namespace Hexagon
{
   namespace AdvancedCodeEditor
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

         void set_x(float x);
         void set_y(float y);
         void set_width(float width);
         void set_height(float height);

         float get_x();
         float get_y();
         float get_width();
         float get_height();
      void move_up();
      void move_down();
      void move_left();
      void move_right();
      void move_to(int x=0, int y=0);
      };
   }
}



