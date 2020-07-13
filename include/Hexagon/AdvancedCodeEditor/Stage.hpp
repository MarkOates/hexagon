#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/Elements/TextMesh.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Stage : public StageInterface
      {
      private:
         AllegroFlare::FontBin* font_bin;
         int num_columns;
         int num_rows;
         std::vector<std::string> lines;
         Hexagon::Elements::TextMesh text_mesh;
         Hexagon::AdvancedCodeEditor::Cursor cursor;
         static ALLEGRO_EVENT a_default_empty_event;
         bool initialized;

      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, int num_columns=0, int num_rows=0);
         virtual ~Stage();


         std::vector<std::string> get_lines();
         Hexagon::AdvancedCodeEditor::Cursor &get_cursor_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      bool cursor_move_up();
      bool cursor_move_down();
      bool cursor_move_left();
      bool cursor_move_right();
      void initialize();
      void set_content(std::string content="");
      virtual void render() override;
      virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      ALLEGRO_FONT* obtain_text_font();
      void refresh_text_mesh();
      };
   }
}



