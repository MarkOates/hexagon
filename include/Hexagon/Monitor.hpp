#pragma once




namespace Hexagon
{
   class Monitor
   {
   private:
      int desktop_x1;
      int desktop_y1;
      int desktop_x2;
      int desktop_y2;
      int dpi;

   protected:


   public:
      Monitor(int desktop_x1=0, int desktop_y1=0, int desktop_x2=0, int desktop_y2=0, int dpi=0);
      ~Monitor();

      void set_desktop_x1(int desktop_x1);
      void set_desktop_y1(int desktop_y1);
      void set_desktop_x2(int desktop_x2);
      void set_desktop_y2(int desktop_y2);
      void set_dpi(int dpi);
      int get_desktop_x1() const;
      int get_desktop_y1() const;
      int get_desktop_x2() const;
      int get_desktop_y2() const;
      int get_dpi() const;
      int get_resolution_x();
      int get_resolution_y();
   };
}



