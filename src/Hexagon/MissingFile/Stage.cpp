

#include <Hexagon/MissingFile/Stage.hpp>
#include <Hexagon/Elements/TexturedRectangle.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <Blast/FileCreator.hpp>


namespace Hexagon
{
namespace MissingFile
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, std::string expected_filename)
   : StageInterface(StageInterface::MISSING_FILE)
   , font_bin(font_bin)
   , expected_filename(expected_filename)
   , title_text("MISSING FILE")
   , is_focused(true)
   , display(nullptr)
   , font(nullptr)
   , cell_width(10)
   , cell_height(20)
{
}


Stage::~Stage()
{
}


void Stage::set_is_focused(bool is_focused)
{
   this->is_focused = is_focused;
}


void Stage::set_display(ALLEGRO_DISPLAY* display)
{
   this->display = display;
}


void Stage::set_font(ALLEGRO_FONT* font)
{
   this->font = font;
}


void Stage::set_cell_width(int cell_width)
{
   this->cell_width = cell_width;
}


void Stage::set_cell_height(int cell_height)
{
   this->cell_height = cell_height;
}


std::string Stage::get_expected_filename()
{
   return expected_filename;
}


bool Stage::get_is_focused()
{
   return is_focused;
}


ALLEGRO_DISPLAY* Stage::get_display()
{
   return display;
}


ALLEGRO_FONT* Stage::get_font()
{
   return font;
}


int Stage::get_cell_width()
{
   return cell_width;
}


int Stage::get_cell_height()
{
   return cell_height;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   placement3d place = get_place();
   place.start_transform();

   float padding = cell_width;
   float h_padding = (float)cell_width / 2;
   float line_height = al_get_font_line_height(font);
   ALLEGRO_FONT *title_font = obtain_title_font();

   float width = place.size.x;
   float height = place.size.y;
   ALLEGRO_COLOR color = al_color_html("d82133");
   float thickness = 2.5;

   al_draw_rectangle(
      h_padding, h_padding,
      width-h_padding, height-h_padding,
      color, thickness);

   //ALLEGRO_BITMAP *texture = nullptr;// TODO
   //Hexagon::Elements::TexturedRectangle red_lines_texture_background(
   //   h_padding,
   //   h_padding,
   //   width-h_padding,
   //   height-h_padding,
   //   texture
   //);
   //red_lines_texture_background.draw();

   al_draw_text(title_font, color, width/2, height/3, ALLEGRO_ALIGN_CENTER, title_text.c_str());

   al_draw_text(font, color, width/2, height/3 + line_height*3, ALLEGRO_ALIGN_CENTER, expected_filename.c_str());

   //std::string create_message = "Press ENTER to create (requires reload)";
   //al_draw_text(font, color, width/2, height/3 + line_height*9, ALLEGRO_ALIGN_CENTER, create_message.c_str());

   place.restore_transform();
}

ALLEGRO_FONT* Stage::obtain_text_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "obtain_text_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Menlo-Regular.ttf -20");
}

ALLEGRO_FONT* Stage::obtain_title_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "obtain_title_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("EurostileExtendedBlack-aka-ExtendedBold.ttf -60");
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   return;
}

void Stage::create_expected_file()
{
   std::string initial_file_contents = "// empty";
   Blast::FileCreator file_creator(expected_filename, initial_file_contents);
   file_creator.create_if_not_exists();
   return;
}
} // namespace MissingFile
} // namespace Hexagon


