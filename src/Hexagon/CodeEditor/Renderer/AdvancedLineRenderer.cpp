

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <allegro5/allegro.h>
#include <utility>
#include <Hexagon/RegexMatcher.hpp>
#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>
#include <sstream>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <vector>
#include <tuple>
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


std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> AdvancedLineRenderer::build_comment_tokens()
{
std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens;
ALLEGRO_COLOR comment_color = AllegroFlare::color::color(
   AllegroFlare::color::mix(*font_color, al_color_name("dodgerblue"), 0.35f),
   0.35f);

std::string regex = "";
{
   //std::string comments_not_inside_quotes_regex = "([\"'])(?:\\?+.)*?\1";
   std::string basic_comment_regex = "//.*";
   std::string quoted_string_regex = "\"([^\"]*)\"";
   //std::string attempt = "";

   regex = basic_comment_regex;
}

RegexMatcher regex_matcher(line, regex);

std::vector<std::pair<int, int>> match_infos = regex_matcher.get_match_info();

if (match_infos.empty())
{
   tokens = { { line, 0, *font_color } };
}
else if (match_infos.size() == 1)
{
   int string_end = match_infos[0].first;
   std::string uncommented_substr = line.substr(0, string_end);
   std::string commented_substr = line.substr(string_end);
   tokens = {
      { uncommented_substr, 0, *font_color },
      { commented_substr, string_end, comment_color },
   };
}
else if (match_infos.size() > 1)
{
   throw std::runtime_error("unexpected multi match error");
   ALLEGRO_COLOR error_color = al_color_name("red");
   tokens = { { line, 0, error_color } };
}

return tokens;

}

void AdvancedLineRenderer::render_tokens(std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens, float cell_width)
{
for (auto &token : tokens)
{
   std::string &text = std::get<0>(token);
   int x_position = std::get<1>(token);
   ALLEGRO_COLOR color = std::get<2>(token);

   al_draw_text(font, color, x + (x_position * cell_width), y, ALLEGRO_ALIGN_LEFT, text.c_str());
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

float cell_width = al_get_text_width(font, " ");
std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens = build_comment_tokens();
render_tokens(tokens, cell_width);

return;

}
} // namespace Renderer
} // namespace CodeEditor
} // namespace Hexagon


