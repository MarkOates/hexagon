

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/RegexStore.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/RegexStore.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/shared_globals.hpp>
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


AdvancedLineRenderer::AdvancedLineRenderer(ALLEGRO_FONT* font, ALLEGRO_COLOR* font_color, ALLEGRO_COLOR* backfill_color, float x, float y, std::string line)
   : font(font)
   , font_color(font_color)
   , backfill_color(backfill_color)
   , x(x)
   , y(y)
   , line(line)
{
}


AdvancedLineRenderer::~AdvancedLineRenderer()
{
}


std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> AdvancedLineRenderer::build_quintessence_yaml_name_element_tokens()
{
std::string regex = "^  [\- ] name: .*$";
RegexMatcher regex_matcher(line, regex);
if (regex_matcher.get_match_info().empty()) return {};
ALLEGRO_COLOR yaml_name_element_key_color = AllegroFlare::color::color(al_color_name("dodgerblue"), 0.2);
ALLEGRO_COLOR yaml_name_element_value_color = AllegroFlare::color::color(al_color_name("dodgerblue"), 0.3);
return std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>>{
   { line, 0, yaml_name_element_key_color },
   { line.substr(10), 10, yaml_name_element_value_color },
};

}

std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> AdvancedLineRenderer::build_quoted_string_tokens()
{
std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens;

std::string regex = "";
{
   // this regex provided by https://stackoverflow.com/a/249937/6072362
   std::string quoted_string_regex = Hexagon::RegexStore::double_quoted_strings_with_escapes();
   regex = quoted_string_regex;
}

RegexMatcher regex_matcher(line, regex);

std::vector<std::pair<int, int>> match_infos = regex_matcher.get_match_info();

for (auto &match_info : match_infos)
{
   ALLEGRO_COLOR quote_color = AllegroFlare::color::color(al_color_name("coral"), 0.225);
   std::string str = line.substr(match_info.first, match_info.second);
   tokens.push_back({ str, match_info.first, quote_color });
}

return tokens;

}

std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> AdvancedLineRenderer::build_comment_tokens()
{
std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens;
ALLEGRO_COLOR base_backfill_color = hexagon_get_backfill_color();
ALLEGRO_COLOR comment_color = AllegroFlare::color::color(base_backfill_color, 0.75f);
   //AllegroFlare::color::color(al_color_name("black"), 0.3f)

std::string regex = "";
{
   //std::string comments_not_inside_quotes_regex = "([\"'])(?:\\?+.)*?\1";
   //std::string basic_comment_regex = "//.*";
   std::string basic_comment_regex = "//.*";
   regex = basic_comment_regex;
}

RegexMatcher regex_matcher(line, regex);

std::vector<std::pair<int, int>> match_infos = regex_matcher.get_match_info();

if (match_infos.empty())
{
   //tokens = { { line, 0, *font_color } };
}
else if (match_infos.size() == 1)
{
   int string_end = match_infos[0].first;
   std::string uncommented_substr = line.substr(0, string_end);
   std::string commented_substr = line.substr(string_end);
   tokens = {
      //{ uncommented_substr, 0, *font_color },
      { commented_substr, string_end, comment_color },
   };
}
else if (match_infos.size() > 1)
{
   throw std::runtime_error("unexpected multi match error");
   //ALLEGRO_COLOR error_color = al_color_name("red");
   //tokens = { { line, 0, error_color } };
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

// draw the line straight out
al_draw_text(font, *font_color, x, y, ALLEGRO_ALIGN_LEFT, line.c_str());

float cell_width = al_get_text_width(font, " ");

std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens;

tokens = build_comment_tokens();
render_tokens(tokens, cell_width);

tokens = build_quoted_string_tokens();
render_tokens(tokens, cell_width);

tokens = build_quintessence_yaml_name_element_tokens();
render_tokens(tokens, cell_width);

return;

}
} // namespace Renderer
} // namespace CodeEditor
} // namespace Hexagon


