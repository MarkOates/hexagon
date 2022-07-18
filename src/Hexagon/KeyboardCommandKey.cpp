

#include <Hexagon/KeyboardCommandKey.hpp>



namespace Hexagon
{


KeyboardCommandKey::KeyboardCommandKey(int al_keycode, bool shift, bool ctrl, bool alt, bool command)
   : al_keycode(al_keycode)
   , shift(shift)
   , ctrl(ctrl)
   , alt(alt)
   , command(command)
{
}


KeyboardCommandKey::~KeyboardCommandKey()
{
}


void KeyboardCommandKey::set_al_keycode(int al_keycode)
{
   this->al_keycode = al_keycode;
}


void KeyboardCommandKey::set_shift(bool shift)
{
   this->shift = shift;
}


void KeyboardCommandKey::set_ctrl(bool ctrl)
{
   this->ctrl = ctrl;
}


void KeyboardCommandKey::set_alt(bool alt)
{
   this->alt = alt;
}


void KeyboardCommandKey::set_command(bool command)
{
   this->command = command;
}


int KeyboardCommandKey::get_al_keycode()
{
   return al_keycode;
}


bool KeyboardCommandKey::get_shift()
{
   return shift;
}


bool KeyboardCommandKey::get_ctrl()
{
   return ctrl;
}


bool KeyboardCommandKey::get_alt()
{
   return alt;
}


bool KeyboardCommandKey::get_command()
{
   return command;
}


} // namespace Hexagon


