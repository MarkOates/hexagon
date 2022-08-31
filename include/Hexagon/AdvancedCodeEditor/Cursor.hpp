#pragma once




namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Cursor
      {
      private:
         int x;
         int y;
         float width;
         float height;

      protected:


      public:
         Cursor(int x=0, int y=0, float width=1, float height=1);
         ~Cursor();

         void set_x(int x);
         void set_y(int y);
         void set_width(float width);
         void set_height(float height);
         int get_x() const;
         int get_y() const;
         float get_width() const;
         float get_height() const;
         void move_up();
         void move_down();
         void move_left();
         void move_right();
         void move_to(int x=0, int y=0);
      };
   }
}



