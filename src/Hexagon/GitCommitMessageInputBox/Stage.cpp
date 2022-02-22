

#include <Hexagon/GitCommitMessageInputBox/Stage.hpp>
#include <iostream>
#include <allegro5/allegro_color.h>
#include <Hexagon/OneLineInputBox/Renderer.hpp>
#include <Hexagon/CodeEditor/Renderer.hpp>
#include <Hexagon/Elements/StageInfoOverlay.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/GitCommitMessageInputBox/EventController.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/GitCommitMessageInputBox/EventController.hpp>


namespace Hexagon
{
namespace GitCommitMessageInputBox
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
   , state("normal")
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
   if (!((code_editor.get_type() == GIT_COMMIT_MESSAGE_INPUT_BOX)))
      {
         std::stringstream error_message;
         error_message << "Stage" << "::" << "render" << ": error: " << "guard \"(code_editor.get_type() == GIT_COMMIT_MESSAGE_INPUT_BOX)\" not met";
         throw std::runtime_error(error_message.str());
      }
   //ALLEGRO_COLOR outline_color = al_color_html("f9ac1e");
   //ALLEGRO_COLOR user_input_text_color = al_color_html("ffd033");
   ALLEGRO_COLOR outline_color = al_color_name("red");
   ALLEGRO_COLOR user_input_text_color = al_color_name("red");
   float width = get_place().size.x;
   float height = get_place().size.y;
   //std::string top_left_text = "ESC: Close";
   std::string bottom_right_text = "commit and push";
   ALLEGRO_COLOR backfill_color = al_color_name("black");
   std::vector<std::string> lines = code_editor.get_lines_ref();
   int char_count = code_editor_char_count();

   Hexagon::OneLineInputBox::Renderer renderer(
      nullptr,
      get_font(),
      outline_color,
      user_input_text_color,
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

   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return; // these two lines disabled during copy from Hexagon/CodeEditor/Stage ::GitCommitMessageInputBox::EventController stage_event_controller(this); stage_event_controller.process_local_event(event_name, action_data); return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   // these two lines disabled during copy from Hexagon/CodeEditor/Stage
   ::GitCommitMessageInputBox::EventController stage_event_controller(this);
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
} // namespace GitCommitMessageInputBox
} // namespace Hexagon


