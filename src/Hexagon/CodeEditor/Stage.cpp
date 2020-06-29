

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


Stage::Stage(::CodeEditor::CodeEditor* code_editor)
   : StageInterface(StageInterface::CODE_EDITOR)
   , code_editor(code_editor)
{
}


Stage::~Stage()
{
}


::CodeEditor::CodeEditor* Stage::get_code_editor()
{
   return code_editor;
}


::CodeEditor::CodeEditor* &Stage::get_code_editor_ref()
{
   return code_editor;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render(bool is_focused, ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
//place = this->place;

if (code_editor->get_type() == ONE_LINE_INPUT_BOX)
{
   ALLEGRO_COLOR outline_and_text_color = al_color_name("dodgerblue");
   float width = get_place().size.x;
   float height = get_place().size.y;
   //std::string top_left_text = "ESC: Close";
   std::string bottom_right_text = "search";

   Hexagon::OneLineInputBox::Renderer renderer(
      font,
      outline_and_text_color,
      width,
      height,
      cell_width,
      cell_height,
      code_editor->get_lines_ref(),
      code_editor->selections,
      code_editor->get_cursor_x(),
      code_editor->get_cursor_y(),
      get_place(),
      code_editor->get_first_line_number(),
      (code_editor->get_mode() == ::CodeEditor::CodeEditor::EDIT) // in_edit_mode
   );

   //renderer.set_top_left_text(top_left_text);
   renderer.set_bottom_right_text(bottom_right_text);

   renderer.render();
}
else if (code_editor->get_type() == GIT_COMMIT_MESSAGE_INPUT_BOX)
{
   ALLEGRO_COLOR outline_and_text_color = al_color_name("salmon");
   float width = get_place().size.x;
   float height = get_place().size.y;
   //std::string top_left_text = "ESC: Close";
   std::string bottom_right_text = "commit and push";

   Hexagon::OneLineInputBox::Renderer renderer(
      font,
      outline_and_text_color,
      width,
      height,
      cell_width,
      cell_height,
      code_editor->get_lines_ref(),
      code_editor->selections,
      code_editor->get_cursor_x(),
      code_editor->get_cursor_y(),
      get_place(),
      code_editor->get_first_line_number(),
      (code_editor->get_mode() == ::CodeEditor::CodeEditor::EDIT) // in_edit_mode
   );

   //renderer.set_top_left_text(top_left_text);
   renderer.set_bottom_right_text(bottom_right_text);

   renderer.render();
}
else
{
   bool draw_line_numbers = true;
   ALLEGRO_FONT *code_font = font;
   ALLEGRO_FONT *overlay_font = font;

   ::CodeEditor::Renderer renderer(
      draw_line_numbers,
      is_focused,
      code_editor,
      code_font,
      display,
      cell_width,
      cell_height
   );
   renderer.render();

   if (code_editor->get_draw_info_overlay())
   {
      placement3d &place = get_place();
      std::string file_category_label
         = Hexagon::CodeEditor::FileCategoryDecorator(code_editor->get_file_category()).label();
      std::string text_to_render = file_category_label;
      place.start_transform();
      Hexagon::Elements::StageInfoOverlay stage_info_overlay(overlay_font, &place);
      //if (!is_focused) text_to_render = this->get_filename();
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
} // namespace CodeEditor
} // namespace Hexagon


