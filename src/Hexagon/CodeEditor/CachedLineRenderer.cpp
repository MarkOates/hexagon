

#include <Hexagon/CodeEditor/CachedLineRenderer.hpp>
#include <allegro5/allegro.h>
#include <map>
#include <vector>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
namespace CodeEditor
{


CachedLineRenderer::CachedLineRenderer(ALLEGRO_FONT* font)
   : bitmap_width(800)
   , bitmap_height(1600)
   , initialized(false)
   , cache({})
   , source(nullptr)
   , font(font)
{
}


CachedLineRenderer::~CachedLineRenderer()
{
}


void CachedLineRenderer::initialize()
{
// destroy any existing resources
for (auto &strip : cache) if (strip) al_destroy_bitmap(strip);
cache.clear();
if (source) al_destroy_bitmap(source);

// build new source
source = al_create_bitmap(bitmap_width, bitmap_height);

// build cache strips
int line_height = al_get_font_line_height(font);
int num_lines_in_cache = bitmap_height / line_height;

cache.resize(num_lines_in_cache, nullptr);

for (unsigned i=0; i<num_lines_in_cache; i++)
{
   cache[i] = al_create_sub_bitmap(source, 0, line_height*i, bitmap_width, line_height*(i+1));
}

initialized = true;

}

ALLEGRO_BITMAP* CachedLineRenderer::pull(int index)
{
if (index < 0) throw std::runtime_error("\"CachedLineRenderer::pull\" out of range");
if (index >= cache.size()) throw std::runtime_error("\"CachedLineRenderer::pull\" out of range");
return cache[index];

}
} // namespace CodeEditor
} // namespace Hexagon


