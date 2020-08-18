

#include <Hexagon/CodeEditor/Stage.hpp>
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
   , cell_width(10)
   , cell_height(20)
   , base_font_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f})
   , backfill_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 1.0f})
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


void Stage::set_base_font_color(ALLEGRO_COLOR base_font_color)
{
   this->base_font_color = base_font_color;
}


void Stage::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
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


::CodeEditor::CodeEditor &Stage::get_code_editor_ref()
{
   return code_editor;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render()
{
//place = this->place;

if (code_editor.get_type() == ONE_LINE_INPUT_BOX)
{
   ALLEGRO_COLOR outline_and_text_color = al_color_name("dodgerblue");
   float width = get_place().size.x;
   float height = get_place().size.y;
   //std::string top_left_text = "ESC: Close";
   std::string bottom_right_text = "search";
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   std::vector<std::string> lines = code_editor.get_lines_ref();
   int char_count = code_editor_char_count();

   Hexagon::OneLineInputBox::Renderer renderer(
      get_font(),
      outline_and_text_color,
      backfill_color,
      width,
      height,
      get_cell_width(),
      get_cell_height(),
      lines,
      code_editor.selections,
      code_editor.get_cursor_x(),
      code_editor.get_cursor_y(),
      get_place(),
      code_editor.get_first_line_number(),
      (code_editor.get_mode() == ::CodeEditor::CodeEditor::EDIT) // in_edit_mode
   );

   //renderer.set_top_left_text(top_left_text);
   renderer.set_bottom_right_text(bottom_right_text);
   renderer.set_bottom_left_text(std::to_string(char_count));

   renderer.render();
}
else if (code_editor.get_type() == GIT_COMMIT_MESSAGE_INPUT_BOX)
{
   ALLEGRO_COLOR outline_and_text_color = al_color_name("salmon");
   float width = get_place().size.x;
   float height = get_place().size.y;
   //std::string top_left_text = "ESC: Close";
   std::string bottom_right_text = "commit and push";
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   int char_count = code_editor_char_count();

   Hexagon::OneLineInputBox::Renderer renderer(
      get_font(),
      outline_and_text_color,
      backfill_color,
      width,
      height,
      get_cell_width(),
      get_cell_height(),
      code_editor.get_lines_ref(),
      code_editor.selections,
      code_editor.get_cursor_x(),
      code_editor.get_cursor_y(),
      get_place(),
      code_editor.get_first_line_number(),
      (code_editor.get_mode() == ::CodeEditor::CodeEditor::EDIT) // in_edit_mode
   );

   //renderer.set_top_left_text(top_left_text);
   renderer.set_bottom_right_text(bottom_right_text);
   renderer.set_bottom_left_text(std::to_string(char_count));

   renderer.render();
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
         overlay_font,
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
int char_count = 0;
for (auto &line : code_editor.get_lines_ref())
{
   char_count += line.size();
}
return char_count + (code_editor.get_lines_ref().size() - 1);

}
} // namespace CodeEditor
} // namespace Hexagon


