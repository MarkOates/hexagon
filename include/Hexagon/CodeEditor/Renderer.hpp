#pragma once



#include <Hexagon/RendererInterface.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/placement3d.h>


namespace CodeEditor
{
   class Renderer : public Hexagon::RendererInterface
   {
   private:
      bool is_focused;
      bool draw_line_numbers;
      bool draw_extra_spaces_at_end_of_line;
      bool draw_null_space;
      bool draw_backfill;
      bool draw_represents_symlink;
      ALLEGRO_DISPLAY *display;
      ::CodeEditor::CodeEditor *code_editor;
      placement3d place;
      int cell_width;
      int cell_height;
      ALLEGRO_FONT *font;
      ALLEGRO_COLOR base_font_color;
      ALLEGRO_COLOR backfill_color;
      float backfill_opacity;

      void render_code_lines(placement3d &place, ALLEGRO_COLOR frame_color);
      void render_raw();
      void render_cursor_position_info();
      void draw_selections(int cell_width, int cell_height);

   public:
      Renderer(
         bool draw_line_numbers,
         bool is_focused,
         ::CodeEditor::CodeEditor *code_editor,
         placement3d place,
         ALLEGRO_FONT *font,
         ALLEGRO_DISPLAY *display,
         int cell_width,
         int cell_height,
         ALLEGRO_COLOR base_font_color,
         ALLEGRO_COLOR backfill_color,
         float backfill_opacity
         );
      ~Renderer();

      virtual void render() override;
      void set_draw_represents_symlink(bool draw_represents_symlink=false);
      bool get_draw_represents_symlink();

   public: // not really, but listed as public so they can be tested
      ALLEGRO_COLOR build_font_color(ALLEGRO_COLOR frame_color);
      ALLEGRO_COLOR build_frame_color();
      ALLEGRO_COLOR build_backfill_color();
   };
} // namespace CodeEditor



