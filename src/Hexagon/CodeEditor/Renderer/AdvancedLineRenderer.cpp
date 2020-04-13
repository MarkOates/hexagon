

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <AllegroFlare/Color.hpp>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <utility>
#include <allegro5/allegro.h>
#include <vector>
#include <utility>
#include <string>
#include <allegro5/allegro_color.h>


namespace Hexagon
{
namespace CodeEditor
{
namespace Renderer
{


AdvancedLineRenderer::AdvancedLineRenderer(ALLEGRO_FONT* font, ALLEGRO_COLOR* font_color, float x, float y, std::string line)
   : font(font)
   , font_color(font_color)
   , x(x)
   , y(y)
   , line(line)
{
}


AdvancedLineRenderer::~AdvancedLineRenderer()
{
}


std::vector<std::pair<std::string, ALLEGRO_COLOR>> AdvancedLineRenderer::build_tokens()
{
std::vector<std::pair<std::string, ALLEGRO_COLOR>> tokens;
ALLEGRO_COLOR comment_color = AllegroFlare::color::color(*font_color, 0.3f);

//std::size_t comment_starts_at = line.find("//");
std::string comments_not_inside_quotes_regex = "([\"'])(?:\\?+.)*?\1";
RegexMatcher regex_matcher(line, comments_not_inside_quotes_regex);
std::vector<std::pair<int, int>> match_info = regex_matcher.get_match_info();

tokens = { { line, *font_color } };
return tokens;

}

void AdvancedLineRenderer::render_tokens(std::vector<std::pair<std::string, ALLEGRO_COLOR>> tokens)
{
for (auto &token : tokens)
{
   std::string &text = std::get<0>(token);
   ALLEGRO_COLOR &color = std::get<1>(token);

   al_draw_text(font, *font_color, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
}

}

void AdvancedLineRenderer::render()
{
if (!font)
{
   std::stringstream error_message;
   error_message << "[Hexagon/Powerbar/Renderer/AdvancedLineRenderer error:] cannot \""
                 << __FUNCTION__ << "\" with a nullptr font";
   throw std::runtime_error(error_message.str());
}
if (!font_color)
{
   std::stringstream error_message;
   error_message << "[Hexagon/Powerbar/Renderer/AdvancedLineRenderer error:] cannot \""
                 << __FUNCTION__ << "\" with a nullptr font_color";
   throw std::runtime_error(error_message.str());
}

std::vector<std::pair<std::string, ALLEGRO_COLOR>> tokens = build_tokens();
render_tokens(tokens);

return;

}
} // namespace Renderer
} // namespace CodeEditor
} // namespace Hexagon


