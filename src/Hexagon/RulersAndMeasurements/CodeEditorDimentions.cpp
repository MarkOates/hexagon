

#include <Hexagon/RulersAndMeasurements/CodeEditorDimentions.hpp>



namespace Hexagon
{
namespace RulersAndMeasurements
{


CodeEditorDimentions::CodeEditorDimentions()
{
}


CodeEditorDimentions::~CodeEditorDimentions()
{
}


float CodeEditorDimentions::calculate_max_half_surface_width(float surface_width, float cell_width, int num_columns)
{
   // TODO: function is probably not needed or used anywhers
   return (surface_width * 0.5f) / (cell_width * num_columns);
}
} // namespace RulersAndMeasurements
} // namespace Hexagon


