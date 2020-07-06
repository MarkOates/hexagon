#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace FullScreenOverlay
   {
      class Stage : public StageInterface
      {
      private:
         bool initialized;
         static ALLEGRO_EVENT a_default_empty_event;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_FONT* text_font;
         ALLEGRO_BITMAP* screen_sub_bitmap;

      public:
         Stage(ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* text_font=nullptr);
         ~Stage();

         void set_text_font(ALLEGRO_FONT* text_font);
         void set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap);

         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void initialize();
      void draw_design();
      void render(bool _is_focused=true, ALLEGRO_DISPLAY* _display=nullptr, ALLEGRO_FONT* _font=nullptr, int _cell_width=10, int _cell_height=20);
      void draw();
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



