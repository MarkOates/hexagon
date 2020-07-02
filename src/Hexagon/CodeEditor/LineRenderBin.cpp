

#include <Hexagon/CodeEditor/LineRenderBin.hpp>



namespace Hexagon
{
namespace CodeEditor
{


LineRenderBin::LineRenderBin()
   : AllegroFlare::Bin<std::string, ALLEGRO_BITMAP *>()
{
}


LineRenderBin::~LineRenderBin()
{
}


ALLEGRO_BITMAP* LineRenderBin::load_data(std::string identifier)
{
return nullptr;

}

void LineRenderBin::destroy_data(ALLEGRO_BITMAP* resource)
{
return;

}
} // namespace CodeEditor
} // namespace Hexagon


