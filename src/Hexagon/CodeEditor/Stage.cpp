

#include <Hexagon/CodeEditor/Stage.hpp>
#include <sstream>
#include <iostream>
#include <allegro5/allegro_color.h>
#include <Hexagon/OneLineInputBox/Renderer.hpp>
#include <Hexagon/CodeEditor/Renderer.hpp>
#include <Hexagon/Elements/StageInfoOverlay.hpp>
#include <Hexagon/CodeEditor/FileCategoryDecorator.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>


namespace Hexagon
{
namespace CodeEditor
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(::CodeEditor::CodeEditor code_editor)
   : StageInterface(code_editor.get_type())
   , code_editor(code_editor)
   , is_focused(false)
   , display(nullptr)
   , font(nullptr)
   , font_bin(nullptr)
   , cell_width(10)
   , cell_height(20)
   , base_font_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f})
   , backfill_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 1.0f})
   , state("normal")
   , represents_a_symlink(false)
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


void Stage::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Stage::set_cell_width(int cell_width)
{
   this->cell_width = cell_width;
}


void Stage::set_cell_height(int cell_height)
{
   this->cell_height = cell_height;
}


void Stage::set_base_font_color(ALLEGRO_COLOR base_font_color)
{
   this->base_font_color = base_font_color;
}


void Stage::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void Stage::set_represents_a_symlink(bool represents_a_symlink)
{
   this->represents_a_symlink = represents_a_symlink;
}


::CodeEditor::CodeEditor Stage::get_code_editor()
{
   return code_editor;
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


AllegroFlare::FontBin* Stage::get_font_bin()
{
   return font_bin;
}


int Stage::get_cell_width()
{
   return cell_width;
}


int Stage::get_cell_height()
{
   return cell_height;
}


ALLEGRO_COLOR Stage::get_base_font_color()
{
   return base_font_color;
}


ALLEGRO_COLOR Stage::get_backfill_color()
{
   return backfill_color;
}


bool Stage::get_represents_a_symlink()
{
   return represents_a_symlink;
}


::CodeEditor::CodeEditor &Stage::get_code_editor_ref()
{
   return code_editor;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::change_state_to_submitted_and_pending_destruction()
{
   state = "submitted_and_pending_destruction";
   return;
}

bool Stage::is_state_to_submitted_and_pending_destruction()
{
   return state == "submitted_and_pending_destruction";
}

void Stage::render()
{
   //place = this->place;

   if (code_editor.get_type() == ONE_LINE_INPUT_BOX)
   {
      std::stringstream error;
      error << "Hexagon/CodeEditor/Stage: Unexpected ask to render ONE_LINE_INPUT_BOX type. "
            << "Expecting to now be using Hexagon::OneLineInputBox::Stage type instead.";
      throw std::runtime_error(error.str());
   }
   else if (code_editor.get_type() == GIT_COMMIT_MESSAGE_INPUT_BOX)
   {
      std::stringstream error;
      error << "Hexagon/CodeEditor/Stage: Unexpected ask to render GIT_COMMIT_MESSAGE_INPUT_BOX type. "
            << "Expecting to now be using Hexagon::OneLineInputBox::Stage type instead.";
      throw std::runtime_error(error.str());
   }
   else
   {
      bool draw_line_numbers = true;
      ALLEGRO_FONT *code_font = get_font();
      ALLEGRO_FONT *overlay_font = get_font();
      //ALLEGRO_COLOR base_font_color = al_color_name("white");
      //ALLEGRO_COLOR backfill_color = al_color_name("black");
      //ALLEGRO_COLOR base_font_color = al_color_name("white");
      //ALLEGRO_COLOR backfill_color = al_color_name("black");
      float backfill_opacity = 0.8f;

      ::CodeEditor::Renderer renderer(
         draw_line_numbers,
         get_is_focused(),
         &code_editor,
         get_place(),
         code_font,
         get_display(),
         get_cell_width(),
         get_cell_height(),
         base_font_color,
         backfill_color,
         backfill_opacity
      );
      if (get_represents_a_symlink()) renderer.set_draw_represents_symlink(true);
      renderer.render();

      if (code_editor.get_draw_info_overlay())
      {
         placement3d &place = get_place();
         std::string file_category_label
            = Hexagon::CodeEditor::FileCategoryDecorator(code_editor.get_file_category()).label();
         std::string text_to_render = file_category_label;
         //ALLEGRO_COLOR backfill_color = al_color_name("black");
         //float backfill_opacity = 0.8f;

         place.start_transform();
         Hexagon::Elements::StageInfoOverlay stage_info_overlay(
            get_font_bin(),
            &backfill_color,
            backfill_opacity,
            &place
         );
         //if (!is_focused) text_to_render = this.get_filename();
         stage_info_overlay.set_text(text_to_render);
         stage_info_overlay.render();
         place.restore_transform();
      }
   }

   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return; ::CodeEditor::EventController stage_event_controller(this); stage_event_controller.process_local_event(event_name, action_data); return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   ::CodeEditor::EventController stage_event_controller(this);
   stage_event_controller.process_event(event);
   return;
}

int Stage::code_editor_char_count()
{
   if (code_editor.get_lines_ref().size() == 0) return 0;
   int char_count = 0;
   for (auto &line : code_editor.get_lines_ref())
   {
      char_count += line.size();
   }
   return char_count + (code_editor.get_lines_ref().size() - 1);
}
} // namespace CodeEditor
} // namespace Hexagon


