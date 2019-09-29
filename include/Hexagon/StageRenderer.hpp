#pragma once



#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/render_cache.h>



class Stage;

class StageRenderer
{
private:
   ALLEGRO_DISPLAY *display;
   RenderCache render_cache;
   Stage *stage;
   int cell_width;
   int cell_height;
   ALLEGRO_FONT *font;

   void render_code_lines();
   void render_raw();
   void draw_selections(int cell_width, int cell_height);

public:
   StageRenderer(Stage *stage, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, int cell_width, int cell_height);
   ~StageRenderer();

   void render();
};



