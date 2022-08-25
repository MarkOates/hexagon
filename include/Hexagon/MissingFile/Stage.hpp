#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace MissingFile
   {
      class Stage : public StageInterface
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string expected_filename;
         std::string title_text;
         static ALLEGRO_EVENT a_default_empty_event;
         bool is_focused;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;

      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, std::string expected_filename="[Expected filename not set]");
         virtual ~Stage();

         void set_is_focused(bool is_focused);
         void set_display(ALLEGRO_DISPLAY* display);
         void set_font(ALLEGRO_FONT* font);
         void set_cell_width(int cell_width);
         void set_cell_height(int cell_height);
         std::string get_expected_filename() const;
         bool get_is_focused() const;
         ALLEGRO_DISPLAY* get_display() const;
         ALLEGRO_FONT* get_font() const;
         int get_cell_width() const;
         int get_cell_height() const;
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         virtual void render() override;
         ALLEGRO_FONT* obtain_text_font();
         ALLEGRO_FONT* obtain_title_font();
         void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
         void create_expected_file();
      };
   }
}



