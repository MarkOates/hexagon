

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>
#include <allegro5/allegro.h>
#include <utility>
#include <Hexagon/RegexMatcher.hpp>
#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>
#include <sstream>
#include <allegro5/allegro_color.h>
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
ALLEGRO_COLOR comment_color = AllegroFlare::color::color(
   AllegroFlare::color::mix(*font_color, al_color_name("dodgerblue"), 0.35f),
   0.35f);


std::string regex = "";
{
   //std::string comments_not_inside_quotes_regex = "([\"'])(?:\\?+.)*?\1";
   std::string basic_comment_regex = "//.*";
   //std::string attempt = "";

   regex = basic_comment_regex;
}

RegexMatcher regex_matcher(line, regex);

std::vector<std::pair<int, int>> match_info = regex_matcher.get_match_info();

if (match_info.empty())
{
   tokens = { { line, *font_color } };
}
else if (match_info.size() == 1)
{
   //throw std::runtime_error("single match");
   int string_end = match_info[0].first;
   std::string uncommented_substr = line.substr(0, string_end);
   std::string commented_substr = line.substr(string_end);
   tokens = {
      { uncommented_substr, *font_color },
      { commented_substr, comment_color },
   };
}
else if (match_info.size() > 1)
{
   throw std::runtime_error("multi match");
   //ALLEGRO_COLOR error_color = al_color_name("saddlebrown");
   ALLEGRO_COLOR error_color = al_color_name("red");
   tokens = { { line, error_color } };
}

//tokens = { { line, *font_color } };
return tokens;

}

void AdvancedLineRenderer::render_tokens(std::vector<std::pair<std::string, ALLEGRO_COLOR>> tokens, float cell_width)
{
float x_pos = 0;
for (auto &token : tokens)
{
   std::string &text = std::get<0>(token);
   ALLEGRO_COLOR color = std::get<1>(token);

   al_draw_text(font, color, x + x_pos, y, ALLEGRO_ALIGN_LEFT, text.c_str());

   x_pos += (text.length() * cell_width);
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
std::vector<std::pair<std::string, ALLEGRO_COLOR>> tokens = build_tokens();
render_tokens(tokens, cell_width);

return;

}
} // namespace Renderer
} // namespace CodeEditor
} // namespace Hexagon


