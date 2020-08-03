

#include <Hexagon/Elements/QuoteRenderer.hpp>



namespace Hexagon
{
namespace Elements
{


QuoteRenderer::QuoteRenderer(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
{
}


QuoteRenderer::~QuoteRenderer()
{
}


void QuoteRenderer::render()
{
return;

}

ALLEGRO_FONT* QuoteRenderer::obtain_quote_font()
{
return nullptr;

}
} // namespace Elements
} // namespace Hexagon


