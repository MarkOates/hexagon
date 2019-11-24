#pragma once



#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/render_cache.h>
#include <allegro_flare/placement3d.h>



class StageRenderer
{
private:
   ALLEGRO_DISPLAY *display;
   RenderCache render_cache;
   CodeEditor::Stage *stage;
   int cell_width;
   int cell_height;
   ALLEGRO_FONT *font;

   void draw_cursor(int cursor_x, float _cursor_y, float _cell_width, CodeEditor::Stage::mode_t mode);
   void render_code_lines(placement3d &place);
   void render_raw();
   void draw_selections(int cell_width, int cell_height);

public:
   StageRenderer(CodeEditor::Stage *stage, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, int cell_width, int cell_height);
   ~StageRenderer();

   void render();
};



