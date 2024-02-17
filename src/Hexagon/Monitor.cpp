

#include <Hexagon/Monitor.hpp>




namespace Hexagon
{


Monitor::Monitor(int desktop_x1, int desktop_y1, int desktop_x2, int desktop_y2, int dpi)
   : desktop_x1(desktop_x1)
   , desktop_y1(desktop_y1)
   , desktop_x2(desktop_x2)
   , desktop_y2(desktop_y2)
   , dpi(dpi)
{
}


Monitor::~Monitor()
{
}


void Monitor::set_desktop_x1(int desktop_x1)
{
   this->desktop_x1 = desktop_x1;
}


void Monitor::set_desktop_y1(int desktop_y1)
{
   this->desktop_y1 = desktop_y1;
}


void Monitor::set_desktop_x2(int desktop_x2)
{
   this->desktop_x2 = desktop_x2;
}


void Monitor::set_desktop_y2(int desktop_y2)
{
   this->desktop_y2 = desktop_y2;
}


void Monitor::set_dpi(int dpi)
{
   this->dpi = dpi;
}


int Monitor::get_desktop_x1() const
{
   return desktop_x1;
}


int Monitor::get_desktop_y1() const
{
   return desktop_y1;
}


int Monitor::get_desktop_x2() const
{
   return desktop_x2;
}


int Monitor::get_desktop_y2() const
{
   return desktop_y2;
}


int Monitor::get_dpi() const
{
   return dpi;
}


int Monitor::get_resolution_x()
{
   return desktop_x2 - desktop_x1;
}

int Monitor::get_resolution_y()
{
   return desktop_y2 - desktop_y1;
}


} // namespace Hexagon


