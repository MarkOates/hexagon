

#include <Hexagon/MarkerNavigator.hpp>




namespace Hexagon
{


MarkerNavigator::MarkerNavigator()
   : markers_index({})
{
}


MarkerNavigator::~MarkerNavigator()
{
}


std::map<std::string, Hexagon::Marker> MarkerNavigator::get_markers_index() const
{
   return markers_index;
}


void MarkerNavigator::load()
{
   // TODO
   return;
}

void MarkerNavigator::clear()
{
   markers_index.clear();
   return;
}

void MarkerNavigator::add_or_override(std::string label, Hexagon::Marker marker)
{
   markers_index[label] = marker;
   return;
}

bool MarkerNavigator::marker_exists(std::string label)
{
   // TODO
   return false;
}


} // namespace Hexagon


