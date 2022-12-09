

#include <Hexagon/CodeEditor/CachedLineRenderer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>


namespace Hexagon
{
namespace CodeEditor
{


CachedLineRenderer::CachedLineRenderer(ALLEGRO_FONT* font)
   : font(font)
   , bitmap_width(800)
   , num_caches_to_build(200)
   , initialized(false)
   , cache({})
   , source(nullptr)
{
}


CachedLineRenderer::~CachedLineRenderer()
{
}


void CachedLineRenderer::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[CachedLineRenderer::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CachedLineRenderer::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[CachedLineRenderer::initialize]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CachedLineRenderer::initialize: error: guard \"font\" not met");
   }
   if (initialized) return;

   // destroy any existing resources
   for (auto &strip : cache) if (strip) al_destroy_bitmap(strip);
   cache.clear();
   if (source) al_destroy_bitmap(source);

   // build new source
   int line_height = al_get_font_line_height(font);
   int bitmap_height = line_height * num_caches_to_build;
   source = al_create_bitmap(bitmap_width, bitmap_height);

   // build cache strips
   int num_lines_in_cache = bitmap_height / line_height;

   cache.resize(num_lines_in_cache, nullptr);

   for (unsigned i=0; i<num_lines_in_cache; i++)
   {
      cache[i] = al_create_sub_bitmap(source, 0, line_height*i, bitmap_width, line_height*(i+1));
   }

   initialized = true;
}

void CachedLineRenderer::destruct()
{
   for (auto &strip : cache) if (strip) al_destroy_bitmap(strip);
   cache.clear();
   if (source) al_destroy_bitmap(source);
}

int CachedLineRenderer::size()
{
   return cache.size();
}

bool CachedLineRenderer::exists(int index)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CachedLineRenderer::exists]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CachedLineRenderer::exists: error: guard \"initialized\" not met");
   }
   if (index < 0) return false;
   if (index >= cache.size()) return false;
   return true;
}

ALLEGRO_BITMAP* CachedLineRenderer::pull(int index)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[CachedLineRenderer::pull]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CachedLineRenderer::pull: error: guard \"initialized\" not met");
   }
   if (!(index >= 0))
   {
      std::stringstream error_message;
      error_message << "[CachedLineRenderer::pull]: error: guard \"index >= 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CachedLineRenderer::pull: error: guard \"index >= 0\" not met");
   }
   if (!(index < cache.size()))
   {
      std::stringstream error_message;
      error_message << "[CachedLineRenderer::pull]: error: guard \"index < cache.size()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CachedLineRenderer::pull: error: guard \"index < cache.size()\" not met");
   }
   return cache[index];
}


} // namespace CodeEditor
} // namespace Hexagon


