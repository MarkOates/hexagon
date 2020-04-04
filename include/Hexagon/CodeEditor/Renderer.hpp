#pragma once



#include <Hexagon/RendererInterface.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/render_cache.h>
#include <allegro_flare/placement3d.h>



namespace CodeEditor
{
   class Renderer : public Hexagon::RendererInterface
   {
   private:
      bool is_focused;
      bool is_showing_info;
      bool draw_line_numbers;
      bool draw_extra_spaces_at_end_of_line;
      bool draw_null_space;
      ALLEGRO_DISPLAY *display;
      RenderCache render_cache;
      CodeEditor::Stage *stage;
      int cell_width;
      int cell_height;
      ALLEGRO_FONT *font;

      //void draw_cursor(bool is_focused, int cursor_x, float _cursor_y, float _cell_width, CodeEditor::Stage::mode_t mode);
      void render_code_lines(placement3d &place, ALLEGRO_COLOR frame_color);
      void render_raw();
      void render_info_overlay();
      void render_cursor_position_info();
      void draw_selections(int cell_width, int cell_height);

   public:
      Renderer(bool draw_line_numbers, bool is_focused, CodeEditor::Stage *stage, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, int cell_width, int cell_height);
      ~Renderer();

      virtual void render() override;
   };
} // namespace CodeEditor



