#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace UI
   {
      class DrawingBox : public StageInterface
      {
      private:
         bool initialized;
         AllegroFlare::FontBin* font_bin;
         int width;
         int height;
         static ALLEGRO_EVENT a_default_empty_event;
         ALLEGRO_BITMAP* surface;
         bool stroking;
         int pointer_x;
         int pointer_y;

      public:
         DrawingBox(AllegroFlare::FontBin* font_bin=nullptr, int width=800, int height=800);
         ~DrawingBox();

         void set_stroking(bool stroking);
         void set_pointer_x(int pointer_x);
         void set_pointer_y(int pointer_y);

         bool get_initialized();
         bool get_stroking();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void initialize();
      void render() override;
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      void draw_crosshair();
      void destroy() override;
      };
   }
}



