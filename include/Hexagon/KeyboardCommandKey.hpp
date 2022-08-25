#pragma once




namespace Hexagon
{
   class KeyboardCommandKey
   {
   private:
      int al_keycode;
      bool shift;
      bool ctrl;
      bool alt;
      bool command;

   public:
      KeyboardCommandKey(int al_keycode=0, bool shift=false, bool ctrl=false, bool alt=false, bool command=false);
      ~KeyboardCommandKey();

      void set_al_keycode(int al_keycode);
      void set_shift(bool shift);
      void set_ctrl(bool ctrl);
      void set_alt(bool alt);
      void set_command(bool command);
      int get_al_keycode() const;
      bool get_shift() const;
      bool get_ctrl() const;
      bool get_alt() const;
      bool get_command() const;
   };
}



