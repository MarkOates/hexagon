

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/RegexStore.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/RegexStore.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/RegexStore.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <stdexcept>
#include <sstream>
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
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace CodeEditor
{
namespace Renderer
{


AdvancedLineRenderer::AdvancedLineRenderer(ALLEGRO_FONT* font, ALLEGRO_COLOR* font_color, ALLEGRO_COLOR* backfill_color, float x, float y, std::string full_line_text, int max_num_columns)
   : font(font)
   , font_color(font_color)
   , backfill_color(backfill_color)
   , x(x)
   , y(y)
   , full_line_text(full_line_text)
   , max_num_columns(max_num_columns)
{
}


AdvancedLineRenderer::~AdvancedLineRenderer()
{
}


std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> AdvancedLineRenderer::build_test_declaration_element_tokens()
{
   std::string primary_line_regex = "^   [a-z0-9_]+\\)$";
   RegexMatcher primary_regex_matcher(full_line_text, primary_line_regex);

   std::string secondary_line_regex = "^TEST(_F)?\\([a-zA-Z_]+, ?[a-z_]*\\)?";
   RegexMatcher secondary_regex_matcher(full_line_text, secondary_line_regex);

   if (
         primary_regex_matcher.get_match_info().empty()
      && secondary_regex_matcher.get_match_info().empty()
   ) return {};

   std::string function_name_regex = " [a-z0-9_]+?__";
   RegexMatcher function_name_regex_matcher(full_line_text, function_name_regex);

   ALLEGRO_COLOR test_declaration_color = AllegroFlare::color::color(al_color_name("dodgerblue"), 0.2);
   ALLEGRO_COLOR function_name_color = AllegroFlare::color::color(al_color_name("dodgerblue"), 0.3);

   std::vector<std::pair<int, int>> function_name_regex_matcher_match_info =
      function_name_regex_matcher.get_match_info();
   if (!function_name_regex_matcher_match_info.empty())
   {
      int function_starts_at = function_name_regex_matcher_match_info[0].first;
      int function_length = function_name_regex_matcher_match_info[0].second - 2;
      std::string function_name = full_line_text.substr(function_starts_at, function_length);
      return std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>>{
         { full_line_text, 0, test_declaration_color },
         { function_name, function_starts_at, function_name_color },
      };
   }
   else {
      return std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>>{
         { full_line_text, 0, test_declaration_color },
      };
   }
}

std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> AdvancedLineRenderer::build_quintessence_yaml_name_element_tokens()
{
   std::string regex = "^  [\- ] name: .*$";
   RegexMatcher regex_matcher(full_line_text, regex);
   if (regex_matcher.get_match_info().empty()) return {};
   ALLEGRO_COLOR yaml_name_element_key_color = AllegroFlare::color::color(al_color_name("dodgerblue"), 0.2);
   ALLEGRO_COLOR yaml_name_element_value_color = AllegroFlare::color::color(al_color_name("dodgerblue"), 0.3);
   return std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>>{
      { full_line_text, 0, yaml_name_element_key_color },
      { full_line_text.substr(10), 10, yaml_name_element_value_color },
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

   RegexMatcher regex_matcher(full_line_text, regex);

   std::vector<std::pair<int, int>> match_infos = regex_matcher.get_match_info();

   for (auto &match_info : match_infos)
   {
      ALLEGRO_COLOR quote_color = AllegroFlare::color::color(al_color_name("coral"), 0.225);
      std::string str = full_line_text.substr(match_info.first, match_info.second);
      tokens.push_back({ str, match_info.first, quote_color });
   }

   return tokens;
}

std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> AdvancedLineRenderer::build_comment_tokens()
{
   if (!(backfill_color))
      {
         std::stringstream error_message;
         error_message << "AdvancedLineRenderer" << "::" << "build_comment_tokens" << ": error: " << "guard \"backfill_color\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens;
   ALLEGRO_COLOR base_backfill_color = *backfill_color;
   ALLEGRO_COLOR comment_color = AllegroFlare::color::color(base_backfill_color, 0.75f);
      //AllegroFlare::color::color(al_color_name("black"), 0.3f)

   std::string regex = "";
   {
      //std::string comments_not_inside_quotes_regex = "([\"'])(?:\\?+.)*?\1";
      //std::string basic_comment_regex = "//.*";
      std::string basic_comment_regex = "//.*";
      regex = basic_comment_regex;
   }

   RegexMatcher regex_matcher(full_line_text, regex);

   std::vector<std::pair<int, int>> match_infos = regex_matcher.get_match_info();

   if (match_infos.empty())
   {
      //tokens = { { full_line_text, 0, *font_color } };
   }
   else if (match_infos.size() == 1)
   {
      int string_end = match_infos[0].first;
      std::string uncommented_substr = full_line_text.substr(0, string_end);
      std::string commented_substr = full_line_text.substr(string_end);
      tokens = {
         //{ uncommented_substr, 0, *font_color },
         { commented_substr, string_end, comment_color },
      };
   }
   else if (match_infos.size() > 1)
   {
      throw std::runtime_error("unexpected multi match error");
      //ALLEGRO_COLOR error_color = al_color_name("red");
      //tokens = { { full_line_text, 0, error_color } };
   }

   return tokens;
}

void AdvancedLineRenderer::render_tokens(std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens, float cell_width)
{
   for (auto &token : tokens)
   {
      int x_position = std::get<1>(token);
      if (x_position > max_num_columns) continue;

      std::string &text = std::get<0>(token);
      ALLEGRO_COLOR color = std::get<2>(token);
      int concatinated_string_max_length = max_num_columns - x_position;
      std::string concatinated_string = text.substr(0, concatinated_string_max_length);

      al_draw_text(font, color, x + (x_position * cell_width), y, ALLEGRO_ALIGN_LEFT, concatinated_string.c_str());
   }
}

void AdvancedLineRenderer::render()
{
   if (!(font))
      {
         std::stringstream error_message;
         error_message << "AdvancedLineRenderer" << "::" << "render" << ": error: " << "guard \"font\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_color))
      {
         std::stringstream error_message;
         error_message << "AdvancedLineRenderer" << "::" << "render" << ": error: " << "guard \"font_color\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(backfill_color))
      {
         std::stringstream error_message;
         error_message << "AdvancedLineRenderer" << "::" << "render" << ": error: " << "guard \"backfill_color\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string concatinated_line = full_line_text.substr(0, max_num_columns);
   // draw the line straight out
   al_draw_text(font, *font_color, x, y, ALLEGRO_ALIGN_LEFT, concatinated_line.c_str());

   float cell_width = al_get_text_width(font, " ");

   std::vector<std::tuple<std::string, int, ALLEGRO_COLOR>> tokens;

   tokens = build_comment_tokens();
   render_tokens(tokens, cell_width);

   tokens = build_quoted_string_tokens();
   render_tokens(tokens, cell_width);

   tokens = build_quintessence_yaml_name_element_tokens();
   render_tokens(tokens, cell_width);

   tokens = build_test_declaration_element_tokens();
   render_tokens(tokens, cell_width);

   return;
}
} // namespace Renderer
} // namespace CodeEditor
} // namespace Hexagon


